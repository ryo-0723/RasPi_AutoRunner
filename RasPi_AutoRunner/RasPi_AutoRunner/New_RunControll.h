#pragma once

#include <Siv3D.hpp>

class New_RunControll {
private:
	double end_s = 0, start_s = 0, max_s = 0, limit_s = 0;
	double up_t = 0, down_t = 0, max_power_t = 0, all_t = 0;
	double L1 = 0, L3 = 0;
	double kakudo = 0;
	double acc_, acc;
	double target = 0, end_potion = 0;
	unsigned long times = 0;
	bool Stop_flag = false, Reset_flag = false, Timer_state = false;
	bool cal_state = false, next_state = true;
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


	void calculation(LineString line,double start_s,double end_s) {
		if (cal_state) return;
		double distance = line.calculateLength();
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
		cal_state = true;
	}
	void tar_point() {
		//  X=Vot+(1/2)*at^2;
		if (cal_state) {
			timer_start();//タイマーを開始する←何度呼び出しても一度だけ実行される
		}
		double t = read_ms() * 0.001;
		double ut = constrain(t, 0.00, up_t);
		double dt = constrain(t - (up_t + max_power_t), 0.00, down_t);
		double target_ = acc * sq(ut) * 0.50 + start_s * ut
			+ max_s * constrain(t - up_t, 0.00, max_power_t)
			+ (-acc * sq(dt) * 0.50) + limit_s * dt;
		//座標の更新をするところ
		//毎周期ごとに積算せずに最初から計算
		target = target_ + end_potion;

		if (all_t <= t) {
			end_potion = target;
			timer_stop();
			timer_reset();
			cal_state = false;
			next_state = true;
		}
	}
	bool next_status() {//今回の経路を巡行し終えたらtrueになる
		return next_state;
	}
	void set_next_status() {//次の経路をセットしたら必ず行う
		next_state = false;
	}
	double end_dis() {
		return end_potion;
	}
	double tar_dis() {
		return target;
	}
	double all_time() {
		return all_t;
	}
};
extern New_RunControll auto_move;
