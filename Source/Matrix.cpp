#include "Matrix.h"

//�R���X�g���N�^
Matrix::Matrix()
{
	//�P�ʍs��𐶐�����i����������j
	Identity();
}
Matrix::Matrix(const Mat4 &p_matrix)
{
	//�w�肳�ꂽ�}�g���N�X��ݒ肷��
	memmove(&this->m_val, &p_matrix, sizeof(this->m_val));
}

//�f�X�g���N�^
Matrix::~Matrix()
{
	
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@���Z�q�̃I�[�o�[���[�h��`
*-------------------------------------------------------------------------------*/

//�}�g���N�X���m�̏�Z
Matrix operator*(const Matrix &p_left, const Matrix &p_right)
{
	Matrix t_matrix;

	//�s��̏�Z�iOpenGL�͍s�x�N�g���ł͂Ȃ���x�N�g���Ȃ��Ƃɒ��ӁA��Z�͈�ʓI�ȍs��̏�Z�ƈႤ�j
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

//�}�g���N�X���m�̏�Z
Matrix operator*(const Matrix &p_left, const Mat4 &p_right)
{
	Matrix t_matrix(p_right);

	t_matrix = p_left * t_matrix;

	return t_matrix;
}

//�}�g���N�X���m�̏�Z
Matrix operator*(const Mat4 &p_left, const Matrix &p_right)
{
	Matrix t_matrix(p_left);

	t_matrix = t_matrix * p_right;

	return t_matrix;
}

//�}�g���N�X���m�̏�Z
Matrix operator*(const Mat4 &p_left, const Mat4 &p_right)
{
	Matrix t_matrix;
	Matrix t_matrix_left(p_left);
	Matrix t_matrix_right(p_right);

	t_matrix = t_matrix_left * t_matrix_right;

	return t_matrix;
}

//�}�g���N�X�̑��
void Matrix::operator=(const Mat4 &p_matrix)
{
	memmove(&this->m_val, &p_matrix, sizeof(this->m_val));
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�P�ʍs��𐶐�����
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void Matrix::Identity()
{	
	//�Q�l�p�̃���
	//[��][  ][  ][  ]
	//[  ][��][  ][  ]
	//[  ][  ][��][  ]
	//[  ][  ][  ][��]

	//�s�񏉊���
	memset(&m_val, 0, sizeof(m_val));

	//�P�ʍs��ݒ肷��
	m_val.m[0][0] = 1.0f;
	m_val.m[1][1] = 1.0f;
	m_val.m[2][2] = 1.0f;
	m_val.m[3][3] = 1.0f;

}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�ړ��s���K�p����
*	����
*	�@p_x	�F[I/ ]�@X ���W�̈ړ���
*	�@p_y	�F[I/ ]�@Y ���W�̈ړ���
*	�@p_z	�F[I/ ]�@Z ���W�̈ړ���
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void Matrix::Translate(const GLfloat p_x, const GLfloat p_y, const GLfloat p_z)
{
	//�Q�l�p�̃���
	//[  ][  ][  ][  ]
	//[  ][  ][  ][  ]
	//[  ][  ][  ][  ]
	//[��][��][��][  ]

	Matrix t_matrix;

	//�ړ��s���K�p
	t_matrix.m_val.m[3][0] = p_x;
	t_matrix.m_val.m[3][1] = p_y;
	t_matrix.m_val.m[3][2] = p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�g��/�k���s���K������
*	����
*	�@p_x	�F[I/ ]�@X ���W�̔{��
*	�@p_y	�F[I/ ]�@Y ���W�̔{��
*	�@p_z	�F[I/ ]�@Z ���W�̔{��
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void Matrix::Scale(const GLfloat p_x, const GLfloat p_y, const GLfloat p_z)
{
	//�Q�l�p�̃���
	//[��][  ][  ][  ]
	//[  ][��][  ][  ]
	//[  ][  ][��][  ]
	//[  ][  ][  ][  ]

	Matrix t_matrix;

	//�g��k���s���K�p
	t_matrix.m_val.m[0][0] = p_x;
	t_matrix.m_val.m[1][1] = p_y;
	t_matrix.m_val.m[2][2] = p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@��]�s���K������
*	����
*	�@p_rotate	�F[I/ ]�@��]�p�x�i360�x�n�j
*	�@���L�A��]���ƂȂ鐳�K�����ꂽ�e�����x�N�g����ݒ肷��
*	�@p_x		�F[I/ ]�@��]�� X �����i��FX ���������Ɍ�������ꍇ�� 1.0 ���w��A���̑� 0.0�j
*	�@p_y		�F[I/ ]�@��]�� Y �����i��FY ���������Ɍ�������ꍇ�� 1.0 ���w��A���̑� 0.0�j
*	�@p_z		�F[I/ ]�@��]�� Z �����i��FZ ���������Ɍ�������ꍇ�� 1.0 ���w��A���̑� 0.0�j
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void Matrix::Rotate(const GLfloat p_rotate, const GLfloat p_x, const GLfloat p_y, const GLfloat p_z)
{
	//�Q�l�p�̃���
	//[��][��][��][  ]
	//[��][��][��][  ]
	//[��][��][��][  ]
	//[  ][  ][  ][  ]

	Matrix t_matrix;

	//��]�s���K�p
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
*	�֐�����
*	�@����ϊ��s���K������
*	����
*	�@p_eye		�F[I/ ]�@�J�����̈ʒu
*	�@p_look	�F[I/ ]�@�J�����̒����_
*	�@p_up		�F[I/ ]�@�J�����̏�����x�N�g��
*				  �i��FY �������㉺�����ŁA�オ������̏ꍇ�́AY ���� 1.0�A���̑��� 0.0 ���w��j
*
*	�@�}�͉��LURL�́u����ϊ��s��v���ڎQ��
*	�@http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20090902
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void Matrix::LookAt(const Vec3 &p_eye, const Vec3 &p_look, const Vec3 &p_up)
{
	Matrix t_matrix;
	
	Vec3 d = { p_look.x - p_eye.x, p_look.y - p_eye.y, p_look.z - p_eye.z  };
	//�x�N�g����[0]�̓G���[
	if (0 == d.x && 0 == d.y && 0 == d.z)
	{
		ERROR_MESSAGE("����ϊ��s�� �v�Z�G���[ �������s���ł��B\n" \
					  "p_eye.x = %f, p_eye.y = %f, p_eye.z = %f\n" \
					  "p_look.x = %f, p_look.y = %f, p_look.z = %f\n" \
					  "p_up.x = %f, p_up.y = %f, p_up.z = %f\n" \
					  , p_eye.x, p_eye.y, p_eye.z, p_look.x, p_look.y, p_look.z, p_up.x, p_up.y, p_up.z);
		return;
	}

	Vec3 f = Math::Normalize( d );
	Vec3 u = Math::Normalize(p_up);

	Vec3 s = Math::Cross(f, u);
	//�x�N�g����[0]�̓G���[
	if (0 == s.x && 0 == s.y && 0 == s.z)
	{
		ERROR_MESSAGE("����ϊ��s�� �v�Z�G���[ �������s���ł��B\n" \
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
*	�֐�����
*	�@���s���e�ϊ��s���K������
*	����
*	�@p_left	�F[I/ ]�@�߂��̖�(p_near��)�̍����܂ł̋���
*	�@p_right	�F[I/ ]�@�߂��̖�(p_near��)�̉E���܂ł̋���
*	�@p_bottom	�F[I/ ]�@�߂��̖�(p_near��)�̉����܂ł̋���
*	�@p_top		�F[I/ ]�@�߂��̖�(p_near��)�̏㑤�܂ł̋���
*	�@p_near	�F[I/ ]�@�߂��̖ʂ܂ł̋���
*	�@p_far		�F[I/ ]�@�����̖ʂ܂ł̋���
*
*	�@�}�͉��LURL�́u���s���e�ϊ��v���ڎQ��
*	�@http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20090829
*	�߂�l
*	�@�Ȃ�
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
		ERROR_MESSAGE("���s���e�ϊ��s�� �v�Z�G���[ �������s���ł��B\n" \
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
*	�֐�����
*	�@�������e�ϊ��s���K������
*	�@����ɂ���uPerspective�v�֐��ł��s����쐬���邱�Ƃ��\�ł��i�I�[�o�[���[�h���Ă���܂��j
*	�@�������Ⴄ�̂ŁA�g���₷������p�r�ɍ��킹�Ďg�p���邱�Ɓi���ʓI�ɂ͓������Ƃ��ł��܂��j
*	����
*	�@p_left	�F[I/ ]�@�߂��̖�(p_near��)�̍����܂ł̋���
*	�@p_right	�F[I/ ]�@�߂��̖�(p_near��)�̉E���܂ł̋���
*	�@p_bottom	�F[I/ ]�@�߂��̖�(p_near��)�̉����܂ł̋���
*	�@p_top		�F[I/ ]�@�߂��̖�(p_near��)�̏㑤�܂ł̋���
*	�@p_near	�F[I/ ]�@�߂��̖ʂ܂ł̋���
*	�@p_far		�F[I/ ]�@�����̖ʂ܂ł̋���
*
*	�@�}�͉��LURL�́u�������e�ϊ��v���ڎQ��
*	�@http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20090829
*	�߂�l
*	�@�Ȃ�
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
		ERROR_MESSAGE("�������e�ϊ��s�� �v�Z�G���[ �������s���ł��B\n" \
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
*	�֐�����
*	�@�������e�ϊ��s���K������
*	�@���ɂ���uPerspective�v�֐��ł��s����쐬���邱�Ƃ��\�ł��i�I�[�o�[���[�h���Ă���܂��j
*	�@�������Ⴄ�̂ŁA�g���₷������p�r�ɍ��킹�Ďg�p���邱�Ɓi���ʓI�ɂ͓������Ƃ��ł��܂��j
*	����
*	�@p_near		�F[I/ ]�@�߂��̖ʂ܂ł̋���
*	�@p_far			�F[I/ ]�@�����̖ʂ܂ł̋���
*	�@p_fovY_deg	�F[I/ ]�@�J������ Y�����̉�p
*	�@p_aspect		�F[I/ ]�@�`���̉�ʂ̃A�X�y�N�g��i�� �� �����j
*
*	�߂�l
*	�@�Ȃ�
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
*	�֐�����
*	�@�t�s������߂�
*	�@�Q�l�T�C�g�Fhttp://thira.plavox.info/blog/2008/06/_c.html
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�t�s��
*-------------------------------------------------------------------------------*/
void Matrix::Inverse(void)
{
	//�t�s��̌��ʂ��ꎞ�I�ɕۑ�����ϐ�
	double in_matrix[4][4];		//���͗p�̍s��
	double out_matrix[4][4];	//�o�͗p�̍s��

	//�ꎞ�I�ȃf�[�^��~����
	double t_data; 

	//�J�E���^�ϐ�
	int i = 0;
	int j = 0;
	int k = 0;

	//�s��̔z�񎟐�
	//���㗬�p�ł��邩���Ƃ������ƂŎc���Ă�����`�ŕ��i�͕ς��Ȃ��l
	int N = 4;

	//���͗p�̍s����R�s�[����i�v�Z�ߒ��ŏ㏑�������̂Ƃ��ł�double�ɂ������̂Łj
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			in_matrix[i][j] = (double)m_val.m[i][j];
		}
	}

	//�P�ʍs������
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			out_matrix[i][j] = (i == j) ? 1.0 : 0.0;
		}
	}

	//�|���o���@���g�p���ċt�s������߂�
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

	//�L���X�g�ϊ����Ȃ��猋�ʂ������o�ϐ��ɃR�s�[����
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			m_val.m[i][j] = (GLfloat)out_matrix[i][j];
		}
	}
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�]�u�s������߂�
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void Matrix::Transpose(void)
{
	Matrix t_matrix;

	//�J�E���^�ϐ�
	int i = 0;
	int j = 0;

	//�s��̔z�񎟐�
	//���㗬�p�ł��邩���Ƃ������ƂŎc���Ă�����`�ŕ��i�͕ς��Ȃ��l
	int N = 4;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			t_matrix.m_val.m[j][i] = m_val.m[i][j];
		}
	}

	*this = t_matrix;
}