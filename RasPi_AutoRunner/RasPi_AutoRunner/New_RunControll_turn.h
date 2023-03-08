#pragma once

#include <Siv3D.hpp>

/*加速の計算がおかしいから値の増え方が変だけど
* 今回はこれで行きます
*/


class New_RunControll_turn {
private:
	double target = 0;
	unsigned long times = 0;
	bool Stop_flag = false, Reset_flag = false, Timer_state = false;
	bool  next_state = true;
	double now_turn = 0;
	double dis_turn = 0;
	double target_acc = 0;
	double half = 0;
	double old_turn = 0;
	double up_t = 0, down_t = 0;
public:
	New_RunControll_turn(){}


	unsigned long millis() {
		return (unsigned long)Time::GetMillisec();
	}
	double constrain(const double x, const double a, const double b) {
		if (x < a) {
			return a;
		}
		else if (b < x) {
			return b;
		}
		else
			return x;
	}
	double sq(double r) {
		return r * r;
	}
	void timer_start() {
		if (Timer_state == 0) {
			times = millis();
		}
		Timer_state = 1;
		Stop_flag = 0;
		Reset_flag = 0;
	}
	void timer_stop() {
		Timer_state = 0;
		if (Stop_flag == 0) {
			times = millis() - times;
		}
		Stop_flag = 1;
	}
	void timer_reset() {
		Reset_flag = 1;
	}
	unsigned long read_ms() {
		if (Reset_flag)return 0;
		if (Stop_flag)return times;
		return millis() - times;// ms
	}
	/// @brief 	台形制御のための時間計算
	/// @param target_turn 目標角度 度
	/// @param target_time 終わらせる目標時間 s
	/// @param now_time    実行させる今の時間　ms
	void calculation(double target_turn,double target_time,double now_time) {
		//前回の線の終わりと今回の線の初めの位置が同じとき
		//時間の計測を行う

		dis_turn = target_turn - now_turn;
		//角度の差分を求める

		 target_acc = (4 * dis_turn) / sq(target_time);
		//加速度を求める

		 half = target_time * 0.5;//s
		 up_t = constrain(now_time * 0.001, 0.0, half);
		down_t = constrain(now_time * 0.001 - half, 0.0, half);
		target =( 0.5 * target_acc * sq(up_t))+((target_acc* sq(down_t))-(0.5 * target_acc * sq(down_t)))+old_turn;
		//座標の更新をするところ
		//毎周期ごとに積算せずに最初から計算

		if (abs(dis_turn)<= abs(target)) {
			
			next_state = true;
			now_turn = target;
			old_turn = target;
		}
		else {
			next_state = false;
		}
	}
	/// @brief 目標角度を返す
	/// @return 目標角度
	double tar_turn() {
		return target;
	}
	double acc() {
		return target_acc;
	}
	double distance() {
		return dis_turn;
	}
	double up() {
		return up_t;
	}
	double down() {
		return down_t;
	}
};
extern New_RunControll_turn auto_move_turn;
