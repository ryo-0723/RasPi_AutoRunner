#pragma once

#include "display_manager.h"
#include "Robot.h"
#include "FieldConstant.h"

class Field {
private:
	Screen_Resizer& resizer;
	Robot robot;
	int offset_x = 290;
	int offset_y = 250;

	int offset2_x = 290;
	int offset2_y = 250;
	RectF RedField_Frame = { 0 + offset_x,0 + offset_y,3424,6924 };
	RectF BlueField_Frame = { 0 + offset2_x,0 + offset2_y,3424,6924 };

public:
	Field(Screen_Resizer& resizer)
		:resizer(resizer)
	     ,robot(resizer,robot_shape,offset_x,offset_y){}

	Vec2 RedField_Pos() {
		
	}

	Vec2 BlueField_Pos() {

	}


	void FieldWoodDraw() {
		//Print << resizer.toReal(RectF{ 0,0,1000,1000 }).draw();
		//赤ゾーンフィールド
		resizer.toReal(RedField_Frame).rounded(1)
			//.draw()
			.drawFrame(0, resizer.Cal_Size(38), Palette::Burlywood);
		resizer.toReal(RectF{ 0 + offset_x,800 + offset_y,800,38 }).draw(Palette::Burlywood);
		resizer.toReal(RectF{ 2624 + offset_x,800 + offset_y,800,38 }).draw(Palette::Burlywood);
		//ロボットのスタートゾーン横の長い棒
		resizer.toReal(RectF{ 800 + offset_x,5924 + offset_y,38,1000 }).draw(Palette::Burlywood);
		//横向きの長い棒
		resizer.toReal(RectF{ 0 + offset_x,2762 + offset_y,1212,38 }).draw(Palette::Burlywood);
		//白い三つの四角のとこの棒
		resizer.toReal(RectF{ 800 + offset_x,2800 + offset_y,38,2300 }).draw(Palette::Burlywood);

		//上から二つ目の左の四角の木枠
		resizer.toReal(RectF{ 374 + offset_x,1462 + offset_y,838,38 }).draw(Palette::Burlywood);
		resizer.toReal(RectF{ 374 + offset_x,1462 + offset_y,38,876 }).draw(Palette::Burlywood);
		resizer.toReal(RectF{ 374 + offset_x,2300 + offset_y,838,38 }).draw(Palette::Burlywood);
		//上から二つ目の右の四角の木枠
		resizer.toReal(RectF{ 2212 + offset_x,1462 + offset_y,838,38 }).draw(Palette::Burlywood);
		resizer.toReal(RectF{ 3012 + offset_x,1462 + offset_y,38,876 }).draw(Palette::Burlywood);
		resizer.toReal(RectF{ 2212 + offset_x,2300 + offset_y,838,38 }).draw(Palette::Burlywood);
	}
	void FieldLineDraw() {
		//上から一番目の四角の白い線
		resizer.toReal(RectF{ 770 + offset_x,0 + offset_y,30,800 }).draw();
		resizer.toReal(RectF{ 2624 + offset_x,0 + offset_y,30,800 }).draw();
		//上側の長い横線
		resizer.toReal(RectF{ 0 + offset_x,1432 + offset_y,3424,30 }).draw();
		//上から二つ目の四角の一部の白い線
		resizer.toReal(RectF{ 1182 + offset_x,1500 + offset_y,30,800 }).draw();
		resizer.toReal(RectF{ 2212 + offset_x,1500 + offset_y,30,800 }).draw();
		//下側の長い横線
		resizer.toReal(RectF{ 1212 + offset_x,2770 + offset_y,2212,30 }).draw();
		//はっととかが置いてあるとこの線
		resizer.toReal(RectF{ 2924 + offset_x,3224 + offset_y,500,2000 }).drawFrame(resizer.Cal_Size(30), 0);
		//三つの四角
		resizer.toReal(RectF{ 0 + offset_x,2800 + offset_y,800,500 }).drawFrame(resizer.Cal_Size(30), 0);
		resizer.toReal(RectF{ 0 + offset_x,3700 + offset_y,800,500 }).drawFrame(resizer.Cal_Size(30), 0);
		resizer.toReal(RectF{ 0 + offset_x,4600 + offset_y,800,500 }).drawFrame(resizer.Cal_Size(30), 0);
		//ロボットのスタートゾーン横の大きい四角
		resizer.toReal(RectF{ 0 + offset_x,5924 + offset_y,800,1000 }).drawFrame(resizer.Cal_Size(30), 0);
		//ロボットスタートゾーン横の小さい四角
		resizer.toReal(RectF{ 2624 + offset_x,6424 + offset_y,800,500 }).drawFrame(resizer.Cal_Size(30), 0);
	}
	void FieldRedDraw() {
		resizer.toReal(RectF{ 1250 + offset_x,5924 + offset_y,1000,1000 }).drawFrame(resizer.Cal_Size(30), 0, Palette::Red);
		resizer.toReal(RectF{ 1250 + offset_x,6224 + offset_y,700,700 }).drawFrame(resizer.Cal_Size(30), 0, Palette::Red);
	}

	void BlueFieldWoodDraw() {
		//Print << resizer.toReal(RectF{ 0,0,1000,1000 }).draw();
		//青ゾーンフィールド
		resizer.toReal(BlueField_Frame).rounded(1).drawFrame(0, resizer.Cal_Size(38), Palette::Burlywood);
		resizer.toReal(RectF{ 0 + offset2_x,800 + offset2_y,800,38 }).draw(Palette::Burlywood);
		resizer.toReal(RectF{ 2624 + offset2_x,800 + offset2_y,800,38 }).draw(Palette::Burlywood);
		//ロボットのスタートゾーン横の長い棒
		resizer.toReal(RectF{ 2586 + offset2_x,5924 + offset2_y,38,1000 }).draw(Palette::Burlywood);
		//横向きの長い棒
		resizer.toReal(RectF{ 2212 + offset2_x,2762 + offset2_y,1212,38 }).draw(Palette::Burlywood);
		//白い三つの四角のとこの棒
		resizer.toReal(RectF{ 2586 + offset2_x,2800 + offset2_y,38,2300 }).draw(Palette::Burlywood);

		//上から二つ目の右の四角の木枠
		resizer.toReal(RectF{ 374 + offset2_x,1462 + offset2_y,838,38 }).draw(Palette::Burlywood);
		resizer.toReal(RectF{ 374 + offset2_x,1462 + offset2_y,38,876 }).draw(Palette::Burlywood);
		resizer.toReal(RectF{ 374 + offset2_x,2300 + offset2_y,838,38 }).draw(Palette::Burlywood);
		//上から二つ目の左の四角の木枠
		resizer.toReal(RectF{ 2212 + offset2_x,1462 + offset2_y,838,38 }).draw(Palette::Burlywood);
		resizer.toReal(RectF{ 3012 + offset2_x,1462 + offset2_y,38,876 }).draw(Palette::Burlywood);
		resizer.toReal(RectF{ 2212 + offset2_x,2300 + offset2_y,838,38 }).draw(Palette::Burlywood);
	}
	void BlueFieldLineDraw() {
		//上から一番目の四角の白い線
		resizer.toReal(RectF{ 770 + offset2_x,0 + offset2_y,30,800 }).draw();
		resizer.toReal(RectF{ 2624 + offset2_x,0 + offset2_y,30,800 }).draw();
		//上側の長い横線
		resizer.toReal(RectF{ 0 + offset2_x,1432 + offset2_y,3424,30 }).draw();
		//上から二つ目の四角の一部の白い線
		resizer.toReal(RectF{ 1182 + offset2_x,1500 + offset2_y,30,800 }).draw();
		resizer.toReal(RectF{ 2212 + offset2_x,1500 + offset2_y,30,800 }).draw();
		//下側の長い横線
		resizer.toReal(RectF{ 0 + offset2_x,2770 + offset2_y,2212,30 }).draw();
		//はっととかが置いてあるとこの線
		resizer.toReal(RectF{ 0 + offset2_x,3224 + offset2_y,500,2000 }).drawFrame(resizer.Cal_Size(30), 0);
		//三つの四角
		resizer.toReal(RectF{ 2624 + offset2_x,2800 + offset2_y,800,500 }).drawFrame(resizer.Cal_Size(30), 0);
		resizer.toReal(RectF{ 2624 + offset2_x,3700 + offset2_y,800,500 }).drawFrame(resizer.Cal_Size(30), 0);
		resizer.toReal(RectF{ 2624 + offset2_x,4600 + offset2_y,800,500 }).drawFrame(resizer.Cal_Size(30), 0);
		//ロボットのスタートゾーン横の大きい四角
		resizer.toReal(RectF{ 2624 + offset2_x,5924 + offset2_y,800,1000 }).drawFrame(resizer.Cal_Size(30), 0);
		//ロボットスタートゾーン横の小さい四角
		resizer.toReal(RectF{ 0 + offset2_x,6424 + offset2_y,800,500 }).drawFrame(resizer.Cal_Size(30), 0);
	}
	void FieldBlueDraw() {
		resizer.toReal(RectF{ 1212 + offset2_x,5924 + offset2_y,1000,1000 }).drawFrame(resizer.Cal_Size(30), 0, Palette::Blue);
		resizer.toReal(RectF{ 1512 + offset2_x,6224 + offset2_y,700,700 }).drawFrame(resizer.Cal_Size(30), 0, Palette::Blue);
	}
	/// @brief フィールドを描画する関数
	/// @param r=0 赤フィールド　r=1　青フィールド
	void draw(bool r) {
		robot.Update(0,0,0);
		if (r) {
			BlueFieldWoodDraw();
			BlueFieldLineDraw();
			FieldBlueDraw();
		}
		else {
			FieldWoodDraw();
			FieldLineDraw();
			FieldRedDraw();
		}
		robot.draw();
	}
};
