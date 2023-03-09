#pragma once

#include <Siv3D.hpp>

/*加速の計算がおかしいから値の増え方が変だけど
* 今回はこれで行きます
*/


class New_RunControll_turn {
private:
	double target = 0;
	double targetSingleton;
	unsigned long times = 0;
	bool Stop_flag = false, Reset_flag = false, Timer_state = false;
	bool  next_state = true;
	double now_turn = 0;
	double dis_turn = 0;
	double target_acc = 0;
	double half = 0;
	double old_turn = 0;
	double up_t = 0, down_t = 0;
	double target_speed_up = 0;
	double target_speed_down = 0;
public:
	New_RunControll_turn() {}


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
	void calculation(double target_turn, double target_time, double now_time) {
		//前回の線の終わりと今回の線の初めの位置が同じとき
		//時間の計測を行う

		dis_turn = target_turn - old_turn;
		//角度の差分を求める
		//旋回する量を求める

		target_acc = (4 * dis_turn) / sq(target_time);
		//加速度を求める 度/s^2

		const auto nowS = now_time * 0.001;
		const auto halfS = target_time * 0.5;

		// 時間算出
		up_t = constrain(nowS, 0.00, halfS);
		down_t = constrain(nowS - halfS, 0.00, halfS);

		// 速度算出
		target_speed_up = target_acc * up_t;
		target_speed_down = target_acc * down_t;//逆にならないといけない

		// 位置算出
		//const auto upX = target_acc * sq(up_t) * 0.5;
		//const auto downX = target_acc * (target_acc * halfS - target_speed_down);

		const auto limitV = target_acc * halfS;

		if (nowS <= halfS)
		{
			if (target_acc)
			{
				target = sq(target_speed_up)  // V^2 = 2ax を x につて式変形
					/ (2 * target_acc) + old_turn;
			}
			else {
				target = old_turn;
			}
		}
		else
		{
			if (target_acc)
			{
				target
					= target_acc * sq(halfS)
					+ sq(abs(target_speed_down - limitV)) / (2 * -target_acc) + old_turn;
			}
			else {
				target = old_turn;
			}
		}
		//座標の更新をするところ
		//毎周期ごとに積算せずに最初から計算

		if (dis_turn == target) {
			next_state = true;
			old_turn = target;
		}
		else {
			next_state = false;
		}
	}

	void reset() {
		old_turn = 0;
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
	double speed() {
		return target_speed_down;
	}
};
extern New_RunControll_turn auto_move_turn;
