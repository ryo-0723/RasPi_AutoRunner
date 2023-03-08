#pragma once

#include "display_manager.h"
#include "MenuConstant.h"
#include "Button.h"
#include "Slider.h"
#include "Meter.h"
#include <Siv3D.hpp>
class Menu {
private:
	Screen_Resizer& resizer;
	Button button, Routebutton;
	Slider slider;
	Meter Speedmeter;
	Meter Movetimer;
public:
	Menu(Screen_Resizer& resizer)
		:resizer(resizer)
		, button(resizer, Serial_box, U"Serial",20)
		, Routebutton(resizer,ChengeRoute,U"Routechange",15)
		, slider(resizer, Feildpick, Palette::Red, Palette::Blue)
		, Speedmeter(resizer, SpeedMeter, U"m/s", { 0,30 })
		, Movetimer(resizer, MoveTimer, U"/s", { 0,1800 }) {}

	const Font RobotPos{ 40 };
	const Font Machine_Font{ 25 };
	const Font Serialport{25};
	const Texture Signal_max{ 0xf08fa_icon ,100 };
	const Texture Signal_slash{ 0xf08fc_icon ,100 };

	void MenuFrameDraw() {
		resizer.toReal(Line{ 0,0,0,500 }).draw();
		resizer.toReal(Line{ 5,50,5,resizer.GetNowSize().y - 100 }).draw();
		//Print << resizer.GetNowSize();
		//メニュー画面の左側に線を書きたいけどあと回し
	}
	void Update() {
		slider.Update();
		button.Update();
		Routebutton.Update();
	}
	void MenuUIDraw(const ReadData& Data,bool open,int portspeed,double robot_speed,double move_time) {
		bool status[5] = { Data.roller_shoot,Data.roller_collect,Data.catapult_shoot,Data.catapult_charge ,Data.auto_flag};
		Speedmeter.draw(robot_speed);
		Movetimer.draw(move_time);
		robotposition_show(Data.x_axis, Data.y_axis, Data.turn);
		slider.draw();
		button.draw();
		Routebutton.draw();
		mechanism_state(Data.rpm, Data.roller_angle, status);
		Serial_status(open,portspeed);
	}
	bool slider_jadge() {
		return slider.Slider_jadge();
	}

	bool button_jadge() {
		return button.Rect_judge();
	}
	bool routebutton() {
		return Routebutton.Rect_click();
	}
	void Serial_status(bool s,int speed) {
		switch (s) {
		case 0:
			Signal_slash
				.resized(resizer.Cal_Size(230))
				.draw(resizer.Cal_Pos({ 1530, 20 }), Palette::Black);
			break;
		case 1:
			Signal_max
				.resized(resizer.Cal_Size(210))
				.draw(resizer.Cal_Pos({ 1530, 20 }), Palette::Black);
			break;
		}
		resizer.toReal(portFrame).drawFrame(resizer.Cal_Size(1),Palette::Black);
		Serialport(U"port:",speed).drawBase(resizer.Cal_Pos({ portFrame.x+30,portFrame.y+100 }), Palette::Black);


	}

	void robotposition_show(long x, long y, float yaw) {
		resizer.toReal(RobotPos_showFrame).drawFrame(resizer.Cal_Size(1), 0, Palette::Black);
		const auto f = [&](String&& str, double deltaY) {
			RobotPos(str).draw(resizer.Cal_Pos({ RobotPos_showFrame.x + 40,RobotPos_showFrame.y + deltaY }), Palette::Black);
		};
		f(U"Position", 15);
		f(U"X:{}"_fmt(x), 150);
		f(U"Y:{}"_fmt(y), 250);
		f(U"θ:{:.2f}"_fmt(yaw), 350);
	}
	//回収の表示は省略します！！
	void mechanism_state(float rpm, int angle, bool status[]) {
		resizer.toReal(mechanism_state_frame).drawFrame(resizer.Cal_Size(1), resizer.Cal_Size(0), Palette::Black);
		Machine_Font(U"BottleRoller")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.x + Machine_Font.spaceWidth() * 2,mechanism_state_frame.y }), Palette::Black);
		Machine_Font(U"Rorarion speed : ", rpm, U"m/s")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.x + Machine_Font.spaceWidth() * 18,mechanism_state_frame.y + Machine_Font.height() * 2.5 }), Palette::Black);
		Machine_Font(U"direction　: ", angle, U"°")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.x + Machine_Font.spaceWidth() * 18,mechanism_state_frame.y + Machine_Font.height() * 4.5 }), Palette::Black);
		Machine_Font(U"shoot status  : ", status[0] ? U"OK" : U"NOT")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.x + Machine_Font.spaceWidth() * 18,mechanism_state_frame.y + Machine_Font.height() * 6.5 }), Palette::Black);
		Machine_Font(U"collect_status  : ", status[1] ? U"catch" : U"rerease")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.x + Machine_Font.spaceWidth() * 18,mechanism_state_frame.y + Machine_Font.height() * 8.5 }), Palette::Black);

		Machine_Font(U"Catapult")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.x + Machine_Font.spaceWidth() * 2 ,mechanism_state_frame.y + Machine_Font.height() * 11 }), Palette::Black);
		Machine_Font(U"shoot status  : ", status[2] ? U"Complete" : U"NOT")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.x + Machine_Font.spaceWidth() * 18,mechanism_state_frame.y + Machine_Font.height() * 13 }), Palette::Black);
		Machine_Font(U"charge status : ", status[3] ? U"NOT" : U"Prepare")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.x + Machine_Font.spaceWidth() * 18,mechanism_state_frame.y + Machine_Font.height() * 15 }), Palette::Black);
		Machine_Font(U"Auto_flag : ", status[4] ? U"play" : U"NOT")
			.draw(resizer.Cal_Pos({ mechanism_state_frame.x + Machine_Font.spaceWidth() * 18,mechanism_state_frame.y + Machine_Font.height() * 17 }), Palette::Black);
	}

};
