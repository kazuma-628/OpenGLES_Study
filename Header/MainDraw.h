#ifndef MAIN_DRAW_H
#define MAIN_DRAW_H

//include��`
#include "Common.h"
#include "ShaderManager.h"
#include "Matrix.h"
#include "DeviceManager.h"
#include "WindowManager.h"
#include "ModelManager.h"
#include "ResourceManager.h"

//�O���t�B�b�N��Ԃ̍��W�n
typedef struct
{
	GLfloat x;		//X���W
	GLfloat y;		//Y���W
	GLfloat z;		//Z���W
}Vector;


class MainDraw
{

public:
	//�R���X�g���N�^
	MainDraw();

	//�f�X�g���N�^
	~MainDraw();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@���C���`��̏���������
	*	����
	*	�@�Ȃ�
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void Prepare();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@���C���`����J�n����
	*	����
	*	�@p_WindowManager		�F[I/ ]�@�E�B���h�E�Ǘ��I�u�W�F�N�g
	*	�@p_DeviceManager		�F[I/ ]�@Key�Ǘ��I�u�W�F�N�g
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void Drawing(WindowManager* p_WindowManager, DeviceManager* p_DeviceManager);

private:

	ShaderManager *m_MainShader;		//���C���V�F�[�_�[�I�u�W�F�N�g
	GLint m_attr_pos;					//���_�f�[�^
	GLint m_attr_color;					//�J���[�f�[�^
	GLint m_ModelView_matrix;			//���f���r���[�}�g���b�N�X�i�I�u�W�F�N�g�ړ��p�̃}�g���b�N�X�j
	GLint m_Proj_matrix;				//���f���r���[�}�g���b�N�X�i3D��Ԃɂ��邽�߂̃}�g���N�X�j

	Vector m_Rotate;				//��]�ʂ��Ǘ�����ϐ�
	Vector m_Translate;				//�ړ��ʂ��Ǘ�����ϐ�
};
#endif