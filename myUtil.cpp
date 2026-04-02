#include <GSgameLight.h>
#include "myUtil.h"

/// <summary>
/// 円と円が重なっているかを調べる
/// </summary>
/// <param name="x1">円1の中心x</param>
/// <param name="y1">円1の中心y</param>
/// <param name="radius1">円1の半径</param>
/// <param name="x2">円2の中心x</param>
/// <param name="y2">円2の中心y</param>
/// <param name="radius2">円2の半径</param>
/// <returns>重なっていれば1、重なっていなければ0を返却する</returns>
int CircleCircleIntersection(float x1, float y1, float radius1, float x2, float y2, float radius2)
{
	//(x1-x2)^2 + (y1 - y2)^2 < (半径1 + 半径2)^2
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
		<= ((radius1 + radius2) * (radius1 + radius2));

}

//ランダム値(int)
int RandomRange(int min, int max) {
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
//ランダム値(float)
float RandomRangef(float min, float max) {
	return min + (float)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

// 指定した範囲で乱数を返却する。
// 例えば1.5fを指定すると、-1.5～+1.5の範囲の値を返却する。
float RandomPlusMinus(float value) {
	return RandomRangef(-value, value);
}

/// 点から点への角度（ラジアン）を求める。
float PointToPointAngle(float fromX, float fromY, float toX, float toY)
{
	return (float)atan2(toY - fromY, toX - fromX);
}
