#pragma once

#include "display_manager.h"

class Meter {
private:
	Screen_Resizer& resizer;
	Circle  MeterCircle;
	const Font Value_Font{ 70,Resource(U"engine/font/DSEG7ModernMini-Bold.ttf") };
	const Font Unit_Font{ 50,Typeface::CJK_Regular_JP };
	Triangle Needle;
	String Unit_string;
	Vec2 range;
	Color Value_FontColor{ 0,204,255 ,200};
	Color Frame_Color{40,40,40,255};
	Color Needle_Color{250,70,0,220};
	Color Unit_FontColor{ 153,204,255,255};
	double Needle_Angle=0;
public:

	Meter(Screen_Resizer& resizer,Circle  MeterCircle,String Unit_string,Vec2 range)
		:resizer(resizer), MeterCircle(MeterCircle),Unit_string(Unit_string),range(range)
	{
		Needle = { {MeterCircle.center.x - MeterCircle.r/35,MeterCircle.center.y}
				,{MeterCircle.center.x,MeterCircle.center.y - MeterCircle.r*0.9}
				,{MeterCircle.center.x+ MeterCircle.r / 35,MeterCircle.center.y }
			};
	}

	void draw(double Value) {
		resizer.toReal(MeterCircle)
			.drawArc(-130_deg, 260_deg, resizer.Cal_Size(10), 0, Color{220, 220, 220,250})
		.drawArc(-130_deg, 260_deg, resizer.Cal_Size(5), 0, Frame_Color);
		/*-130 130*/
		//(x - in_min)* (out_max - out_min) / (in_max - in_min) + out_min;
		Needle_Angle=(Value - range.x)* (130 +130) / (range.y - range.x) -130;
		resizer.toReal(Needle).rotatedAt(resizer.Cal_Pos(MeterCircle.center),ToRadians(Needle_Angle))
			.draw(Needle_Color).drawFrame(resizer.Cal_Size(1), 0, Palette::Darkgrey);
		resizer.toReal(Circle{MeterCircle.center,MeterCircle.r / 45 })
			.draw(Needle_Color);
		Unit_Font(Unit_string)
			.drawBaseAt(resizer.Cal_Pos({ MeterCircle.center.x, MeterCircle.center.y + MeterCircle.r * 0.7 }), Unit_FontColor);
		Value_Font(U"{:.2f}"_fmt(Value))
			.drawAt(resizer.Cal_Pos({ MeterCircle.center.x, MeterCircle.center.y + MeterCircle.r * -0.15 }), Value_FontColor);
		}

		void Set_Unit_sting(String r ) {
			this->Unit_string = r;
		}
		void Set_range(Vec2 r) {
			this->range = r;
		}
};
