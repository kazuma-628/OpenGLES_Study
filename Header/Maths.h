#ifndef MATHS_H
#define MATHS_H

//include定義
#include "Common.h"

class Math
{

public:
	//コンストラクタ
	Math();

	//デストラクタ
	~Math();

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ベクトルの長さを求める
	*	引数
	*	　p_Vector		：[I/ ]　ベクトル
	*	戻り値
	*	　正常終了		：ベクトルの長さ
	*	　異常終了		：0.0
	*-------------------------------------------------------------------------------*/
	static float Length(Vec3 &p_Vector);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ベクトルを正規化する
	*	引数
	*	　p_Vector		：[I/ ]　ベクトル
	*	戻り値
	*	　正常終了		：正規化されたベクトル
	*	　異常終了		：全要素[0.0]
	*-------------------------------------------------------------------------------*/
	static Vec3 Normalize(Vec3 &p_Vector);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ベクトルの内積を求める
	*	引数
	*	　p_Vector1		：[I/ ]　ベクトル1
	*	　p_Vector2		：[I/ ]　ベクトル2
	*	戻り値
	*	　正常終了		：内積
	*	　異常終了		：0.0
	*-------------------------------------------------------------------------------*/
	static float Dot(Vec3 &p_Vector1, Vec3 &p_Vector2);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　ベクトルの外積を求める
	*	引数
	*	　p_Vector1		：[I/ ]　ベクトル1
	*	　p_Vector2		：[I/ ]　ベクトル2
	*	戻り値
	*	　正常終了		：外積
	*	　異常終了		：全要素[0.0]
	*-------------------------------------------------------------------------------*/
	static Vec3 Cross(Vec3 &p_Vector1, Vec3 &p_Vector2);

	/*-------------------------------------------------------------------------------
	*	関数説明
	*	　3要素の頂点で作られたポリゴンから法線を計算する
	*	引数
	*	　p_Vector1		：[I/ ]　ベクトル1
	*	　p_Vector2		：[I/ ]　ベクトル2
	*	　p_Vector3		：[I/ ]　ベクトル3
	*	　※下図のように反時計回りのベクトルで入力してください（正の値が取れます）
	*				 １
	*				／＼
	*			　／　　＼
	*			／　　　　＼
	*		　２￣￣￣￣￣￣３
	*	戻り値
	*	　正常終了		：正規化されたベクトル
	*	　異常終了		：全要素[0.0]
	*-------------------------------------------------------------------------------*/
	static Vec3 Normal(Vec3 &p_Vector1, Vec3 &p_Vector2, Vec3 &p_Vector3);

private:


};
#endif