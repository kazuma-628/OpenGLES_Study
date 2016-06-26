#include "Matrix.h"

//コンストラクタ
Matrix::Matrix()
{
	//単位行列を生成する（初期化する）
	Identity();
}

//デストラクタ
Matrix::~Matrix()
{
	
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　演算子のオーバーロード定義
*-------------------------------------------------------------------------------*/

//マトリクス同士の乗算
Matrix operator*(Matrix &p_left, Matrix &p_right)
{
	//参考用のメモ
	//[ 0][ 1][ 2][ 3]
	//[ 4][ 5][ 6][ 7]
	//[ 8][ 9][10][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//行列の乗算（OpenGLは行ベクトルではなく列ベクトルなことに注意、乗算は一般的な行列の乗算と違う）
	for (int i = 0; i < 4; i++)
	{
		t_matrix.m_val[i]		= p_left.m_val[i] * p_right.m_val[0]  + p_left.m_val[i + 4] * p_right.m_val[1]
									+ p_left.m_val[i + 8] * p_right.m_val[2] + p_left.m_val[i + 12] * p_right.m_val[3];
		t_matrix.m_val[i + 4]	= p_left.m_val[i] * p_right.m_val[4]  + p_left.m_val[i + 4] * p_right.m_val[5] 
									+ p_left.m_val[i + 8] * p_right.m_val[6] + p_left.m_val[i + 12] * p_right.m_val[7];
		t_matrix.m_val[i + 8]	= p_left.m_val[i] * p_right.m_val[8]  + p_left.m_val[i + 4] * p_right.m_val[9]
									+ p_left.m_val[i + 8] * p_right.m_val[10] + p_left.m_val[i + 12] * p_right.m_val[11];
		t_matrix.m_val[i + 12]	= p_left.m_val[i] * p_right.m_val[12] + p_left.m_val[i + 4] * p_right.m_val[13]
									+ p_left.m_val[i + 8] * p_right.m_val[14] + p_left.m_val[i + 12] * p_right.m_val[15];
	}
	return t_matrix;
}

//マトリクス同士の乗算
Matrix operator*(Matrix &p_left, GLfloat *p_right)
{
	Matrix t_matrix;

	t_matrix.SetMatrix(p_right);

	t_matrix = p_left * t_matrix;

	return t_matrix;
}

//マトリクス同士の乗算
Matrix operator*(GLfloat *p_left, Matrix &p_right)
{
	Matrix t_matrix;

	t_matrix.SetMatrix(p_left);

	t_matrix = t_matrix * p_right;

	return t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　単位行列を生成する
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Matrix::Identity()
{	
	//参考用のメモ
	//[●][ 1][ 2][ 3]
	//[ 4][●][ 6][ 7]
	//[ 8][ 9][●][11]
	//[12][13][14][●]

	//行列初期化
	memset(m_val, 0, sizeof(m_val));

	//単位行列設定する
	m_val[0] = 1.0f;
	m_val[5] = 1.0f;
	m_val[10] = 1.0f;
	m_val[15] = 1.0f;

}

/*-------------------------------------------------------------------------------
*	関数説明
*	　移動行列を適用する
*	引数
*	　p_x	：[I/ ]　X 座標の移動量
*	　p_y	：[I/ ]　Y 座標の移動量
*	　p_z	：[I/ ]　Z 座標の移動量
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Matrix::Translate(const GLfloat p_x, const GLfloat p_y, const GLfloat p_z)
{
	//参考用のメモ
	//[ 0][ 1][ 2][ 3]
	//[ 4][ 5][ 6][ 7]
	//[ 8][ 9][10][11]
	//[●][●][●][15]

	Matrix t_matrix;

	//移動行列を適用
	t_matrix.m_val[12] = p_x;
	t_matrix.m_val[13] = p_y;
	t_matrix.m_val[14] = p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　回転行列を適用する
*	引数
*	　p_x	：[I/ ]　X 座標の倍率
*	　p_y	：[I/ ]　Y 座標の倍率
*	　p_z	：[I/ ]　Z 座標の倍率
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Matrix::Scale(const GLfloat p_x, const GLfloat p_y, const GLfloat p_z)
{
	//参考用のメモ
	//[●][ 1][ 2][ 3]
	//[ 4][●][ 6][ 7]
	//[ 8][ 9][●][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//拡大縮小行列を適用
	t_matrix.m_val[0] = p_x;
	t_matrix.m_val[5] = p_y;
	t_matrix.m_val[10] =  p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　回転行列を適用する
*	引数
*	　p_rotate	：[I/ ]　回転角度（360度系）
*	　下記、回転軸となる正規化された方向ベクトルを設定する
*	　p_x		：[I/ ]　X 成分（X 成分に効かせる場合は 1.0 を指定）
*	　p_y		：[I/ ]　Y 成分（Y 成分に効かせる場合は 1.0 を指定）
*	　p_z		：[I/ ]　Z 成分（Z 成分に効かせる場合は 1.0 を指定）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Matrix::Rotate(const GLfloat p_rotate, const GLfloat p_x, const GLfloat p_y, const GLfloat p_z)
{
	//参考用のメモ
	//[●][●][●][ 3]
	//[●][●][●][ 7]
	//[●][●][●][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//回転行列を適用
	GLfloat t_c = cosf(DEGREE_TO_RADIAN(p_rotate));
	GLfloat t_s = sinf(DEGREE_TO_RADIAN(p_rotate));

	t_matrix.m_val[0] = (p_x * p_x) * (1.0f - t_c) + t_c;
	t_matrix.m_val[1] = (p_x * p_y) * (1.0f - t_c) - p_z * t_s;
	t_matrix.m_val[2] = (p_x * p_z) * (1.0f - t_c) + p_y * t_s;

	t_matrix.m_val[4] = (p_y * p_x) * (1.0f - t_c) + p_z * t_s;
	t_matrix.m_val[5] = (p_y * p_y) * (1.0f - t_c) + t_c;
	t_matrix.m_val[6] = (p_y * p_z) * (1.0f - t_c) - p_x * t_s;

	t_matrix.m_val[8] = (p_z * p_x) * (1.0f - t_c) - p_y * t_s;
	t_matrix.m_val[9] = (p_z * p_y) * (1.0f - t_c) + p_x * t_s;
	t_matrix.m_val[10] = (p_z * p_z) * (1.0f - t_c) + t_c;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　透視投影変換行列を適用する
*	引数
*	　p_left	：[I/ ]　近くの面(p_near面)の左側までの距離
*	　p_right	：[I/ ]　近くの面(p_near面)の右側までの距離
*	　p_bottom	：[I/ ]　近くの面(p_near面)の下側までの距離
*	　p_top		：[I/ ]　近くの面(p_near面)の上側までの距離
*	　p_near	：[I/ ]　近くの面までの距離
*	　p_far		：[I/ ]　遠くの面までの距離
*
*	　図は下記URLの「透視投影変換」項目参照
*	　http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20090829
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Matrix::Perspective(float p_left, float p_right,
						 float p_bottom, float p_top,
						 float p_near, float p_far)
{
	//参考用のメモ
	//[ 0][ 1][ 2][ 3]
	//[ 4][ 5][ 6][ 7]
	//[ 8][ 9][10][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//透視投影変換行列を適用する
	float dx = p_right - p_left;
	float dy = p_top - p_bottom;
	float dz = p_far - p_near;

	if (0 == dx || 0 == dy || 0 == dz)
	{
		printf("デバッグ情報\n");
		printf("p_right = %f, p_left = %f, p_top = %f, p_bottom = %f, p_far = %f, p_near = %f\n",
			p_right, p_left, p_top, p_bottom, p_far, p_near);
		ERROR_MESSAGE("透視投影変換行列の引数異常です");
	}
	
	
	t_matrix.m_val[0] = 2.0f * p_near / dx;
	t_matrix.m_val[5] = 2.0f * p_near / dy;
	t_matrix.m_val[8] = (p_right + p_left) / dx;
	t_matrix.m_val[9] = (p_top + p_bottom) / dy;
	t_matrix.m_val[10] = -(p_far + p_near) / dz;
	t_matrix.m_val[11] = -1.0f;
	t_matrix.m_val[14] = -2.0f * p_far * p_near / dz;
	t_matrix.m_val[15] = 0.0f;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　透視投影変換行列を適応する
*	　一つ上にある「Perspective」関数でも行列を作成することが可能です（オーバーロードしてあります）
*	　引数が違うので、使いやすい方や用途に合わせて使用すること（結果的には同じことができます）
*	引数
*	　p_near		：[I/ ]　近くの面までの距離
*	　p_far			：[I/ ]　遠くの面までの距離
*	　p_fovY_deg	：[I/ ]　カメラの Y方向の画角
*	　p_aspect		：[I/ ]　描画先の画面のアスペクト比（幅 ÷ 高さ）
*
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Matrix::Perspective(float p_near, float p_far,
						float p_fovY_degree, float p_aspect)
{
	Matrix t_matrix;

	GLfloat t_f = 1.0f / (tanf(DEGREE_TO_RADIAN(p_fovY_degree)) / 2.0f);

	t_matrix.m_val[0] = t_f / p_aspect;
	t_matrix.m_val[5] = t_f;
	t_matrix.m_val[10] = (p_far + p_near) / (p_near - p_far);
	t_matrix.m_val[11] = -1;
	t_matrix.m_val[14] = (2.0f * p_far * p_near) / (p_near - p_far);

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　逆行列を求める
*	引数
*	　なし
*	戻り値
*	　逆行列
*-------------------------------------------------------------------------------*/
Matrix Matrix::Inverse() const
{
	Matrix t_matrix;


	return t_matrix;
}
