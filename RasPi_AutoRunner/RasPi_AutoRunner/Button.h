#pragma once
#include"display_manager.h"

class Button {
private:
	Screen_Resizer& resizer;
	RoundRect Frame_rect;
	String string;
	const Font font;
	bool Click = false;
	bool returnClick = false;
public:
	Button(Screen_Resizer& resizer, RoundRect Frame_rect, String string, uint8 font_size)
		:resizer(resizer)
		, Frame_rect(Frame_rect)
		, string(string)
		, font(font_size)
	{
	}	/// @brief ボタンの判定関数
	void Update() {
		if (resizer.toReal(Frame_rect).mouseOver() && resizer.toReal(Frame_rect).leftClicked())
			returnClick = 1;
		else
			returnClick = 0;
		if (resizer.toReal(Frame_rect).mouseOver() && resizer.toReal(Frame_rect).leftPressed())
			Click = 1;
		else
			Click = 0;
	}
	/// @brief ボタンの描画関数
	void draw() {
		if (Click) {
			resizer.toReal(Frame_rect).movedBy(resizer.Cal_Size({ 3,3 })).draw();
		}
		else {
			resizer.toReal(Frame_rect).drawShadow(resizer.Cal_Size({ 3,3 }), 0, 0).draw();
		}
		font(string).drawAt(resizer.toReal(Frame_rect).center(), Palette::Black);
	}
	/// @brief ボタンの判定を返す関数
	/// @return 0=クリックされていない　1=クリックされている
	bool Rect_judge() {
		return Click;
	}
	void Set_string(String s) {
		string = s;
	}
};
