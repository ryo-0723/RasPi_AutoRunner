#pragma once

#include <Siv3D.hpp>

LineString blueshootRoute1{
	{0,0},{-650,3150} ,{-1062,3150} };
//スタートから一回目の回収手前まで


LineString blueshootRoute2{
	{-1062,3150},{-1362,3150} };
//回収までのところに移動

LineString blueshootRoute3{
	{-1362,3150},{-1062,3150}
};
//発射位置に移動

LineString blueshootRoute4{
	{-1062,3150},{-1062,2750} };
//次の回収のためにy軸だけ移動する

LineString blueshootRoute5{
	{-1062,2750},{-1362,2750} };
//次の回収位置に移動

LineString blueshootRoute6{
	{-1362,2750},{-1062,2750}};
//次の発射位置まで移動

//発射の自動は終了





LineString redshootRoute1{
	{0,0},{-650,3150} ,{-1062,3150} };
//スタートから一回目の回収手前まで

LineString redshootRoute2{
	{-1062,3150},{-1362,3150} };
//回収までのところに移動

LineString redshootRoute3{
	{-1362,3150},{-1062,3150}
};
//発射位置に移動

LineString redshootRoute4{
	{-1062,3150},{-1062,2750} };
//次の回収のためにy軸だけ移動する

LineString redshootRoute5{
	{-1062,2750},{-1362,2750} };
//次の回収位置に移動

LineString redshootRoute6{
	{-1362,2750},{-1062,2750} };
//次の発射位置まで移動

//発射の自動は終了


