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
Matrix operator*(Matrix& p_left, Matrix& p_right)
{
	//�Q�l�p�̃���
	//[ 0][ 1][ 2][ 3]
	//[ 4][ 5][ 6][ 7]
	//[ 8][ 9][10][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//�s��̏�Z
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
*	�@�ړ��s���K������
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

	//�ړ��s���K��
	t_matrix.m_val[12] = p_x;
	t_matrix.m_val[13] = p_y;
	t_matrix.m_val[14] = p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@��]�s���K������
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

	//�g��k���s���K��
	t_matrix.m_val[0] = p_x;
	t_matrix.m_val[5] = p_y;
	t_matrix.m_val[10] =  p_z;

	*this = *this * t_matrix;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@��]�s���K������
*	����
*	�@rotate�F[I/ ]�@��]�p�x�i360�x�n�j
*	�@���L�A��]���ƂȂ鐳�K�����ꂽ�����x�N�g����ݒ肷��
*	�@p_x	�F[I/ ]�@X ���W�iX �����Ɍ�������ꍇ�� 1.0 ���w��j
*	�@p_y	�F[I/ ]�@X ���W�iY �����Ɍ�������ꍇ�� 1.0 ���w��j
*	�@p_z	�F[I/ ]�@X ���W�iZ �����Ɍ�������ꍇ�� 1.0 ���w��j
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void Matrix::Rotate(const GLfloat rotate, const GLfloat p_x, const GLfloat p_y, const GLfloat p_z)
{
	//�Q�l�p�̃���
	//[��][��][��][ 3]
	//[��][��][��][ 7]
	//[��][��][��][11]
	//[12][13][14][15]

	Matrix t_matrix;

	//��]�s���K��
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
*	�֐�����
*	�@�s��̒l���擾����
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�s��̒l
*-------------------------------------------------------------------------------*/
const GLfloat* Matrix::GetMatrix()
{
	//�����o�ɕۑ�����Ă���}�g���b�N�X��ԋp
	return m_val;
}