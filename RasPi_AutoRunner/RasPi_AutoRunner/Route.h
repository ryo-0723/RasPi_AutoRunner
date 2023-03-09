#pragma once
#include "New_RunControll.h"
#include "RouteConstant.h"
#include "MenuConstant.h"
#include "Robot.h"
#include "New_RunControll_turn.h"


/*
* 自動制御のクラス
* ほかのファイルに作った経路を実行し、機構も動かす
* 
*
*/
class Route {
private:
	New_RunControll auto_move;
	New_RunControll_turn auto_move_turn;
	LineString next_line;
	Vec2 next_Pos;
	double turn = 0;
	int route_case = 0;
	double start_s = 0;
	double end_s = 0;
	unsigned long move_time = 0;
	bool auto_end_flag = false;
	SendData data;

	bool  set_catapult_charge = false;
	bool  set_catapult_shoot = false;
	bool  set_bottle_collect = false;
	bool  set_bottle_shoot = false;
	int  set_bottle_angle = 50;
	float  set_bottle_rpm = 0;
	bool buttondata = false;
public:
	Route()
		:auto_move(1.0, 0.5)
		, auto_move_turn()
		, next_Pos()
		, next_line(){}

	void update(bool auto_start_flag,bool field_pick,bool change_button) {
	/*	if (Time::GetMillisec()>3000) {
			auto_start_flag = true;
		}
		*/
		if (change_button) {
			buttondata = !buttondata;
		}
		if (auto_start_flag) {
			if (field_pick) {//フィールドによって変える
				//if (buttondata) {//ボタンによって変える
				//}
				blueshoot();
			}
			else {
				redshoot();
			}
			next_Pos = next_line.calculatePointFromOrigin(auto_move.tar_dis());
		}
		else {
			//自動の実行が許可されてないときの文
			//自動が実行されていないとき
			//自動の経路をリセットする
			route_case = 0;
		}
		data.x_axis = (int32_t)Next_Pos().x;
		data.y_axis = (int32_t)Next_Pos().y;
		data.turn = (float)Next_Pos().z;
		data.rpm = (float)set_bottle_rpm;
		data.roller_angle = (int)set_bottle_angle;
		data.catapult_shoot = (bool)set_catapult_shoot;
		data.catapult_charge = (bool)set_catapult_charge;
		data.roller_shoot = (bool)set_bottle_shoot;
		data.roller_collect = (bool)set_bottle_collect;
		data.auto_end_flag = (bool)auto_end_flag;
		setdata();
	}

	Vec3 Next_Pos() {
		return Vec3{ next_Pos.x,next_Pos.y,auto_move_turn.tar_turn() };
	}
	SendData SetData() {
		return data;
	}
	void setdata() {
		//自動の終了後に送るフラグ
		/*
		Print << auto_move_turn.tar_turn();
		Print << auto_move.all_time();
		Print << auto_move.read_ms();
		*/
		//Print << auto_move_turn.acc();
		//Print << auto_move_turn.distance();
		//Print << auto_move_turn.up();
		//Print << auto_move_turn.down();
		//Print << auto_move_turn.speed();
		//Print << auto_move_turn();
		
		
		Print << data.auto_end_flag;
		Print << data.catapult_charge;
		Print << data.catapult_shoot;
		Print << data.roller_angle;
		Print << data.roller_collect;
		Print << data.roller_shoot;
		Print << data.rpm;
		Print << data.turn;
		Print << data.x_axis;
		Print << data.y_axis;
		
	}



	void redshoot() {
		switch (route_case) {
		case 0://初めの経路の読み取りに失敗するため書く
			next_line = LineString{ {0,0} ,{0,0} };
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 1:
			//物の手前までくる
			start_s = 0;
			end_s = 0.8;
			next_line = redshootRoute1;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(-45,auto_move.all_time(),auto_move.read_ms());
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 2:
			//物をつかむところまでくる
			start_s = 0.8;
			end_s = 0;
			next_line = redshootRoute2;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(-45, auto_move.all_time(), auto_move.read_ms());
			move_time = Time::GetMillisec();
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 3:
			//アームを閉じる
			//カタパルトを上げる
			set_catapult_charge = true;
			set_bottle_collect = true;
			if (Time::GetMillisec() - move_time > 1000) {
				//機構が閉じるまで待つために一秒待機する
				route_case++;
				move_time = Time::GetMillisec();
			}
			break;
		case 4:
			//物をつかんで発射位置まで移動する
			//発射についての設定は走っている途中にする
			set_bottle_rpm = 8;
			set_bottle_angle = 55;
			start_s = 0;
			end_s = 0;
			next_line = redshootRoute3;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(45, auto_move.all_time(), auto_move.read_ms());
			move_time = Time::GetMillisec();
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 5:
			//物を発射する
			//55度に向いて
			//スピードは7m/s
			set_bottle_shoot = true;
			set_catapult_shoot = true;
			if (Time::GetMillisec() - move_time > 1500) {
				//機構が閉じるまで待つために一秒待機する
				route_case++;
				move_time = Time::GetMillisec();
			}
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
			next_line = redshootRoute4;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(-45, auto_move.all_time(), auto_move.read_ms());
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 7:
			//回収物をつかむ場所まで移動する
			start_s = 0;
			end_s = 0;
			next_line = redshootRoute5;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(-45, auto_move.all_time(), auto_move.read_ms());
			move_time = Time::GetMillisec();
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 8:
			//ボトルをつかむ
			//カタパルトを上げる
			set_catapult_charge = true;
			set_bottle_collect = true;
			if (Time::GetMillisec() - move_time > 1000) {
				//機構が閉じるまで待つために一秒待機する
				route_case++;
				move_time = Time::GetMillisec();
			}
			break;
		case 9:
			//回収物をつかんで発射位置まで移動する
			//発射についての設定は走っている途中にする
			set_bottle_rpm = 8;
			set_bottle_angle = 55;
			start_s = 0;
			end_s = 0;
			next_line = redshootRoute6;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(45, auto_move.all_time(), auto_move.read_ms());
			move_time = Time::GetMillisec();
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 10:
			//回収物を発射する
			//55度に向いて
			//スピードは8m/s
			set_bottle_shoot = true;
			set_catapult_shoot = true;
			if (Time::GetMillisec() - move_time > 1500) {
				//機構が閉じるまで待つために一秒待機する
				route_case++;
				move_time = Time::GetMillisec();
			}
			break;
			//二回発射したら自動の終了
			//自動モードを切るために終了フラグを送る
		case 11:
			//情報リセットのためのケース
			set_bottle_rpm = 0;
			auto_end_flag = true;
			set_bottle_shoot = false;
			set_catapult_shoot = false;
			set_catapult_charge = false;
			set_bottle_collect = false;
			auto_end_flag = true;//自動終了のフラグ送信
			break;
		}
	}
	void blueshoot() {
		switch (route_case) {
		case 0://初めの経路の読み取りに失敗するため書く
			next_line = LineString{ {0,0} ,{0,0} };
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 1:
			//物の手前までくる
			start_s = 0;
			end_s = 0.8;
			next_line = blueshootRoute1;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(135, auto_move.all_time(), auto_move.read_ms());
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 2:
			//物をつかむところまでくる
			start_s = 0.8;
			end_s = 0;
			next_line = blueshootRoute2;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(135, auto_move.all_time(), auto_move.read_ms());
			move_time = Time::GetMillisec();
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 3:
			//アームを閉じる
			//カタパルトを上げる
			set_catapult_charge = true;
			set_bottle_collect = true;
			if (Time::GetMillisec() - move_time > 1000) {
				//機構が閉じるまで待つために一秒待機する
				route_case++;
				move_time = Time::GetMillisec();
			}
			break;
		case 4:
			//物をつかんで発射位置まで移動する
			//発射についての設定は走っている途中にする
			set_bottle_rpm = 8;
			set_bottle_angle = 55;
			start_s = 0;
			end_s = 0;
			next_line = blueshootRoute3;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(45, auto_move.all_time(), auto_move.read_ms());
			move_time = Time::GetMillisec();
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 5:
			//物を発射する
			//55度に向いて
			//スピードは7m/s
			set_bottle_shoot = true;
			set_catapult_shoot = true;
			if (Time::GetMillisec() - move_time > 1500) {
				//機構が閉じるまで待つために一秒待機する
				route_case++;
				move_time = Time::GetMillisec();
			}
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
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(135, auto_move.all_time(), auto_move.read_ms());
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 7:
			//回収物をつかむ場所まで移動する
			start_s = 0;
			end_s = 0;
			next_line = blueshootRoute5;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(135, auto_move.all_time(), auto_move.read_ms());
			move_time = Time::GetMillisec();
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 8:
			//ボトルをつかむ
			//カタパルトを上げる
			set_catapult_charge = true;
			set_bottle_collect = true;
			if (Time::GetMillisec() - move_time > 1000) {
				//機構が閉じるまで待つために一秒待機する
				route_case++;
				move_time = Time::GetMillisec();
			}
			break;
		case 9:
			//回収物をつかんで発射位置まで移動する
			//発射についての設定は走っている途中にする
			set_bottle_rpm = 8;
			set_bottle_angle = 55;
			start_s = 0;
			end_s = 0;
			next_line = blueshootRoute6;
			auto_move.calculation(next_line, start_s, end_s);
			auto_move_turn.calculation(45, auto_move.all_time(), auto_move.read_ms());
			move_time = Time::GetMillisec();
			if (auto_move.next_status())//今のケースの経路をしておわったら次のフラグへ
				route_case++;
			break;
		case 10:
			//回収物を発射する
			//55度に向いて
			//スピードは8m/s
			set_bottle_shoot = true;
			set_catapult_shoot = true;
			if (Time::GetMillisec() - move_time > 1500) {
				//機構が閉じるまで待つために一秒待機する
				route_case++;
				move_time = Time::GetMillisec();
			}
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
			auto_end_flag = true;//自動終了のフラグ送信
			break;
		}
	}

};
