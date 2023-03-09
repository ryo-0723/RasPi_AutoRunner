#pragma once

#include <Siv3D.hpp>

class New_RunControll
{
private:
	double end_s = 0, start_s = 0, max_s = 0, limit_s = 0;
	double up_t = 0, down_t = 0, max_power_t = 0, all_t = 0;
	double L1 = 0, L3 = 0;
	double kakudo = 0;
	double acc_, acc;
	double target = 0;
	unsigned long times = 0;
	bool Stop_flag = false, Reset_flag = false, Timer_state = false;
	bool  next_state = true;
	double distance = 0;
	LineString oldline{ {0,0},{0,0} };
public:
	New_RunControll(double acc, double max_s)
	:acc(acc)
	,max_s(max_s){
		acc_ = 1.00 / acc;
	}

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

	/// @brief 台形制御のための時間計算
	/// @param line 台形制御する直線の構造体
	/// @param start_s 初めの速度
	/// @param end_s 終わりの速度
	void calculation(LineString &line,double start_s,double end_s) {
			//前回の線の終わりと今回の線の初めの位置が同じとき
			//時間の計測を行う
		if (oldline.back()==line.front()) {
			//線がつながっているからタイマースタート
			timer_reset();
			timer_start();
		}
		else {
			timer_stop();
		}

		 distance = line.calculateLength()/1000.00;
		//mに変換する
		up_t = (max_s - start_s) * acc_; //最高速度までの加速にかかる時間 /s
		down_t = (max_s - end_s) * acc_; //減速にかかる時間 /s
		L1 = start_s * up_t + acc * sq(up_t) * 0.5; //加速時における移動距離 /m
		L3 = end_s * down_t + acc * sq(down_t) * 0.5; //減速時における移動距離/m
		if (L1 + L3 > abs(distance)) {//台形ができなくなり、三角形になるときの制御
			limit_s = (2.00 * acc * abs(distance) + sq(start_s) + sq(end_s)) * 0.50;
			limit_s = sqrt(limit_s);
			up_t = (limit_s - start_s) * acc_;
			down_t = (limit_s - end_s) * acc_;
			all_t = up_t + down_t;
			max_power_t = 0.0;
		}
		else {//台形が作れる場合の制御 
			max_power_t = (abs(distance) - L1 - L3) / max_s; //最高速度での移動時間 /s
			all_t = up_t + down_t + max_power_t; //移動にかかる合計時間 / s
			limit_s = max_s;
		}

		double t = read_ms() * 0.001;//sにする
		double ut = constrain(t, 0.00, up_t);
		double dt = constrain(t - (up_t + max_power_t), 0.00, down_t);
		double target_ = acc * sq(ut) * 0.50 + start_s * ut
			+ max_s * constrain(t - up_t, 0.00, max_power_t)
			+ (-acc * sq(dt) * 0.50) + limit_s * dt;
		//座標の更新をするところ
		//毎周期ごとに積算せずに最初から計算

		target = target_ * 1000;
		//mで返ってくるためmmに変換する
		if (all_t <= t) {
			timer_stop();
			next_state = true;
			oldline = line;
		}
		else {
			next_state = false;
		}
	}

	void reset() {
		oldline = LineString{ {0,0},{0,0} };
	}
	bool next_status() {//今回の経路を巡行し終えたらtrueになる
		return next_state;
	}
	double tar_dis() {
		return target;
	}
	double move_time() {
		return read_ms();
	}
	double all_time() {
		return all_t;
	}
};
extern New_RunControll auto_move;
