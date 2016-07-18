#include "Matrix.h"

//コンストラクタ
Matrix::Matrix()
{
	//単位行列を生成する（初期化する）
	Identity();
}
Matrix::Matrix(const Mat4 &p_matrix)
{
	//指定されたマトリクスを設定する
	memmove(&this->m_val, &p_matrix, sizeof(this->m_val));
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
Matrix operator*(const Matrix &p_left, const Matrix &p_right)
{
	Matrix t_matrix;

	//行列の乗算（OpenGLは行ベクトルではなく列ベクトルなことに注意、乗算は一般的な行列の乗算と違う）
	for (int i = 0; i < 4; i++)
	{
		t_matrix.m_val.m[i][0] = p_left.m_val.m[0][0] * p_right.m_val.m[i][0] + p_left.m_val.m[1][0] * p_right.m_val.m[i][1]
							   + p_left.m_val.m[2][0] * p_right.m_val.m[i][2] + p_left.m_val.m[3][0] * p_right.m_val.m[i][3];
		t_matrix.m_val.m[i][1] = p_left.m_val.m[0][1] * p_right.m_val.m[i][0] + p_left.m_val.m[1][1] * p_right.m_val.m[i][1]
							   + p_left.m_val.m[2][1] * p_right.m_val.m[i][2] + p_left.m_val.m[3][1] * p_right.m_val.m[i][3];
		t_matrix.m_val.m[i][2] = p_left.m_val.m[0][2] * p_right.m_val.m[i][0] + p_left.m_val.m[1][2] * p_right.m_val.m[i][1] 
							   + p_left.m_val.m[2][2] * p_right.m_val.m[i][2] + p_left.m_val.m[3][2] * p_right.m_val.m[i][3];
		t_matrix.m_val.m[i][3] = p_left.m_val.m[0][3] * p_right.m_val.m[i][0] + p_left.m_val.m[1][3] * p_right.m_val.m[i][1] 
							   + p_left.m_val.m[2][3] * p_right.m_val.m[i][2] + p_left.m_val.m[3][3] * p_right.m_val.m[i][3];
		
		}
	return t_matrix;
}

//マトリクス同士の乗算
Matrix operator*(const Matrix &p_left, const Mat4 &p_right)
{
	Matrix t_matrix(p_right);

	t_matrix = p_left * t_matrix;

	return t_matrix;
}

//マトリクス同士の乗算
Matrix operator*(const Mat4 &p_left, const Matrix &p_right)
{
	Matrix t_matrix(p_left);

	t_matrix = t_matrix * p_right;

	return t_matrix;
}

//マトリクス同士の乗算
Matrix operator*(const Mat4 &p_left, const Mat4 &p_right)
{
	Matrix t_matrix;
	Matrix t_matrix_left(p_left);
	Matrix t_matrix_right(p_right);

	t_matrix = t_matrix_left * t_matrix_right;

	return t_matrix;
}

//マトリクスの代入
void Matrix::operator=(const Mat4 &p_matrix)
{
	memmove(&this->m_val, &p_matrix, sizeof(this->m_val));
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
	//[●][  ][  ][  ]
	//[  ][●][  ][  ]
	//[  ][  ][●][  ]
	//[  ][  ][  ][●]

	//行列初期化
	memset(&m_val, 0, sizeof(m_val));

	//単位行列設定する
	m_val.m[0][0] = 1.0f;
	m_val.m[1][1] = 1.0f;
	m_val.m[2][2] = 1.0f;
	m_val.m[3][3] = 1.0f;

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
	//[  ][  ][  ][  ]
	//[  ][  ][  ][  ]
	//[  ][  ][  ][  ]
	//[●][●][●][  ]

	Matrix t_matrix;

	//移動行列を適用
	t_matrix.m_val.m[3][0] = p_x;
	t_matrix.m_val.m[3][1] = p_y;
	t_matrix.m_val.m[3][2] = p_z;

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
	//[●][  ][  ][  ]
	//[  ][●][  ][  ]
	//[  ][  ][●][  ]
	//[  ][  ][  ][  ]

	Matrix t_matrix;

	//拡大縮小行列を適用
	t_matrix.m_val.m[0][0] = p_x;
	t_matrix.m_val.m[1][1] = p_y;
	t_matrix.m_val.m[2][2] =  p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　回転行列を適応する
*	引数
*	　p_rotate	：[I/ ]　回転角度（360度系）
*	　下記、回転軸となる正規化された方向ベクトルを設定する
*	　p_x		：[I/ ]　X 座標（X 成分に効かせる場合は 1.0 を指定）
*	　p_y		：[I/ ]　X 座標（Y 成分に効かせる場合は 1.0 を指定）
*	　p_z		：[I/ ]　X 座標（Z 成分に効かせる場合は 1.0 を指定）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Matrix::Rotate(const GLfloat p_rotate, const GLfloat p_x, const GLfloat p_y, const GLfloat p_z)
{
	//参考用のメモ
	//[●][●][●][  ]
	//[●][●][●][  ]
	//[●][●][●][  ]
	//[  ][  ][  ][  ]

	Matrix t_matrix;

	//回転行列を適用
	GLfloat t_c = cosf(DEGREE_TO_RADIAN(p_rotate));
	GLfloat t_s = sinf(DEGREE_TO_RADIAN(p_rotate));

	t_matrix.m_val.m[0][0] = (p_x * p_x) * (1.0f - t_c) + t_c;
	t_matrix.m_val.m[0][1] = (p_x * p_y) * (1.0f - t_c) - p_z * t_s;
	t_matrix.m_val.m[0][2] = (p_x * p_z) * (1.0f - t_c) + p_y * t_s;

	t_matrix.m_val.m[1][0] = (p_y * p_x) * (1.0f - t_c) + p_z * t_s;
	t_matrix.m_val.m[1][1] = (p_y * p_y) * (1.0f - t_c) + t_c;
	t_matrix.m_val.m[1][2] = (p_y * p_z) * (1.0f - t_c) - p_x * t_s;

	t_matrix.m_val.m[2][0] = (p_z * p_x) * (1.0f - t_c) - p_y * t_s;
	t_matrix.m_val.m[2][1] = (p_z * p_y) * (1.0f - t_c) + p_x * t_s;
	t_matrix.m_val.m[2][2] = (p_z * p_z) * (1.0f - t_c) + t_c;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　平行投影変換行列を適応する
*	引数
*	　p_left	：[I/ ]　近くの面(p_near面)の左側までの距離
*	　p_right	：[I/ ]　近くの面(p_near面)の右側までの距離
*	　p_bottom	：[I/ ]　近くの面(p_near面)の下側までの距離
*	　p_top		：[I/ ]　近くの面(p_near面)の上側までの距離
*	　p_near	：[I/ ]　近くの面までの距離
*	　p_far		：[I/ ]　遠くの面までの距離
*
*	　図は下記URLの「平行投影変換」項目参照
*	　http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20090829
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void  Matrix::Orthogonal(const GLfloat p_left, const GLfloat p_right,
						 const GLfloat p_bottom, const GLfloat p_top,
						 const GLfloat p_near, const GLfloat p_far)
{
	Matrix t_matrix;

	GLfloat dx = p_right - p_left;
	GLfloat dy = p_top - p_bottom;
	GLfloat dz = p_far - p_near;

	if (0 == dx || 0 == dy || 0 == dz)
	{
		printf("デバッグ情報\n");
		printf("p_right = %f, p_left = %f, p_top = %f, p_bottom = %f, p_far = %f, p_near = %f\n",
			p_right, p_left, p_top, p_bottom, p_far, p_near);
		ERROR_MESSAGE("平行投影変換行列の引数異常です");
	}

	t_matrix.m_val.m[0][0] = 2.0f / dx;
	t_matrix.m_val.m[1][1] = 2.0f / dy;
	t_matrix.m_val.m[2][2] = -2.0f / dz;
	t_matrix.m_val.m[3][0] = -(p_right + p_left) / dx;
	t_matrix.m_val.m[3][1] = -(p_top + p_bottom) / dy;
	t_matrix.m_val.m[3][2] = -(p_far + p_near) / dz;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　透視投影変換行列を適応する
*	　一つ下にある「Perspective」関数でも行列を作成することが可能です（オーバーロードしてあります）
*	　引数が違うので、使いやすい方や用途に合わせて使用すること（結果的には同じことができます）
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
void Matrix::Perspective(const GLfloat p_left, const GLfloat p_right,
						 const GLfloat p_bottom, const GLfloat p_top,
						 const GLfloat p_near, const GLfloat p_far)
{
	Matrix t_matrix;

	GLfloat dx = p_right - p_left;
	GLfloat dy = p_top - p_bottom;
	GLfloat dz = p_far - p_near;

	if (0 == dx || 0 == dy || 0 == dz)
	{
		printf("デバッグ情報\n");
		printf("p_right = %f, p_left = %f, p_top = %f, p_bottom = %f, p_far = %f, p_near = %f\n",
			p_right, p_left, p_top, p_bottom, p_far, p_near);
		ERROR_MESSAGE("透視投影変換行列の引数異常です");
	}
	
	t_matrix.m_val.m[0][0] = 2.0f * p_near / dx;
	t_matrix.m_val.m[1][1] = 2.0f * p_near / dy;
	t_matrix.m_val.m[2][0] = (p_right + p_left) / dx;
	t_matrix.m_val.m[2][1] = (p_top + p_bottom) / dy;
	t_matrix.m_val.m[2][2] = -(p_far + p_near) / dz;
	t_matrix.m_val.m[2][3] = -1.0f;
	t_matrix.m_val.m[3][2] = -2.0f * p_far * p_near / dz;
	t_matrix.m_val.m[3][3] = 0.0f;

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
void Matrix::Perspective(const GLfloat p_near, const GLfloat p_far,
						 const GLfloat p_fovY_degree, const GLfloat p_aspect)
{
	Matrix t_matrix;

	GLfloat t_f = 1.0f / (tanf(DEGREE_TO_RADIAN(p_fovY_degree)) / 2.0f);

	t_matrix.m_val.m[0][0] = t_f / p_aspect;
	t_matrix.m_val.m[1][1] = t_f;
	t_matrix.m_val.m[2][2] = (p_far + p_near) / (p_near - p_far);
	t_matrix.m_val.m[2][3] = -1;
	t_matrix.m_val.m[3][2] = (2.0f * p_far * p_near) / (p_near - p_far);

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　逆行列を求める
*	　参考サイト：http://thira.plavox.info/blog/2008/06/_c.html
*	引数
*	　なし
*	戻り値
*	　逆行列
*-------------------------------------------------------------------------------*/
void Matrix::Inverse(void)
{
	//逆行列の結果を一時的に保存する変数
	double in_matrix[4][4];		//入力用の行列
	double out_matrix[4][4];	//出力用の行列

	//一時的なデータを蓄える
	double t_data; 

	//カウンタ変数
	int i = 0;
	int j = 0;
	int k = 0;

	//行列の配列次数
	//今後流用できるかもということで残しておく定義で普段は変えない値
	int N = 4;

	//入力用の行列をコピーする（計算過程で上書きされるのとついでにdoubleにしたいので）
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			in_matrix[i][j] = (double)m_val.m[i][j];
		}
	}

	//単位行列を作る
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			out_matrix[i][j] = (i == j) ? 1.0 : 0.0;
		}
	}

	//掃き出し法を使用して逆行列を求める
	for (i = 0; i < N; i++)
	{
		t_data = 1 / in_matrix[i][i];
		for (j = 0; j < N; j++)
		{
			in_matrix[i][j] *= t_data;
			out_matrix[i][j] *= t_data;
		}
		
		for (j = 0; j < N; j++)
		{
			if (i != j)
			{
				t_data = in_matrix[j][i];
				for (k = 0; k < N; k++)
				{
					in_matrix[j][k] -= in_matrix[i][k] * t_data;
					out_matrix[j][k] -= out_matrix[i][k] * t_data;
				}
			}
		}
	}

	//キャスト変換しながら結果をメンバ変数にコピーする
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			m_val.m[i][j] = (GLfloat)out_matrix[i][j];
		}
	}
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　転置行列を求める
*	引数
*	　なし
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Matrix::Transpose(void)
{
	Matrix t_matrix;

	//カウンタ変数
	int i = 0;
	int j = 0;

	//行列の配列次数
	//今後流用できるかもということで残しておく定義で普段は変えない値
	int N = 4;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			t_matrix.m_val.m[j][i] = m_val.m[i][j];
		}
	}

	*this = t_matrix;
}