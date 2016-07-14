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
*	�@��]�s���K�p����
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
	t_matrix.m_val.m[2][2] =  p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@��]�s���K������
*	����
*	�@p_rotate	�F[I/ ]�@��]�p�x�i360�x�n�j
*	�@���L�A��]���ƂȂ鐳�K�����ꂽ�����x�N�g����ݒ肷��
*	�@p_x		�F[I/ ]�@X ���W�iX �����Ɍ�������ꍇ�� 1.0 ���w��j
*	�@p_y		�F[I/ ]�@X ���W�iY �����Ɍ�������ꍇ�� 1.0 ���w��j
*	�@p_z		�F[I/ ]�@X ���W�iZ �����Ɍ�������ꍇ�� 1.0 ���w��j
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
void Matrix::Perspective(const float p_left, const float p_right,
						 const float p_bottom, const float p_top,
						 const float p_near, const float p_far)
{
	Matrix t_matrix;

	//�������e�ϊ��s���K�p����
	float dx = p_right - p_left;
	float dy = p_top - p_bottom;
	float dz = p_far - p_near;

	if (0 == dx || 0 == dy || 0 == dz)
	{
		printf("�f�o�b�O���\n");
		printf("p_right = %f, p_left = %f, p_top = %f, p_bottom = %f, p_far = %f, p_near = %f\n",
			p_right, p_left, p_top, p_bottom, p_far, p_near);
		ERROR_MESSAGE("�������e�ϊ��s��̈����ُ�ł�");
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
void Matrix::Perspective(const float p_near, const float p_far,
						 const float p_fovY_degree, const float p_aspect)
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
*	�֐�����
*	�@�t�s������߂�
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�t�s��
*-------------------------------------------------------------------------------*/
Matrix Matrix::Inverse() const
{
	Matrix t_matrix;


	return t_matrix;
}
