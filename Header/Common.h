#ifndef COMMON_H
#define COMMON_H

//include��`�i�قƂ�ǂ̃t�@�C���ŕK�v�ɂȂ�͂��Ȃ̂ňꊇ��`�j
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <glew.h>
#include <glfw3.h>

//���s�s�\�ȃG���[�����������ꍇ�̃��b�Z�[�W�o�͗p��`
#define ERROR_MESSAGE(Message) (error_message_func(Message, __FILE__ ,__LINE__))


/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�{�֐��͊O�����烆�[�U�[���g�����Ƃ͂���܂���B
*	�@�G���[���b�Z�[�W��\���������ꍇ�́A�uERROR_MESSAGE�v�}�N�����g�p���Ă��Ă��������B
*
*	�@���s�s�\�ȃG���[�����������ꍇ�A���b�Z�[�W�{�b�N�X��\�����āA���Ń��Z�b�g����֐��ł��B
*	�@
*	����
*	�@Message	�F[I/ ]�@�\���������G���[���b�Z�[�W
*	�@File		�F[I/ ]�@�G���[�����������t�@�C����
*	�@Line		�F[I/ ]�@�G���[�����������s��
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
//Define��`
#define ERR_ALL_MES_MAX 512		//�G���[���b�Z�[�W�̑S���̍ő啶����
#define ERR_TMP_MES_MAX 256		//�G���[���b�Z�[�W�̃e���v�̈�̍ő啶����

inline void error_message_func(char* Message, char* File, int Line)
{
	char All_Message[ERR_ALL_MES_MAX] = { 0 };
	char tmp_char[ERR_TMP_MES_MAX] = { 0 };
	char* Err_Message = "\n\n���s�s�\�ȃG���[���������܂����B\n"\
						"���̓R�}���h�v�����v�g���m�F���Ă��������B\n\n";

	//�G���[�����������t�@�C���ƍs���𕶎���Ƃ��Đ���
	sprintf_s(tmp_char, sizeof(tmp_char), "%s%s\n%s%d", "�t�@�C���F", File, "�s���F", Line);
	
	//�f�o�b�N���̕����������
	strcat_s(All_Message, sizeof(All_Message), Message);
	strcat_s(All_Message, sizeof(All_Message), Err_Message);
	strcat_s(All_Message, sizeof(All_Message), tmp_char);

	//���b�Z�[�W�{�b�N�X�\��
	MessageBox(NULL, All_Message, "Debug Message", MB_OK | MB_ICONSTOP);

	//�f�o�b�N�ŌĂяo��������������悤�Ɏ��Ń��Z�b�g
	//�G���[������������u���f�i�f�o�b�O�̒�~����Ȃ��j�v���āA
	//���j���[�o�[�́u�E�B���h�E�v���u�f�o�b�O�v���u�Ăяo�������v�Ŋ֐��R�[�������������܂��B
	free((void*)0xFF);		
	
	exit(EXIT_FAILURE);		//�v���O�������I������i���Ń��Z�b�g�ł����܂ŗ��邱�Ƃ͂Ȃ��Ǝv�����ǁB�B�B�j
}

#endif