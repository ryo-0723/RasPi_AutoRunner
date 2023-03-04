#pragma once
#include <Siv3D.hpp>
#include "ScreenStyle.h"
/*
開発開始　12月６日
開発終了日　12月14日
開発者　藤本涼
OpenSiv3D用の画面の縮小拡大を自動的に行うもの
*/

class Screen_Resizer {
private:
	Vec2 Virtual_Size;
	ScreenStyle Style;
	Vec2 Offset_Pos = {}, Scalling = {}, Scall = {};
	RectF Screen = {};
	int defaultKeepPosY;
public:
	Screen_Resizer(const Vec2& Virtual_Size
		, ScreenStyle Style = ScreenStyle::Center);

	/// @brief 描画領域内に表示させるスクリーンのリサイズ
	/// @param Screen 描画させたい領域
	void Resize_Update(const RectF& Screen);

	Vec2 GetWindow_Size();

	Vec2 Get_Pos();

	Vec2 GetNowSize() {
		return Cal_Size(defaultKeepPosY *(Virtual_Size / defaultKeepPosY)*(Scene::Size() / Virtual_Size));
	}
	/// @brief ウィンドウの表示タイプの変更
	/// @param Style 表示タイプ
	void SetStyle(ScreenStyle r);

	/// @brief 実ウィンドウでの座標になるよう計算
	/// @param Pos 仮想ウィンドウでの座標
	Vec2  Cal_Pos(const Vec2& Pos) const;
	//左下からの座標にします！！←後回しかな

	/// @brief 実ウィンドウでの大きさになるように計算
	/// @param Size 仮想ウィンドウでの大きさ
	Vec2 Cal_Size(const Vec2& Size) const;

	/// @brief 実ウィンドウでの大きさになるように計算
	/// @param Size 仮想ウィンドウでの大きさ
	double Cal_Size(const double& Size)const;


	Line toReal(const Line& Raw) const;

	RectF toReal(const RectF& Raw) const;

	RoundRect toReal(const RoundRect& Raw) const;

	Circle toReal(const Circle& Raw) const;

	Triangle toReal(const Triangle& Raw)const;

	Bezier2 toReal(const Bezier2& Raw)const;

	Bezier3 toReal(const Bezier3& Raw)const;

};
extern Screen_Resizer display1;
