# include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include"Field.h"
#include"Menu.h"

Rect WorkArea;
SIV3D_SET(EngineOption::Renderer::Direct3D11);
std::pair<RectF, RectF> Screen_SplitFixedRight(const RectF& raw, double px) {
	return std::make_pair(
		RectF{ 0,0,raw.w - px,raw.h },
		RectF{ raw.w - px,0,px,raw.h }
	);
}
void Main()
{	
	Window::SetMinimumFrameBufferSize({ 1000, 500 });
	Window::Resize(1368, 730);
	Screen_Resizer display1({ 4000,7500 });
	Screen_Resizer display2({ 1800,1300 }, ScreenStyle::Keep);
	//Screen_Resizer display2({ 1800,1300 }, ScreenStyle::Left);
	//11:7の比率
	Field field(display1);
	Menu menu(display2);

	display1.SetStyle(ScreenStyle::Center);
	Window::SetStyle(WindowStyle::Sizable);//ウィンドウを自由に大きさ変えれるやつ

	const Array<MonitorInfo> monitors = System::EnumerateMonitors();

	for (const auto& monitor : monitors)
	{
		WorkArea = { 0,0,monitor.workArea.w,monitor.workArea.h - 23 };
	}

	Print << WorkArea;
	while (System::Update())
	{
		const auto [left, right] = Screen_SplitFixedRight(Scene::Rect(), 900);
		//left.draw(ColorF{ 0.0, 0.5, 1.0, 0.1 });
		right.draw(Palette::Whitesmoke);
		display1.Resize_Update(left);
		display2.Resize_Update(right);

		//ClearPrint();
		display1.toReal(RectF{ 0,0, 4000, 7500 }).draw(ColorF{ 0, 1.0, 0, 0.5 });
		//display2.toReal(RectF{ 0,0, 700, 1000 }).draw(ColorF{ 0.0, 0.5, 1.0, 0.5 });
		//
		//
		menu.Update();
		menu.MenuFrameDraw();
		menu.MenuUIDraw();
		field.draw(menu.slider_jadge());






	}
}
