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
*	　拡大/縮小行列を適応する
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
	t_matrix.m_val.m[2][2] = p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	関数説明
*	　回転行列を適応する
*	引数
*	　p_rotate	：[I/ ]　回転角度（360度系）
*	　下記、回転軸となる正規化された各方向ベクトルを設定する
*	　p_x		：[I/ ]　回転軸 X 成分（例：X 成分だけに効かせる場合は 1.0 を指定、その他 0.0）
*	　p_y		：[I/ ]　回転軸 Y 成分（例：Y 成分だけに効かせる場合は 1.0 を指定、その他 0.0）
*	　p_z		：[I/ ]　回転軸 Z 成分（例：Z 成分だけに効かせる場合は 1.0 を指定、その他 0.0）
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
	GLfloat t_c = cosf((float)DEGREE_TO_RADIAN(p_rotate));
	GLfloat t_s = sinf((float)DEGREE_TO_RADIAN(p_rotate));

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
*	　視野変換行列を適応する
*	引数
*	　p_eye		：[I/ ]　カメラの位置
*	　p_look	：[I/ ]　カメラの注視点
*	　p_up		：[I/ ]　カメラの上向きベクトル
*				  （例：Y 成分が上下成分で、上が上向きの場合は、Y だけ 1.0、その他は 0.0 を指定）
*
*	　図は下記URLの「視野変換行列」項目参照
*	　http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20090902
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Matrix::LookAt(const Vec3 &p_eye, const Vec3 &p_look, const Vec3 &p_up)
{
	Matrix t_matrix;
	
	Vec3 d = { p_look.x - p_eye.x, p_look.y - p_eye.y, p_look.z - p_eye.z  };
	//ベクトルが[0]はエラー
	if (0 == d.x && 0 == d.y && 0 == d.z)
	{
		ERROR_MESSAGE("視野変換行列 計算エラー 引数が不正です。\n" \
					  "p_eye.x = %f, p_eye.y = %f, p_eye.z = %f\n" \
					  "p_look.x = %f, p_look.y = %f, p_look.z = %f\n" \
					  "p_up.x = %f, p_up.y = %f, p_up.z = %f\n" \
					  , p_eye.x, p_eye.y, p_eye.z, p_look.x, p_look.y, p_look.z, p_up.x, p_up.y, p_up.z);
		return;
	}

	Vec3 f = Math::Normalize( d );
	Vec3 u = Math::Normalize(p_up);

	Vec3 s = Math::Cross(f, u);
	//ベクトルが[0]はエラー
	if (0 == s.x && 0 == s.y && 0 == s.z)
	{
		ERROR_MESSAGE("視野変換行列 計算エラー 引数が不正です。\n" \
					  "p_eye.x = %f, p_eye.y = %f, p_eye.z = %f\n" \
					  "p_look.x = %f, p_look.y = %f, p_look.z = %f\n" \
					  "p_up.x = %f, p_up.y = %f, p_up.z = %f\n" \
					  , p_eye.x, p_eye.y, p_eye.z, p_look.x, p_look.y, p_look.z, p_up.x, p_up.y, p_up.z);
		return;
	}

	s = Math::Normalize( s );
	u = Math::Cross(s, f);

	t_matrix.m_val.m[0][0] = s.x;
	t_matrix.m_val.m[1][0] = s.y;
	t_matrix.m_val.m[2][0] = s.z;
	t_matrix.m_val.m[0][1] = u.x;
	t_matrix.m_val.m[1][1] = u.y;
	t_matrix.m_val.m[2][1] = u.z;
	t_matrix.m_val.m[0][2] = -f.x;
	t_matrix.m_val.m[1][2] = -f.y;
	t_matrix.m_val.m[2][2] = -f.z;
	t_matrix.m_val.m[3][0] = -(Math::Dot(s, p_eye));
	t_matrix.m_val.m[3][1] = -(Math::Dot(u, p_eye));
	t_matrix.m_val.m[3][2] = Math::Dot(f, p_eye);

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
		ERROR_MESSAGE("平行投影変換行列 計算エラー 引数が不正です。\n" \
					  "p_left = %f, p_right = %f, p_bottom = %f p_top = %f, p_near = %f, p_far = %f\n" \
					  , p_left, p_right, p_bottom, p_top, p_near, p_far);
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
		ERROR_MESSAGE("透視投影変換行列 計算エラー 引数が不正です。\n" \
					  "p_left = %f, p_right = %f, p_bottom = %f p_top = %f, p_near = %f, p_far = %f\n" \
					  , p_left, p_right, p_bottom, p_top, p_near, p_far);
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

	GLfloat t_f = 1.0f / (tanf((float)DEGREE_TO_RADIAN(p_fovY_degree)) / 2.0f);

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