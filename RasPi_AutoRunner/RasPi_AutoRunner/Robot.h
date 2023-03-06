#pragma once

#include "display_manager.h"

class Robot {
private:
	Screen_Resizer& resizer;
	RectF Robot_shape;
	Vec3 Robot_Pos;
	Vec2 Offset_Pos;
public:
	Robot(Screen_Resizer& resizer,RectF Robot_shape,int offsetx,int offsety)
		:resizer(resizer)
		,Robot_Pos()
		,Robot_shape(Robot_shape)
	{
		Offset_Pos.x = 290;
		Offset_Pos.y= 250;
	}
	//ロボットの開始位置からの座標を計算していこうと思う

	void Update(double x, double y, double turn) {
		Robot_Pos.x = Offset_Pos.x +38+ 800 +38+ 374 + 350 + x;
		Robot_Pos.y = 7500 - (Offset_Pos.y + 38 + 350 + y);
		Robot_Pos.z = turn;
		Print << Offset_Pos;
	}
	void draw() {
		resizer.toReal(Robot_shape).setCenter(resizer.Cal_Pos({ Robot_Pos.x,Robot_Pos.y })).rotated(Robot_Pos.z)
			.drawFrame(resizer.Cal_Size(10), 0, Palette::Black);
		RectF{ 0,0
			,resizer.Cal_Size(Robot_shape.w * 0.5)
			,resizer.Cal_Size(Robot_shape.h * 0.5) }
			.setPos(resizer.Cal_Pos({ Robot_Pos.x,Robot_Pos.y - Robot_shape.h * 0.5 }))
			.rotatedAt(resizer.Cal_Pos({ Robot_Pos.x,Robot_Pos.y }), Robot_Pos.z)
			.draw(Palette::Aqua);
	}


};
