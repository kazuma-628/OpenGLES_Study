#ifndef TEXTURE_H
#define TEXTURE_H

//include��`
#include "Common.h"
#include <gdiplus.h>

//#define��`
#define TEXTURE_FILE_DIR				"../Resource/"	//���\�[�X�t�@�C���̕ۑ��f�B���N�g��


typedef enum
{
	PIXELFORMAT_24BIT_RGB = PixelFormat24bppRGB,	//1�F��8bit�œ��ߏ�񂪊܂܂�Ă��Ȃ�PNG�`����BMP�`��JPG�`���ȂǁiGL_RGB�ɑ����j
	PIXELFORMAT_32BIT_RGBA = PixelFormat32bppARGB	//1�F��8bit�œ��ߏ�񂪊܂܂�Ă���PNG�`���ȂǁiGL_RGBA�ɑ����j
}PixelFotmat;

//�e�N�X�`���f�[�^�̏��
typedef struct
{
	//�e�ϐ���[glTexImage2D(3D,etc...)]�̈����ƂȂ���́i���̂܂܈����ɐݒ肷��Ηǂ��j
	GLint internalFormat;		//�s�N�Z�������t�H�[�}�b�g
	GLsizei width;				//��
	GLsizei height;				//����
	GLint border;				//OpenGL�Ƃ̌݊��̂��߂ɂ��鑶�݁iOpenGLES�͏��[0]�j
	GLenum format;				//�s�N�Z���t�H�[�}�b�g�i�s�N�Z�������t�H�[�}�b�g�Ɠ������̂��ݒ肳���j
	GLenum type;				//�s�N�Z�����̌^
	GLvoid *data;				//�s�N�Z���f�[�^
}TextureData;


class Texture
{

public:
	//�R���X�g���N�^
	Texture();

	//�f�X�g���N�^
	~Texture();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�摜�t�@�C������e�N�X�`���f�[�^�̓ǂݍ��݂��s���܂�
	*	����
	*	�@p_FileName	�F[I/ ]�@�ǂݍ��݂��s���g���q�t���̉摜�t�@�C����
	*							 [Resource]�t�H���_�ȍ~�̃t�@�C���p�X����͂��Ă��������B
	*							 �܂��A�f�B���N�g�����܂����Ƃ��́u/�v�ŋ�؂��Ă��������i��uxxx/xxx.vert�v�j
	*	�@p_PixelFotmat	�F[I/ ]�@�摜�t�@�C���̃t�H�[�}�b�g
	*							 [PIXELFORMAT_24BIT_RGB] or [PIXELFORMAT_32BIT_RGBA] �Ŏw��i�ڍׂ͒�`�����̃R�����g�Q�Ɓj
	*	�@p_TextureData	�F[ /O]�@�e�N�X�`���f�[�^
	*							 [TextureData]�\���̂�[PixelData]�͕s�v�ɂȂ������_�ŕK��[free]�Ń�����������Ă��������B
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	static void TextureDataLoad(const char* p_FileName, const PixelFotmat p_PixelFotmat, TextureData *p_TextureData);

private:

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�F���uBGR(A)�v���uRGB(A)�v�ɕϊ�����
	*	����
	*	�@p_PixelFotmat	�F[I/ ]�@�摜�t�@�C���̃t�H�[�}�b�g
	*							 PIXELFORMAT_24BIT_RGB or PIXELFORMAT_32BIT_RGBA �Ŏw��i�ڍׂ͒�`�����̃R�����g�Q�Ɓj
	*	�@p_BitmapData	�F[I/ ]�@�ϊ����̃e�N�X�`���f�[�^�iGdiplus::Bitmap �N���X�� LockBits�֐��œǂݍ��񂾂����f�[�^�j
	*	�@p_TextureData	�F[ /O]�@�ϊ���̃e�N�X�`���f�[�^�@
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	static void TextureDataBRGtoRGB(const int p_PixelFotmat, const Gdiplus::BitmapData* p_BitmapData, TextureData* p_TextureData);

};
#endif