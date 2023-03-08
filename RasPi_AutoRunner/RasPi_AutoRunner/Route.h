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

	bool  set_catapult_charge = false;
	bool  set_catapult_shoot = false;
	bool  set_bottle_collect = false;
	bool  set_bottle_shoot = false;
	int  set_bottle_angle = 50;
	float  set_bottle_rpm = 0;
public:
	Route()
		:auto_move(5.0, 0.5)
		, next_Pos()
		, next_line() {}

	void update(bool auto_start_flag) {
		if (auto_start_flag) {
			switch (route_case) {
			case 1:
				//物の手前までくる
				start_s = 0;
				end_s = 0.1;
				next_line = blueshootRoute1;
				break;
			case 2:
				//物をつかむところまでくる
				start_s = 0.1;
				end_s = 0;
				next_line = blueshootRoute2;
				break;
			case 3:
				//アームを閉じる
				//カタパルトを上げる
				set_catapult_charge = true;
				set_bottle_collect = true;
				break;
			case 4:
				//物をつかんで発射位置まで移動する
				//発射についての設定は走っている途中にする
				set_bottle_rpm = 8;
				set_bottle_angle = 55;
				start_s = 0;
				end_s = 0;
				next_line = blueshootRoute3;
				break;
			case 5:
				//物を発射する
				//55度に向いて
				//スピードは7m/s
				set_bottle_shoot = true;
				set_catapult_shoot = true;
				break;
			case 6:
				set_bottle_shoot = false;
				set_catapult_shoot = false;
				set_catapult_charge = false;
				set_bottle_collect = false;
				//一度発射が終わったらリセットする
				//次の回収物の横までくる
				start_s = 0;
				end_s = 0;
				next_line = blueshootRoute4;
				break;
			case 7:
				//回収物をつかむ場所まで移動する
				start_s = 0;
				end_s = 0;
				next_line = blueshootRoute5;
				break;
			case 8:
				//ボトルをつかむ
				//カタパルトを上げる
				set_catapult_charge = true;
				set_bottle_collect = true;
				break;
			case 9:
				//回収物をつかんで発射位置まで移動する
				//発射についての設定は走っている途中にする
				set_bottle_rpm = 8;
				set_bottle_angle = 55;
				start_s = 0;
				end_s = 0;
				next_line = blueshootRoute6;
				break;
			case 10:
				//回収物を発射する
				//55度に向いて
				//スピードは8m/s
				set_bottle_shoot = true;
				set_catapult_shoot = true;
				break;
				//二回発射したら自動の終了
				//自動モードを切るために終了フラグを送る
			case 11:
				//情報リセットのためのケース
				auto_end_flag = true;
				set_bottle_shoot = false;
				set_catapult_shoot = false;
				set_catapult_charge = false;
				set_bottle_collect = false;
			}

			auto_move.calculation(next_line, start_s, end_s);
			auto_move.tar_point();
			next_Pos = next_line.calculatePointFromOrigin(auto_move.tar_dis());
			if (auto_move.next_status()) {//今のケースの経路をしておわったら次のフラグへ
				if (route_case < 11) {
					route_case++;
					auto_move.set_next_status();//次の経路のためのフラグ整理
				}
				else {
					auto_end_flag = true;//自動終了のフラグ送信
				}
			}
		}
		else {
			//自動の実行が許可されてないときの文
			//自動が実行されていないとき
			//自動の経路をリセットする
			route_case = 1;
		}
		setdata();
	}
	Vec3 Next_Pos() {
		return Vec3{ next_Pos.x,next_Pos.y,turn };
	}
	float move_time() {
		return Time::GetSec() - time;
	}

	SendData SetData() {
		return Data;
	}
	void setdata() {
		Data.x_axis = (long)Next_Pos().x;
		Data.y_axis = (long)Next_Pos().y;
		Data.turn = (long)Next_Pos().z;
		Data.rpm = set_bottle_rpm;
		Data.roller_angle = set_bottle_angle;
		Data.catapult_shoot =  set_catapult_shoot;
		Data.catapult_charge = set_catapult_charge;
		Data.roller_shoot = set_bottle_shoot;
		Data.roller_collect = set_bottle_collect;
		Data.auto_end_flag = auto_end_flag;
		//自動の終了後に送るフラグ
	}
};
