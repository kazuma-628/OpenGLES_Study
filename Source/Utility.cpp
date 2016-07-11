#include "Utility.h"

//�R���X�g���N�^
Utility::Utility()
{

}

//�f�X�g���N�^
Utility::~Utility()
{

}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�x�N�g���̒��������߂�
*	����
*	�@p_Vector		�F[I/ ]�@�x�N�g��
*	�߂�l
*	�@����I��		�F�x�N�g���̒���
*	�@�ȏ�I��		�F0.0		
*-------------------------------------------------------------------------------*/
float Utility::Length(Vec3 *p_Vector)
{
	float length = 0.0f;	//�x�N�g���̒���

	//�����`�F�b�N
	if (NULL == p_Vector)
	{
		ERROR_MESSAGE("�����G���[");
		return length;
	}
	
	//�v�Z���₷���悤�ɑ���i�덷�����Ȃ����邽�߂�[double]�Ōv�Z�j
	double x = (double)(p_Vector->x);
	double y = (double)(p_Vector->y);
	double z = (double)(p_Vector->z);

	//�x�N�g���̒��������߂�
	length = (float)sqrt(x * x + y * y + z * z);

	return length;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�x�N�g���𐳋K������
*	����
*	�@p_Vector		�F[I/ ]�@�x�N�g��
*	�߂�l
*	�@����I��		�F���K�����ꂽ�x�N�g��
*	�@�ȏ�I��		�F�S�v�f[0.0]
*-------------------------------------------------------------------------------*/
Vec3 Utility::Normalize(Vec3 *p_Vector)
{
	Vec3 normalize = { 0.0f };		//���K�����ꂽ�x�N�g��

	//�����`�F�b�N
	if (NULL == p_Vector)
	{
		ERROR_MESSAGE("�����G���[");
		return normalize;
	}

	//�v�Z���₷���悤�ɑ���i�덷�����Ȃ����邽�߂�[double]�Ōv�Z�j
	double x = (double)(p_Vector->x);
	double y = (double)(p_Vector->y);
	double z = (double)(p_Vector->z);

	//�x�N�g���̒��������߂�
	double length = sqrt(x * x + y * y + z * z);

	//�x�N�g���̒�����[0]����0���Z�ɂȂ�̂ŃG���[
	if (length < (1e-6))
	{
		ERROR_MESSAGE("�v�Z�G���[");
		return normalize;
	}

	//���K������
	length = 1.0 / length;
	x *= length;
	y *= length;
	z *= length;

	//�߂�l��ݒ�
	normalize.x = (float)x;
	normalize.y = (float)y;
	normalize.z = (float)z;

	return normalize;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�x�N�g���̓��ς����߂�
*	����
*	�@p_Vector1		�F[I/ ]�@�x�N�g��1
*	�@p_Vector2		�F[I/ ]�@�x�N�g��2
*	�߂�l
*	�@����I��		�F����
*	�@�ȏ�I��		�F0.0
*-------------------------------------------------------------------------------*/
float Utility::Dot(Vec3 *p_Vector1, Vec3 *p_Vector2)
{
	float dot = 0.0f; //����

	//�����`�F�b�N
	if (NULL == p_Vector1 || NULL == p_Vector2)
	{
		ERROR_MESSAGE("�����G���[");
		return dot;
	}

	//�v�Z���₷���悤�ɑ���i�덷�����Ȃ����邽�߂�[double]�Ōv�Z�j
	double x1 = (double)(p_Vector1->x);
	double y1 = (double)(p_Vector1->y);
	double z1 = (double)(p_Vector1->z);

	double x2 = (double)(p_Vector2->x);
	double y2 = (double)(p_Vector2->y);
	double z2 = (double)(p_Vector2->z);

	//���ς����߂�
	dot = (float)((x1 * x2) + (y1 * y2) + (z1 * z2));
	
	return dot;
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�x�N�g���̊O�ς����߂�
*	����
*	�@p_Vector1		�F[I/ ]�@�x�N�g��1
*	�@p_Vector2		�F[I/ ]�@�x�N�g��2
*	�߂�l
*	�@����I��		�F���K�����ꂽ�x�N�g��
*	�@�ȏ�I��		�F�S�v�f[0.0]
*-------------------------------------------------------------------------------*/
Vec3 Utility::Cross(Vec3 *p_Vector1, Vec3 *p_Vector2)
{
	Vec3 cross = { 0.0f };		//���K�����ꂽ�x�N�g��

	//�����`�F�b�N
	if (NULL == p_Vector1 || NULL == p_Vector2)
	{
		ERROR_MESSAGE("�����G���[");
		return cross;
	}

	//�v�Z���₷���悤�ɑ���i�덷�����Ȃ����邽�߂�[double]�Ōv�Z�j
	double x1 = (double)(p_Vector1->x);
	double y1 = (double)(p_Vector1->y);
	double z1 = (double)(p_Vector1->z);

	double x2 = (double)(p_Vector2->x);
	double y2 = (double)(p_Vector2->y);
	double z2 = (double)(p_Vector2->z);

	//�O�ς����߂�
	cross.x = (float)(y1 * z2 - z1 * y2);
	cross.y = (float)(z1 * x2 - x1 * z2);
	cross.z = (float)(x1 * y2 - y1 * x2);

	return cross;
}