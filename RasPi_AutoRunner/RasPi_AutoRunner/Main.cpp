# include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include "Field.h"
#include "Menu.h"
#include "Route.h"

SIV3D_SET(EngineOption::Renderer::Direct3D11);
std::pair<RectF, RectF> Screen_SplitFixedRight(const RectF& raw, double px) {
	return std::make_pair(
		RectF{ 0,0,raw.w - px,raw.h },
		RectF{ raw.w - px,0,px,raw.h }
	);
}
void Main()
{
	Window::SetMinimumFrameBufferSize({ 1000, 400 });
	Window::Resize(1023,605);
	Screen_Resizer display1({ 4000,7500 });
	Screen_Resizer display2({ 1800,1500 }, ScreenStyle::Keep);
	Window::Resize(1023, 535);

	Field field(display1);
	Menu menu(display2);
	Route route;

	display1.SetStyle(ScreenStyle::Center);
	Window::SetStyle(WindowStyle::Sizable);//ウィンドウを自由に大きさ変えれるやつ

	const Array<SerialPortInfo> infos = System::EnumerateSerialPorts();
	const Array<String> options = infos.map([](const SerialPortInfo& info)
		{
			return U"{}({})"_fmt(info.port, info.description);
	     }) << U"none";
	Serial serial;

	SendData sendData;
	const int serialspeed = 115200;
	while (System::Update())
	{
		ClearPrint();
		Print << options;
		const bool isOpen = serial.isOpen();
		if (menu.button_jadge()) {
			serial.open(U"COM10", serialspeed);
		}

		//////////////受信
		Print << sizeof(ReadData);
		ReadData readData;
		constexpr uint8 r_datasize=sizeof(readData);
		while (serial.available())
		{
			uint8 readbinary[r_datasize];
			for (int i = 0; i < r_datasize; i++)
				serial.read(readbinary[i]);
			memcpy(&readData,readbinary, r_datasize);
		}
		//////////////////////////
		/////////////////////送信
		constexpr uint8 s_datasize = sizeof(sendData);
		uint8 sendbinary[s_datasize];
		memcpy(sendbinary, &sendData, s_datasize);
		for (int i = 0; i < s_datasize;i++)
			serial.writeByte(sendbinary[i]);
		///////////////////////////

		const auto [left, right] = Screen_SplitFixedRight(Scene::Rect(), 700);
		//left.draw(ColorF{ 0.0, 0.5, 1.0, 0.1 });
		right.draw(Palette::Whitesmoke);
		display1.Resize_Update(left);
		display2.Resize_Update(right);

		display1.toReal(RectF{ 0,0, 4000, 7500 }).draw(ColorF{ 0, 1.0, 0, 0.5 });
		//display2.toReal(RectF{ 0,0, 700, 1000 }).draw(ColorF{ 0.0, 0.5, 1.0, 0.5 });
		route.update(readData.auto_flag);
		menu.Update();
		menu.MenuFrameDraw();
		menu.MenuUIDraw(readData, isOpen,serialspeed, readData.robot_speed,Time::GetMillisec()/1000.00);
		field.draw(menu.slider_jadge(),readData.x_axis,readData.y_axis,readData.turn);
		//////////////////////////////データのセット
		sendData=route.SetData();
		/////////////////////////////////

	}
}
