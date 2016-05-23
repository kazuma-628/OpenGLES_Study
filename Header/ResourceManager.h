#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

//include��`
#include "Common.h"
#include <gdiplus.h>

//#define��`

#define PIXELFORMAT_24BIT_RGB	(PixelFormat24bppRGB)	//���ߏ�񂪊܂܂�Ă��Ȃ�PNG�`����BMP�`��JPG�`���Ȃ�
														//�uglTexImage2D�v�Ȃǂł́uGL_RGB�v���w�肷�邱��
#define PIXELFORMAT_32BIT_RGBA	(PixelFormat32bppARGB)	//���ߏ�񂪊܂܂�Ă���PNG�`���Ȃ�
														//�uglTexImage2D�v�Ȃǂł́uGL_RGBA�v���w�肷�邱��
#define TEXTURE_DATA_MAX			128			//�e�N�X�`���Ǘ��p�̍ő吔
#define TEXTURE_FILE_NAME_MAX		64			//�e�N�X�`���t�@�C�����̍ő啶�����i�f�B���N�g���܂ށj


//�e�N�X�`���f�[�^�̏��
typedef struct
{
	char Name[TEXTURE_FILE_NAME_MAX];
	unsigned int Width;		//��
	unsigned int Height;	//����
	int PixelFormat;		//�s�N�Z���t�H�[�}�b�g
	void* PixelData;		//�s�N�Z���f�[�^
}TextureData;


class ResourceManager
{

public:
	//�R���X�g���N�^
	ResourceManager();

	//�f�X�g���N�^
	~ResourceManager();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�摜�t�@�C������e�N�X�`���f�[�^�̓ǂݍ��݂��s���܂�
	*	����
	*	�@p_FileName	�F[I/ ]�@�ǂݍ��݂��s���g���q�t���̉摜�t�@�C�����i[��] texture.png�j
	*								���� Resource�t�H���_�Ɋi�[����Ă���K�v������܂� ��
	*	�@p_PixelFotmat	�F[I/ ]�@�摜�t�@�C���̃t�H�[�}�b�g
	*							 PIXELFORMAT_24BIT_RGB or PIXELFORMAT_32BIT_RGBA �Ŏw��i�ڍׂ͒�`�����̃R�����g�Q�Ɓj
	*	�߂�l
	*	�@�e�N�X�`���f�[�^�i��,����,�s�N�Z���f�[�^�Ȃ� �� �ڍׂ�[TextureData]�\���̎Q�Ɓj
	*-------------------------------------------------------------------------------*/
	TextureData* TextureDataLoad(const char* p_FileName, const int p_PixelFotmat);

private:

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@���ɉ摜�t�@�C������e�N�X�`���f�[�^�̓ǂݍ��݂��������Ă��邩�������܂�
	*	����
	*	�@p_FileName	�F[I/ ]�@�ǂݍ��݂��s���g���q�t���̉摜�t�@�C�����i[��] texture.png�j�@
	*	�߂�l
	*	�@�e�N�X�`���f�[�^�����ɓǂݍ���ł���ꍇ 
	*		���e�N�X�`���f�[�^�i��,����,�s�N�Z���f�[�^�Ȃ� �� �ڍׂ�[TextureData]�\���̎Q�Ɓj
	*	�@�e�N�X�`���f�[�^���܂��ǂݍ��܂�Ă��Ȃ��ꍇ
	*		��NULL
	*-------------------------------------------------------------------------------*/
	TextureData* TextureDataSearch(const char* p_FileName);

	TextureData m_TextureData[TEXTURE_DATA_MAX];	//�e�N�X�`���Ǘ��p�̕ϐ�
	int m_AttribInfoIndex;							//�e�N�X�`���ϐ��Ǘ��p�̃C���f�b�N�X�l


	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�F���uBGR(A)�v���uRGB(A)�v�ɕϊ�����
	*	����
	*	�@p_BitmapData	�F[I/ ]�@�ϊ����̃e�N�X�`���f�[�^�iGdiplus::Bitmap �N���X�� LockBits�֐��œǂݍ��񂾂����f�[�^�j
	*	�@p_TextureData	�F[ /O]�@�ϊ���̃e�N�X�`���f�[�^�@
	*	�@p_PixelFotmat	�F[I/ ]�@�摜�t�@�C���̃t�H�[�}�b�g
	*							 PIXELFORMAT_24BIT_RGB or PIXELFORMAT_32BIT_RGBA �Ŏw��i�ڍׂ͒�`�����̃R�����g�Q�Ɓj
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void TextureDataBRGtoRGB(const Gdiplus::BitmapData* p_BitmapData, TextureData* p_TextureData, const int p_PixelFotmat);

};
#endif