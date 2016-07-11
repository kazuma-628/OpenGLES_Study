#include "Utility.h"

//コンストラクタ
Utility::Utility()
{

}

//デストラクタ
Utility::~Utility()
{

}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ベクトルの長さを求める
*	引数
*	　p_Vector		：[I/ ]　ベクトル
*	戻り値
*	　正常終了		：ベクトルの長さ
*	　以上終了		：0.0		
*-------------------------------------------------------------------------------*/
float Utility::Length(Vec3 *p_Vector)
{
	float length = 0.0f;	//ベクトルの長さ

	//引数チェック
	if (NULL == p_Vector)
	{
		ERROR_MESSAGE("引数エラー");
		return length;
	}
	
	//計算しやすいように代入（誤差を少なくするために[double]で計算）
	double x = (double)(p_Vector->x);
	double y = (double)(p_Vector->y);
	double z = (double)(p_Vector->z);

	//ベクトルの長さを求める
	length = (float)sqrt(x * x + y * y + z * z);

	return length;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ベクトルを正規化する
*	引数
*	　p_Vector		：[I/ ]　ベクトル
*	戻り値
*	　正常終了		：正規化されたベクトル
*	　以上終了		：全要素[0.0]
*-------------------------------------------------------------------------------*/
Vec3 Utility::Normalize(Vec3 *p_Vector)
{
	Vec3 normalize = { 0.0f };		//正規化されたベクトル

	//引数チェック
	if (NULL == p_Vector)
	{
		ERROR_MESSAGE("引数エラー");
		return normalize;
	}

	//計算しやすいように代入（誤差を少なくするために[double]で計算）
	double x = (double)(p_Vector->x);
	double y = (double)(p_Vector->y);
	double z = (double)(p_Vector->z);

	//ベクトルの長さを求める
	double length = sqrt(x * x + y * y + z * z);

	//ベクトルの長さが[0]だと0除算になるのでエラー
	if (length < (1e-6))
	{
		ERROR_MESSAGE("計算エラー");
		return normalize;
	}

	//正規化する
	length = 1.0 / length;
	x *= length;
	y *= length;
	z *= length;

	//戻り値を設定
	normalize.x = (float)x;
	normalize.y = (float)y;
	normalize.z = (float)z;

	return normalize;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ベクトルの内積を求める
*	引数
*	　p_Vector1		：[I/ ]　ベクトル1
*	　p_Vector2		：[I/ ]　ベクトル2
*	戻り値
*	　正常終了		：内積
*	　以上終了		：0.0
*-------------------------------------------------------------------------------*/
float Utility::Dot(Vec3 *p_Vector1, Vec3 *p_Vector2)
{
	float dot = 0.0f; //内積

	//引数チェック
	if (NULL == p_Vector1 || NULL == p_Vector2)
	{
		ERROR_MESSAGE("引数エラー");
		return dot;
	}

	//計算しやすいように代入（誤差を少なくするために[double]で計算）
	double x1 = (double)(p_Vector1->x);
	double y1 = (double)(p_Vector1->y);
	double z1 = (double)(p_Vector1->z);

	double x2 = (double)(p_Vector2->x);
	double y2 = (double)(p_Vector2->y);
	double z2 = (double)(p_Vector2->z);

	//内積を求める
	dot = (float)((x1 * x2) + (y1 * y2) + (z1 * z2));
	
	return dot;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　ベクトルの外積を求める
*	引数
*	　p_Vector1		：[I/ ]　ベクトル1
*	　p_Vector2		：[I/ ]　ベクトル2
*	戻り値
*	　正常終了		：正規化されたベクトル
*	　以上終了		：全要素[0.0]
*-------------------------------------------------------------------------------*/
Vec3 Utility::Cross(Vec3 *p_Vector1, Vec3 *p_Vector2)
{
	Vec3 cross = { 0.0f };		//正規化されたベクトル

	//引数チェック
	if (NULL == p_Vector1 || NULL == p_Vector2)
	{
		ERROR_MESSAGE("引数エラー");
		return cross;
	}

	//計算しやすいように代入（誤差を少なくするために[double]で計算）
	double x1 = (double)(p_Vector1->x);
	double y1 = (double)(p_Vector1->y);
	double z1 = (double)(p_Vector1->z);

	double x2 = (double)(p_Vector2->x);
	double y2 = (double)(p_Vector2->y);
	double z2 = (double)(p_Vector2->z);

	//外積を求める
	cross.x = (float)(y1 * z2 - z1 * y2);
	cross.y = (float)(z1 * x2 - x1 * z2);
	cross.z = (float)(x1 * y2 - y1 * x2);

	return cross;
}


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
*	　以上終了		：全要素[0.0]
*-------------------------------------------------------------------------------*/
Vec3 Utility::Normal(Vec3 *p_Vector1, Vec3 *p_Vector2, Vec3 *p_Vector3)
{
	Vec3 normal = { 0.0f };		//正規化されたベクトル

	//引数チェック
	if (NULL == p_Vector1 || NULL == p_Vector2 || NULL == p_Vector3)
	{
		ERROR_MESSAGE("引数エラー");
		return normal;
	}

	//計算しやすいように代入（誤差を少なくするために[double]で計算）
	double x1 = (double)(p_Vector1->x);
	double y1 = (double)(p_Vector1->y);
	double z1 = (double)(p_Vector1->z);

	double x2 = (double)(p_Vector2->x);
	double y2 = (double)(p_Vector2->y);
	double z2 = (double)(p_Vector2->z);

	double x3 = (double)(p_Vector3->x);
	double y3 = (double)(p_Vector3->y);
	double z3 = (double)(p_Vector3->z);

	//ベクトル[1][2] と ベクトル[2][3] を求める
	Vec3 tmp_normal1 = { float(x2 - x1), float(y2 - y1), float(z2 - z1) };
	Vec3 tmp_normal2 = { float(x3 - x2), float(y3 - y2), float(z3 - z2) };

	//ベクトル[1][2] と ベクトル[2][3]の外積を求める
	normal = Cross(&tmp_normal1, &tmp_normal2);

	//正規化して単位ベクトルにする
	normal = Normalize(&normal);

	return normal;
}