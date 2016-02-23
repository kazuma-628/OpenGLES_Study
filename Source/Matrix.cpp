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
Matrix operator*(Matrix& p_left, Matrix& p_right)
{
	//参考用のメモ
	//[ 0][ 1][ 2][ 3]
	//[ 4][ 5][ 6][ 7]
	//[ 8][ 9][10][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//行列の乗算
	t_matrix.m_val[0] = p_left.m_val[0] * p_right.m_val[0] + p_left.m_val[1] * p_right.m_val[4] + p_left.m_val[2] * p_right.m_val[8] + p_left.m_val[3] * p_right.m_val[12];
	t_matrix.m_val[1] = p_left.m_val[0] * p_right.m_val[1] + p_left.m_val[1] * p_right.m_val[5] + p_left.m_val[2] * p_right.m_val[9] + p_left.m_val[3] * p_right.m_val[13];
	t_matrix.m_val[2] = p_left.m_val[0] * p_right.m_val[2] + p_left.m_val[1] * p_right.m_val[6] + p_left.m_val[2] * p_right.m_val[10] + p_left.m_val[3] * p_right.m_val[14];
	t_matrix.m_val[3] = p_left.m_val[0] * p_right.m_val[3] + p_left.m_val[1] * p_right.m_val[7] + p_left.m_val[2] * p_right.m_val[11] + p_left.m_val[3] * p_right.m_val[15];

	t_matrix.m_val[4] = p_left.m_val[4] * p_right.m_val[0] + p_left.m_val[5] * p_right.m_val[4] + p_left.m_val[6] * p_right.m_val[8] + p_left.m_val[7] * p_right.m_val[12];
	t_matrix.m_val[5] = p_left.m_val[4] * p_right.m_val[1] + p_left.m_val[5] * p_right.m_val[5] + p_left.m_val[6] * p_right.m_val[9] + p_left.m_val[7] * p_right.m_val[13];
	t_matrix.m_val[6] = p_left.m_val[4] * p_right.m_val[2] + p_left.m_val[5] * p_right.m_val[6] + p_left.m_val[6] * p_right.m_val[10] + p_left.m_val[7] * p_right.m_val[14];
	t_matrix.m_val[7] = p_left.m_val[4] * p_right.m_val[3] + p_left.m_val[5] * p_right.m_val[7] + p_left.m_val[6] * p_right.m_val[11] + p_left.m_val[7] * p_right.m_val[15];

	t_matrix.m_val[8] = p_left.m_val[8] * p_right.m_val[0] + p_left.m_val[9] * p_right.m_val[4] + p_left.m_val[10] * p_right.m_val[8] + p_left.m_val[11] * p_right.m_val[12];
	t_matrix.m_val[9] = p_left.m_val[8] * p_right.m_val[1] + p_left.m_val[9] * p_right.m_val[5] + p_left.m_val[10] * p_right.m_val[9] + p_left.m_val[11] * p_right.m_val[13];
	t_matrix.m_val[10] = p_left.m_val[8] * p_right.m_val[2] + p_left.m_val[9] * p_right.m_val[6] + p_left.m_val[10] * p_right.m_val[10] + p_left.m_val[11] * p_right.m_val[14];
	t_matrix.m_val[11] = p_left.m_val[8] * p_right.m_val[3] + p_left.m_val[9] * p_right.m_val[7] + p_left.m_val[10] * p_right.m_val[11] + p_left.m_val[11] * p_right.m_val[15];

	t_matrix.m_val[12] = p_left.m_val[12] * p_right.m_val[0] + p_left.m_val[13] * p_right.m_val[4] + p_left.m_val[14] * p_right.m_val[8] + p_left.m_val[15] * p_right.m_val[12];
	t_matrix.m_val[13] = p_left.m_val[12] * p_right.m_val[1] + p_left.m_val[13] * p_right.m_val[5] + p_left.m_val[14] * p_right.m_val[9] + p_left.m_val[15] * p_right.m_val[13];
	t_matrix.m_val[14] = p_left.m_val[12] * p_right.m_val[2] + p_left.m_val[13] * p_right.m_val[6] + p_left.m_val[14] * p_right.m_val[10] + p_left.m_val[15] * p_right.m_val[14];
	t_matrix.m_val[15] = p_left.m_val[12] * p_right.m_val[3] + p_left.m_val[13] * p_right.m_val[7] + p_left.m_val[14] * p_right.m_val[11] + p_left.m_val[15] * p_right.m_val[15];

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
*	　移動行列を適応する
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

	//移動行列を適応
	t_matrix.m_val[12] = p_x;
	t_matrix.m_val[13] = p_y;
	t_matrix.m_val[14] = p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　回転行列を適応する
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

	//拡大縮小行列を適応
	t_matrix.m_val[0] = p_x;
	t_matrix.m_val[5] = p_y;
	t_matrix.m_val[10] =  p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　回転行列を適応する
*	引数
*	　rotate：[I/ ]　回転角度（360度系）
*	　下記、回転軸となる正規化された方向ベクトルを設定する
*	　p_x	：[I/ ]　X 座標（X 成分に効かせる場合は 1.0 を指定）
*	　p_y	：[I/ ]　X 座標（Y 成分に効かせる場合は 1.0 を指定）
*	　p_z	：[I/ ]　X 座標（Z 成分に効かせる場合は 1.0 を指定）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Matrix::Rotate(const GLfloat rotate, const GLfloat p_x, const GLfloat p_y, const GLfloat p_z)
{
	//参考用のメモ
	//[●][●][●][ 3]
	//[●][●][●][ 7]
	//[●][●][●][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//回転行列を適応
	GLfloat c = cosf(DEGREE_TO_RADIAN(rotate));
	GLfloat s = sinf(DEGREE_TO_RADIAN(rotate));

	t_matrix.m_val[0] = (p_x * p_x) * (1.0f - c) + c;
	t_matrix.m_val[1] = (p_x * p_y) * (1.0f - c) - p_z * s;
	t_matrix.m_val[2] = (p_x * p_z) * (1.0f - c) + p_y * s;

	t_matrix.m_val[4] = (p_y * p_x) * (1.0f - c) + p_z * s;
	t_matrix.m_val[5] = (p_y * p_y) * (1.0f - c) + c;
	t_matrix.m_val[6] = (p_y * p_z) * (1.0f - c) - p_x * s;

	t_matrix.m_val[8] = (p_z * p_x) * (1.0f - c) - p_y * s;
	t_matrix.m_val[9] = (p_z * p_y) * (1.0f - c) + p_x * s;
	t_matrix.m_val[10] = (p_z * p_z) * (1.0f - c) + c;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　行列の値を取得する
*	引数
*	　なし
*	戻り値
*	　行列の値
*-------------------------------------------------------------------------------*/
const GLfloat* Matrix::GetMatrix()
{
	//メンバに保存されているマトリックスを返却
	return m_val;
}