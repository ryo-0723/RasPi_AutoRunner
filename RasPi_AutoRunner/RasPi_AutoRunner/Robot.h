#pragma once

#include "display_manager.h"

class Robot {
private:
	Screen_Resizer& resizer;
	RectF Robot_shape;
	Vec3 Robot_Pos;
	Vec3 Offset_Pos = {};

public:
	Robot(Screen_Resizer& resizer,RectF Robot_shape)
		:resizer(resizer),Robot_shape(Robot_shape)
	{}


	void Update() {

	}
	void draw() {
		resizer.toReal(Robot_shape)
			.draw(Color{ 79 ,86 ,87,255 });
	}


};
