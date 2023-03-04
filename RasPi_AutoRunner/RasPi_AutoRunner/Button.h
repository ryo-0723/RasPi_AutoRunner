#pragma once
#include"display_manager.h"

class Button {
private:
	Screen_Resizer& resizer;
	RoundRect Frame_rect;
	const Font TCP{ 20 };
	String defaultstring;
	String pushstring;
	Color defaultcolor;
	Color pushcolor;
	bool Click = false;
public:
	Button(Screen_Resizer& resizer, RoundRect Frame_rect, String defaultstring, String pushstring)
		:resizer(resizer), Frame_rect(Frame_rect)
	,defaultstring(defaultstring),pushstring(pushstring)
	,defaultcolor(defaultcolor),pushcolor(pushcolor){}
	/// @brief ボタンの判定関数
	void Update() {
		if (resizer.toReal(Frame_rect).mouseOver() && resizer.toReal(Frame_rect).leftPressed())
			Click = 1;
		else
			Click = 0;
	}
	/// @brief ボタンの描画関数
	void draw() {
		if (Click)
			resizer.toReal(Frame_rect).movedBy(resizer.Cal_Size({ 3,3 }))
			.draw();
		else
			resizer.toReal(Frame_rect).drawShadow(resizer.Cal_Size({ 3,3 }), 0, 0).draw();
	}
	/// @brief ボタンの判定を返す関数
	/// @return 0=クリックされていない　1=クリックされている
	bool Rect_judge() {
		return Click;
	}

};
