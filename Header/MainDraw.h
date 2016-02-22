#ifndef MAINDRAW_H
#define MAINDRAW_H

//include��`
#include "Common.h"
#include "ShaderManager.h"
#include "Matrix.h"

//Define��`


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
	void Prep();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@���C���`����J�n����
	*	����
	*	�@window		�F[I/ ]�@�`���̃E�B���h�E���w�肷��
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void Draw(GLFWwindow *const p_window);

private:

	ShaderManager *m_MainShader;		//���C���V�F�[�_�[�I�u�W�F�N�g
	GLint m_attr_pos;					//���_�f�[�^
	GLint m_attr_color;					//�J���[�f�[�^
	GLint m_move_matrix;				//�}�g���b�N�X�f�[�^

	float move_x;						//�ړ��ʂ��Ǘ�����ϐ��iX�l�j
	float move_y;						//�ړ��ʂ��Ǘ�����ϐ��iY�l�j
};
#endif