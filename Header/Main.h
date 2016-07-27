#ifndef MAIN_H
#define MAIN_H

#include "Common.h"
#include "MainDraw.h"
#include "DeviceManager.h"
#include "WindowManager.h"
#include "ModelManager.h"

//define
#define RotateSpeedWeight		2.0f		//��]���x�̏d�݁i�l���傫���قǉ�]���x�͒x���Ȃ�j
#define InertiaRotateWeight		0.3f		//�Đ���]�ʂ̏d�݁i�l���傫���قǑĐ��ړ��ʂ͑����Ȃ�j
#define InertiaTranslateWeight	0.3f		//�Đ��ړ��ʂ̏d�݁i�l���������قǑĐ���]�ʂ͑����Ȃ�j

//�\����
typedef struct
{
	Vec2 OldPosition;				//�y1�C�x���g�O�z�}�E�X�̃J�[�\�����W
	Vec2 OldScrollAmount;			//�y1�C�x���g�O�z�X�N���[���̍��v�ʁA������Ԃ�[x:0�i��[���E]�X�N���[���j][y:0�i�c[�㉺]�X�N���[���j]�ŁA
									//�@�X�N���[�������������l���~�ρi���Z/���Z�j����Ă���
	int	OldLeftState;				//�y1�C�x���g�O�z�}�E�X�̍��N���b�N�̏��
	int	OldRightState;				//�y1�C�x���g�O�z�}�E�X�̉E�N���b�N�̏��
	Vec3 InertiaTranslate;			// �Đ��ɔ���1�C�x���g���̈ړ��ʁi�t���b�N����ƃt���b�N���x�ɉ������l�����菙�X��[0]�ɂȂ�A�}�E�X�𓮂����Ȃ����[0]�j
	Vec3 InertiaRotate;				// �Đ��ɔ���1�C�x���g���̉�]�ʁi�t���b�N����ƃt���b�N���x�ɉ������l�����菙�X��[0]�ɂȂ�A�}�E�X�𓮂����Ȃ����[0]�j
}TmpGlobalData;

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