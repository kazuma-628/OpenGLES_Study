#include "Matrix.h"

//�R���X�g���N�^
Matrix::Matrix()
{
	//�P�ʍs��𐶐�����i����������j
	Identity();
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
Matrix operator*(Matrix &p_left, Matrix &p_right)
{
	//�Q�l�p�̃���
	//[ 0][ 1][ 2][ 3]
	//[ 4][ 5][ 6][ 7]
	//[ 8][ 9][10][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//�s��̏�Z�iOpenGL�͍s�x�N�g���ł͂Ȃ���x�N�g���Ȃ��Ƃɒ��ӁA��Z�͈�ʓI�ȍs��̏�Z�ƈႤ�j
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

//�}�g���N�X���m�̏�Z
Matrix operator*(Matrix &p_left, GLfloat *p_right)
{
	Matrix t_matrix;

	t_matrix.SetMatrix(p_right);

	t_matrix = p_left * t_matrix;

	return t_matrix;
}

//�}�g���N�X���m�̏�Z
Matrix operator*(GLfloat *p_left, Matrix &p_right)
{
	Matrix t_matrix;

	t_matrix.SetMatrix(p_left);

	t_matrix = t_matrix * p_right;

	return t_matrix;
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
	//[��][ 1][ 2][ 3]
	//[ 4][��][ 6][ 7]
	//[ 8][ 9][��][11]
	//[12][13][14][��]

	//�s�񏉊���
	memset(m_val, 0, sizeof(m_val));

	//�P�ʍs��ݒ肷��
	m_val[0] = 1.0f;
	m_val[5] = 1.0f;
	m_val[10] = 1.0f;
	m_val[15] = 1.0f;

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
	//[ 0][ 1][ 2][ 3]
	//[ 4][ 5][ 6][ 7]
	//[ 8][ 9][10][11]
	//[��][��][��][15]

	Matrix t_matrix;

	//�ړ��s���K�p
	t_matrix.m_val[12] = p_x;
	t_matrix.m_val[13] = p_y;
	t_matrix.m_val[14] = p_z;

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
	//[��][ 1][ 2][ 3]
	//[ 4][��][ 6][ 7]
	//[ 8][ 9][��][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//�g��k���s���K�p
	t_matrix.m_val[0] = p_x;
	t_matrix.m_val[5] = p_y;
	t_matrix.m_val[10] =  p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@��]�s���K�p����
*	����
*	�@p_rotate	�F[I/ ]�@��]�p�x�i360�x�n�j
*	�@���L�A��]���ƂȂ鐳�K�����ꂽ�����x�N�g����ݒ肷��
*	�@p_x		�F[I/ ]�@X �����iX �����Ɍ�������ꍇ�� 1.0 ���w��j
*	�@p_y		�F[I/ ]�@Y �����iY �����Ɍ�������ꍇ�� 1.0 ���w��j
*	�@p_z		�F[I/ ]�@Z �����iZ �����Ɍ�������ꍇ�� 1.0 ���w��j
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void Matrix::Rotate(const GLfloat p_rotate, const GLfloat p_x, const GLfloat p_y, const GLfloat p_z)
{
	//�Q�l�p�̃���
	//[��][��][��][ 3]
	//[��][��][��][ 7]
	//[��][��][��][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//��]�s���K�p
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
*	�֐�����
*	�@�������e�ϊ��s���K�p����
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
void Matrix::Perspective(float p_left, float p_right,
						 float p_bottom, float p_top,
						 float p_near, float p_far)
{
	//�Q�l�p�̃���
	//[ 0][ 1][ 2][ 3]
	//[ 4][ 5][ 6][ 7]
	//[ 8][ 9][10][11]
	//[12][13][14][15]

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
