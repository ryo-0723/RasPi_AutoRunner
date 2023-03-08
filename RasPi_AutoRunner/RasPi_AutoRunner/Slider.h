#pragma once

#include "display_manager.h"

class Slider {
private:
	Screen_Resizer& resizer;
	RoundRect Frame_rect;
	RoundRect _rect;
	Color Left_color, Right_color;
	bool slider = false;//スライダーの現在の位置
public:

	Slider(Screen_Resizer& resizer, RoundRect Frame_rect, Color Left_color, Color Right_color)
		:resizer(resizer), Frame_rect(Frame_rect), Left_color(Left_color), Right_color(Right_color)
	{
		_rect = { Frame_rect.rect.pos,Frame_rect.rect.size.x / 2.2,Frame_rect.rect.size.y,Frame_rect.r };
	}


	/// @brief スライダーの判定関数　毎周期先頭で行おう
	void Update() {
		if (resizer.toReal(_rect).mouseOver() && resizer.toReal(_rect).leftPressed())
			slider = 0;//左
		else if (resizer.toReal(_rect.movedBy({ Frame_rect.rect.size.x - _rect.rect.size.x,0 })).mouseOver()
			&& resizer.toReal(_rect.movedBy({ Frame_rect.rect.size.x - _rect.rect.size.x,0 })).leftPressed())
			slider = 1;//右
	}
	/// @brief スライダーの描画関数
	void  draw() {//スライダーっぽいスイッチ
		//ボタンの外枠
		resizer.toReal(Frame_rect).drawFrame(resizer.Cal_Size(2), 0, Palette::Purple);
		if (not slider)
			resizer.toReal(_rect)
			.draw(Left_color);
		else
			resizer.toReal(_rect.movedBy({ Frame_rect.rect.size.x - _rect.rect.size.x,0 }))
			.draw(Right_color);
	}
	/// @brief スライダーの判定を返す関数
	/// @return　0=左　1=右 
	bool Slider_jadge() {
		return slider;
	}
};
