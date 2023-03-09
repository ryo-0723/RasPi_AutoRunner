#pragma once

#include <Siv3D.hpp>

constexpr RectF box{ 60,240,90,25 };
constexpr RoundRect Serial_box{1160,120,310,100,10};
constexpr RoundRect Feildpick{ 50,20,320,100,2 };
constexpr Circle SpeedMeter{300,1080,280};
constexpr Circle MoveTimer{ 890,1080,280 };
//constexpr Triangle Speedneedle{190,900,100 };
constexpr Triangle Speedneedle{ {184,900},{190,775},{196,900} };
constexpr RectF RobotPos_showFrame{ 1190,810,570,480 };
constexpr RoundRect TrajectoryImportFrame{ 20,70,570,27,2 };
//constexpr RectF trajectory_frame{ 20,100,740,660 };
constexpr RectF mechanism_state_frame{ 50,150,950,650 };
constexpr RectF portFrame{1100,250,650,550};
constexpr RoundRect ChengeRoute{600,20,280,100,10};

#pragma pack(push,1)
//visualstudioでのみのもの
struct ReadData {
	int32_t x_axis = 0;
	int32_t y_axis = 0;
	float turn = 0, rpm = 0, robot_speed = 0;
	int16_t roller_angle = 0;
	uint8_t catapult_shoot : 1;
	uint8_t catapult_charge : 1;
	uint8_t roller_shoot : 1;
	uint8_t roller_collect : 1;
	uint8_t auto_flag : 1;

};// __attribute__((__packed__));

struct SendData {
	int32_t x_axis = 0, y_axis = 0;
	float turn = 0, rpm = 0;
	int16_t roller_angle = 0;
	uint8_t catapult_shoot : 1;
	uint8_t catapult_charge : 1;
	uint8_t roller_shoot : 1;
	uint8_t roller_collect : 1;
	uint8_t auto_end_flag : 1;
}_;// _attribute__((__packed__));
#pragma pack(pop)
//visual studioでのみのもの
