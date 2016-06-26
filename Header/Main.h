#ifndef MAIN_H
#define MAIN_H

#include "Common.h"
#include "MainDraw.h"
#include "DeviceManager.h"
#include "WindowManager.h"
#include "ModelManager.h"

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�`��ɕK�v�Ȋe�����ݒ�/�X�V����
*	����
*	�@p_WindowManager		�F[I/ ]�@�E�B���h�E�Ǘ��I�u�W�F�N�g
*	�@p_DeviceManager		�F[I/ ]�@�f�o�C�X�Ǘ��I�u�W�F�N�g
*	�@p_Global				�F[ /O]�@�O���[�o���f�[�^
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void SetVarietyOfInformation(WindowManager *p_WindowManager, DeviceManager *p_DeviceManager, GlobalData *p_Global);

#endif