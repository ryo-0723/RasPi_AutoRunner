#include "display_manager.h"
#include <Siv3D.hpp>

Screen_Resizer::Screen_Resizer(const Vec2& Virtual_Size, ScreenStyle Style)
	:Virtual_Size(Virtual_Size), Style(Style) {
	defaultKeepPosY = Scene::Size().y;
	//最初に表示されたy軸の大きさを最大として、スクリーンをリサイズする
	//***これより先にウィンドウのの初期表示サイズを設定しておくこと
}
/*
 *仮想スクリーンの大きさを指定する
 *第二引数は画面タイプの設定を行う
*/

void Screen_Resizer::Resize_Update(const RectF& Screen) {
	this->Screen = Screen;
	Scalling = Screen.size / Virtual_Size;
	//仮想ウィンドウと実ウィンドウの大きさの比率を求める
	switch (Style) {
	case ScreenStyle::Left:
		Scall.x = Scall.y = Scalling.x < Scalling.y ? Scalling.x : Scalling.y;
		//x,yのうち、より縮小しなければ画面に入らないほうの縮小率を求める
		Offset_Pos.x = Screen.pos.x;
		Offset_Pos.y = Screen.pos.y + (Screen.size.y - Virtual_Size.y * Scall.y) * 0.5;
		//左上の座標原点を調整する
		break;
	case ScreenStyle::Center:
		Scall.x = Scall.y = Scalling.x < Scalling.y ? Scalling.x : Scalling.y;
		Offset_Pos = Screen.pos + (Screen.size - Virtual_Size * Scall) * 0.5;
		break;
	case ScreenStyle::Right:
		Scall.x = Scall.y = Scalling.x < Scalling.y ? Scalling.x : Scalling.y;
		Offset_Pos.x = Screen.pos.x + (Screen.size.x - Virtual_Size.x * Scall.x);
		Offset_Pos.y = Screen.pos.y + (Screen.size.y - Virtual_Size.y * Scall.y) * 0.5;
		break;
	case  ScreenStyle::Keep:
		Scall.x = Scalling.x;
		Scall.y = defaultKeepPosY / Virtual_Size.y;
		Offset_Pos.x = Screen.pos.x;
		Offset_Pos.y = Screen.pos.y;
		break;
	}
	//pos*scallは実ウィンドウ内での仮想ウィンドウの大きさ
}



Vec2 Screen_Resizer::GetWindow_Size() {
	return Screen.size * Scall;
}

Vec2 Screen_Resizer::Get_Pos() {
	return Offset_Pos;
}

/// @brief ウィンドウの表示タイプの変更
/// @param Style 表示タイプ
void Screen_Resizer::SetStyle(ScreenStyle r) {
	Style = r;
}

/// @brief 実ウィンドウでの座標になるよう計算
/// @param Pos 仮想ウィンドウでの座標
Vec2  Screen_Resizer::Cal_Pos(const Vec2& Pos) const {//左下からの座標にします！！←後回しかな
	return Pos * Scall + Offset_Pos;
}

/// @brief 実ウィンドウでの大きさになるように計算
/// @param Size 仮想ウィンドウでの大きさ
Vec2 Screen_Resizer::Cal_Size(const Vec2& Size) const {
	return  Size * Scall;
}

/// @brief 実ウィンドウでの大きさになるように計算
/// @param Size 仮想ウィンドウでの大きさ
double Screen_Resizer::Cal_Size(const double& Size)const {
	return Size * Scall.x;
}

Line Screen_Resizer::toReal(const Line& Raw) const {
	return Line{ Cal_Pos(Raw.begin),Cal_Pos(Raw.end) };
}

RectF Screen_Resizer::toReal(const RectF& Raw) const {
	return RectF{ Cal_Pos(Raw.pos),Cal_Size(Raw.size) };
}

RoundRect Screen_Resizer::toReal(const RoundRect& Raw) const {
	return RoundRect{ Cal_Pos(Raw.rect.pos),Cal_Size(Raw.rect.size),Cal_Size(Raw.r)};
}

Circle Screen_Resizer::toReal(const Circle& Raw) const {
	return Circle{ Cal_Pos(Raw.center),Cal_Size(Raw.r) };
}

Triangle Screen_Resizer::toReal(const Triangle& Raw)const {
	return Triangle{ Cal_Pos(Raw.p0),Cal_Pos(Raw.p1),Cal_Pos(Raw.p2) };
}

Bezier2 Screen_Resizer::toReal(const Bezier2& Raw)const {
	return Bezier2{ Cal_Pos(Raw.p0),Cal_Pos(Raw.p1),Cal_Pos(Raw.p2) };
}

Bezier3 Screen_Resizer::toReal(const Bezier3& Raw)const {
	return Bezier3{ Cal_Pos(Raw.p0),Cal_Pos(Raw.p1),Cal_Pos(Raw.p2),Cal_Pos(Raw.p3) };
}
