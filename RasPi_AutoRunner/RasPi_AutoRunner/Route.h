#pragma once
#include "New_RunControll.h"
#include "RouteConstant.h"
#include "MenuConstant.h"



/*
* 自動制御のクラス
* ほかのファイルに作った経路を実行し、機構も動かす
* 
*
*/
class Route {
private:
	New_RunControll auto_move;
	LineString next_line;
	Vec2 next_Pos;
	double turn = 0;
	int route_case = 1;
	double start_s = 0;
	double end_s = 0;
	float time = 0;
	bool auto_end_flag = false;
	SendData Data;
	//bool auto_start_flag = false;
public:
	Route()
		:auto_move(5.0, 50)
		, next_Pos()
		, next_line() {}

	void update(bool auto_start_flag) {
		if (auto_start_flag) {
			switch (route_case) {
			case 1:
				//物の手前までくる
				start_s = 0;
				end_s = 0.2;
				next_line = blueshootRoute1;
				break;
			case 2:
				//物をつかむところまでくる
				start_s = 0.2;
				end_s = 0;
				next_line = blueshootRoute2;
				break;
			case 3:
				//物をつかんで発射位置まで移動する
				start_s = 0;
				end_s = 0;
				next_line = blueshootRoute3;
				break;
			case 4:
				//次の回収物の横までくる
				start_s = 0;
				end_s = 0;
				next_line = blueshootRoute4;
				break;
			case 5:
				//回収物をつかむ場所まで移動する
				start_s = 0;
				end_s = 0;
				next_line = blueshootRoute5;
				break;
			case 6:
				//回収物をつかんで発射位置まで移動する
				start_s = 0;
				end_s = 0;
				next_line = blueshootRoute6;
				break;
			}

			auto_move.calculation(next_line, start_s, end_s);
			auto_move.tar_point();
			next_Pos = next_line.calculatePointFromOrigin(auto_move.tar_dis());
			if (auto_move.next_status()) {//今のケースの経路をしておわったら次のフラグへ
				if (route_case < 7) {
					route_case++;
				}
				else {
					auto_end_flag = true;
				}
				auto_move.set_next_status();//次の経路のためのフラグ整理
			}
		}
		setdata();
	}
	Vec3 Next_Pos() {
		return Vec3{ next_Pos.x,next_Pos.y,turn };
	}
	float move_time() {
		return Time::GetSec() - time;
	}
	bool Auto_end_flag() {
		return auto_end_flag;
	}

	SendData SetData() {
		return Data;
	}
	void setdata() {
		Data.x_axis = (long)Next_Pos().x;
		Data.y_axis = (long)Next_Pos().y;
		Data.turn = (long)Next_Pos().z;
		Data.rpm = 0;
		Data.roller_angle = 0;
		Data.catapult_shoot = 1;
		Data.catapult_charge = 1;
		Data.roller_shoot = 1;
		Data.roller_collect = 1;
		Data.auto_end_flag = Auto_end_flag();
		//自動の終了後に送るフラグ
	}
};
