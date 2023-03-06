#pragma once

#include <Siv3D.hpp>

constexpr RectF box{ 60,240,90,25 };
constexpr RoundRect Serial_box{1160,40,310,130,10};
constexpr RoundRect Feildpick{ 50,20,320,100,2 };
constexpr Circle SpeedMeter{300,1080,280};
constexpr Circle MoveTimer{ 890,1080,280 };
//constexpr Triangle Speedneedle{190,900,100 };
constexpr Triangle Speedneedle{ {184,900},{190,775},{196,900} };
constexpr RectF RobotPos_showFrame{ 1190,810,570,450 };
constexpr RoundRect TrajectoryImportFrame{ 20,70,570,27,2 };
//constexpr RectF trajectory_frame{ 20,100,740,660 };
constexpr RectF mechanism_state_frame{ 50,150,720,650 };
