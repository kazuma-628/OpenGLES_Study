#ifndef COMMON_H
#define COMMON_H

//Visual Studio�Łufopen,strcat,strcpy�v�Ȃǂ̊֐����g�p���邱�Ƃɂ��G���[/���[�j���O���o���Ȃ��悤�ɂ���
#define _CRT_SECURE_NOWARNINGS
#pragma warning(disable:4996)

////////////////////////////////////
// ��`�ς݂̃w�b�_�[�t�@�C���ǂݍ���
//�i�قƂ�ǂ̃t�@�C���ŕK�v�ɂȂ�͂��Ȃ̂ňꊇ��`�j
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <glew.h>
#include <glfw3.h>
#include <math.h>
#include <locale.h>



////////////////////////////////////////
// Define�x�N�g���\����

//�f�o�b�O���b�Z�[�W�o�͗p�}�N���i���[�U�[�����ڎg�p���邱�Ƃ͂���܂���j
//�G���[�E���[�j���O���b�Z�[�W���o�͂������ꍇ�́uERROR_MESSAGE�v���́uWARNING_MESSAGE�v���g�p���Ă��������B
#define DEBUG_PRINT(Level, String, ...)		printf("\n������ " Level " �������@\n�t�@�C���F%s�@\n�s���F%d�@�֐����F%s�@\n" String "\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);

//���s�s�\�ȃG���[�����������ꍇ�̃��b�Z�[�W�o�͗p��`
#define ERROR_MESSAGE(String, ...)			DEBUG_PRINT("�G���[", String, __VA_ARGS__);	error_message_func();

//���s�s�\�ł͂Ȃ����A�C�����K�v�ȉ\��������ꍇ�̃��b�Z�[�W�o�͗p��`
#define WARNING_MESSAGE(String, ...)		DEBUG_PRINT("���[�j���O", String, __VA_ARGS__);

//���s�s�\�ȃG���[�̉\���͂��邪�A�f�o�b�O���͈ꎞ�I�ɃG���[�ɂȂ�\��������ꍇ�̃��b�Z�[�W�o�͒�`
//�����͂��̃v���O���������삵�Ȃ��Ȃǂ̃G���[�m�F���̂݃R�����g���O���Č��Ă��������B�Ȃɂ������邩������܂���B
#define ERROR_MESSAGE_SUB(String, ...)	//ERROR_PRINT(String, __VA_ARGS__);	error_message_func();

#define WINDOW_WIDTH				1024			//�E�B���h�E�T�C�Y�i���j
#define WINDOW_HEIGHT				768				//�E�B���h�E�T�C�Y�i�����j
#define GL_GET_ERROR()				GL_NO_ERROR	//glGetError()	//gl�֘A�̃G���[���擾�������ꍇ�̓R�����g�̕��Ɠ���ւ���

////////////////////////////////////
// �x�N�g���\����

typedef struct
{
	GLfloat x;
	GLfloat y;
}Vec2;

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}Vec3;

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
}Vec4;

typedef struct
{
	GLint x;
	GLint y;
}iVec2;

typedef struct
{
	GLint x;
	GLint y;
	GLint z;
}iVec3;

typedef struct
{
	GLint x;
	GLint y;
	GLint z;
	GLint w;
}iVec4;

////////////////////////////////////
// �x�N�g���\����
typedef struct
{
	GLfloat m[2][2];
}Mat2;

typedef struct
{
	GLfloat m[3][3];
}Mat3;

typedef struct
{
	GLfloat m[4][4];
}Mat4;

////////////////////////////////////
// �J���[�x�N�g���\����

typedef struct
{
	GLfloat r;
	GLfloat g;
}Color2;

typedef struct
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
}Color3;

typedef struct
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
}Color4;

typedef struct
{
	GLubyte r;
	GLubyte g;
}bColor2;

typedef struct
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
}bColor3;

typedef struct
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
}bColor4;

////////////////////////////////////
// �U�C�Y�\����
typedef struct
{
	GLsizei  Width;
	GLsizei  Height;
}Size;

////////////////////////////////////

// �\����
typedef struct
{
	Mat4 ModelViewMatrix;		//���f���r���[�}�g���N�X�i�匳�̃}�g���N�X�f�[�^�j
	Mat4 ProjectionMatrix;		//�v���W�F�N�V�����}�g���N�X�i�匳�̃}�g���N�X�f�[�^�j
	GLfloat NearClip;			//�v���W�F�N�V�����}�g���N�X�������Ɏg�p����Near�l�i�匳�̃}�g���N�X�f�[�^�j
	GLfloat FarClip;			//�v���W�F�N�V�����}�g���N�X�������Ɏg�p����Far�l�i�匳�̃}�g���N�X�f�[�^�j
	Size WindowSize;			//�E�B���h�E�̑S�̃T�C�Y
	Vec3 Translate;				//�����ʒu�iX,Y,Z�j����̈ړ���
	Vec3 Rotate;				//�����ʒu�iX,Y,Z�j����̉�]��
}GlobalData;

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�{�֐��͊O�����烆�[�U�[���g�����Ƃ͂���܂���B
*	�@�G���[���b�Z�[�W��\���������ꍇ�́A�uERROR_MESSAGE�v�}�N�����g�p���Ă��Ă��������B
*
*	�@���s�s�\�ȃG���[�����������ꍇ�A���b�Z�[�W�{�b�N�X��\�����āA���Ń��Z�b�g����֐��ł��B
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/

inline void error_message_func(void)
{
	char* ErrorMessage = "���s�s�\�ȃG���[���������܂����B\n" \
						 "���̓R�}���h�v�����v�g���m�F���Ă��������B\n\n" \
						 "�֐��̌Ăяo���������������ꍇ�́A\n" \
						 "[error_message_func]�֐��̎��Ń��Z�b�g��L���ɂ��Ă��������B\n\n" \
						 "OK�������ƃv���O�������I�� ���� �f�o�b�O���܂��B";

	//���b�Z�[�W�{�b�N�X�\��
	MessageBox(NULL, ErrorMessage, "Error Message", MB_OK | MB_ICONSTOP);

	//�f�o�b�N�ŌĂяo��������������悤�Ɏ��Ń��Z�b�g������i�L���ɂ���ꍇ�̓R�����g���O���j
	//�G���[������������u���f�i�f�o�b�O�̒�~����Ȃ��j�v���āA
	//���j���[�o�[�́u�E�B���h�E�v���u�f�o�b�O�v���u�Ăяo�������v�Ŋ֐��R�[������������܂��B	
//	typedef char(*ResetFunc)(char);
//	ResetFunc test = (ResetFunc)0xFF;
//	test(0);

	//�v���O�������I������
	exit(EXIT_FAILURE);
}

#endif