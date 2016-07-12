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


////////////////////////////////////////
// Define�x�N�g���\����

//���s�s�\�ȃG���[�����������ꍇ�̃��b�Z�[�W�o�͗p��`
#define ERROR_MESSAGE(Message)		error_message_func(Message, __FILE__, __FUNCTION__ ,__LINE__);

//���s�s�\�ȃG���[�̉\�������邪�A�f�o�b�O���͈ꎞ�I�ɃG���[�ɂȂ�\��������ꍇ�̃��b�Z�[�W�o�͒�`
//�f�o�b�N���̓��b�Z�[�W��L���ɂ���Ƒ�ʂ̃��b�Z�[�W���o�͂����\��������܂��̂ŁA
//�ŏI�I�ɓ��삪��肭�����Ȃ��Ȃǂ̃G���[�m�F�̎��̂݃R�����g���O���Č��Ă�������
#define ERROR_MESSAGE_SUB(...)		//printf(__VA_ARGS__); error_message_sub_func(__FILE__, __FUNCTION__ ,__LINE__);

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
	Mat4 ModelViewMatrix;		//���C���ƂȂ郂�f���r���[�}�g���N�X�i�匳�̃}�g���N�X�f�[�^�j
	Mat4 ProjectionMatrix;		//���C���ƂȂ�v���W�F�N�V�����}�g���N�X�i�匳�̃}�g���N�X�f�[�^�j
	Size WindowSize;					//�E�B���h�E�̑S�̃T�C�Y
	Vec3 Translate;						//�����ʒu�iX,Y,Z�j����̈ړ���
	Vec3 Rotate;						//�����ʒu�iX,Y,Z�j����̉�]��
}GlobalData;

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�{�֐��͊O�����烆�[�U�[���g�����Ƃ͂���܂���B
*	�@�{�G���[���b�Z�[�W��\���������ꍇ�́A�uERROR_MESSAGE�v�}�N�����g�p���Ă��Ă��������B
*	�@�{�}�N���̈Ӗ��ɂ��ẮA�uDefine�v��`�̃R�����g���m�F���Ă��������B
*
*	�@���s�s�\�ȃG���[�����������ꍇ�A���b�Z�[�W�{�b�N�X��\�����āA���Ń��Z�b�g����֐��ł��B
*	�@
*	����
*	�@Message	�F[I/ ]�@���b�Z�[�W�{�b�N�X�ɕ\���������G���[���b�Z�[�W
*	�@File		�F[I/ ]�@�G���[�����������t�@�C����
*	�@Line		�F[I/ ]�@�G���[�����������s��
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
//Define��`
#define ERR_ALL_MES_MAX 512		//�G���[���b�Z�[�W�̑S���̍ő啶����
#define ERR_TMP_MES_MAX 256		//�G���[���b�Z�[�W�̃e���v�̈�̍ő啶����

inline void error_message_func(const char* Message, const char* File, const char* func, const int Line)
{
	char All_Message[ERR_ALL_MES_MAX] = { 0 };
	char tmp_char[ERR_TMP_MES_MAX] = { 0 };
	char* Err_Message = "\n\n���s�s�\�ȃG���[���������܂����B\n"\
						"���̓R�}���h�v�����v�g���m�F���Ă��������B\n\n";

	//�G���[�����������t�@�C���ƍs���𕶎���Ƃ��Đ���
	sprintf(tmp_char, "%s%s\n%s%s\n%s%d", "�t�@�C���F", File, "�֐����F", func, "�s���F", Line);
	
	//�f�o�b�N���̊e�����������
	strcat_s(All_Message, sizeof(All_Message), Message);
	strcat_s(All_Message, sizeof(All_Message), Err_Message);
	strcat_s(All_Message, sizeof(All_Message), tmp_char);

	//���b�Z�[�W�{�b�N�X�\��
	MessageBox(NULL, All_Message, "Debug Message", MB_OK | MB_ICONSTOP);

	//�f�o�b�N�ŌĂяo��������������悤�Ɏ��Ń��Z�b�g������i�L���ɂ���ꍇ�̓R�����g���O���j
	//�G���[������������u���f�i�f�o�b�O�̒�~����Ȃ��j�v���āA
	//���j���[�o�[�́u�E�B���h�E�v���u�f�o�b�O�v���u�Ăяo�������v�Ŋ֐��R�[������������܂��B	
//	typedef char(*ResetFunc)(char);
//	ResetFunc test = (ResetFunc)0xFF;
//	test(0);

	exit(EXIT_FAILURE);		//�v���O�������I������
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�{�֐��͊O�����烆�[�U�[���g�����Ƃ͂���܂���B
*	�@�{�G���[���b�Z�[�W��\���������ꍇ�́A�uERROR_MESSAGE_SUB�v�}�N�����g�p���Ă��Ă��������B
*	�@�{�}�N���̈Ӗ��ɂ��ẮA�uDefine�v��`�̃R�����g���m�F���Ă��������B
*
*	�@���s�s�\�ȃG���[�̉\�������邪�A�f�o�b�O���͈ꎞ�I�ɃG���[�ɂȂ�\��������ꍇ�A
*	�@���b�Z�[�W�{�b�N�X��\�����āA���Ń��Z�b�g����֐��ł��B
*	�@
*	����
*	�@File			�F[I/ ]�@�G���[�����������t�@�C����
*	�@Line			�F[I/ ]�@�G���[�����������s��
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
inline void error_message_sub_func(const char* File, const char* func, const int Line)
{
	//���b�Z�[�W�{�b�N�X�ւ̃G���[���b�Z�[�W�̍쐬
	char *Message = "Attribute/Uniform�ϐ��̃��P�[�V���������A\n"\
		"�������̓f�[�^�̑��M�i�֘A�t���j�Ɏ��s���܂����B";

	//�f�o�b�O���Ƌ��Ƀ��b�Z�[�W�{�b�N�X��\������
	error_message_func(Message, File, func, Line);
}

#endif