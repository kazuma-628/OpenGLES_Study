#include "Texture.h"
#include <locale.h>

//�R���X�g���N�^
Texture::Texture()
{

}

//�f�X�g���N�^
Texture::~Texture()
{

}

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
void Texture::TextureDataLoad(const char* p_FileName, const PixelFotmat p_PixelFotmat, TextureData *p_TextureData)
{
	printf("�e�N�X�`���u%s�v�̐V�K�ǂݍ��݂��J�n���܂�...", p_FileName);

	//�����`�F�b�N
	if (NULL == p_FileName || NULL == p_TextureData)
	{
		printf("���s\n");
		ERROR_MESSAGE("�e�N�X�`���f�[�^�̓ǂݍ��� �����G���[\n" \
			"p_FileName = %s, p_TextureData = %x\n" \
			, p_FileName, (unsigned int)p_TextureData);
		return;
	}

	//////////////////////////////////////////
	// �e�N�X�`���t�@�C���ւ̃p�X�i���C�h�����j���쐬

	char *texture_dir_file_name = NULL;			//�e�N�X�`���t�@�C���ւ̃p�X�i�}���`�o�C�g�����j
	wchar_t *w_texture_dir_file_name = NULL;	//�e�N�X�`���t�@�C���ւ̃p�X�i���C�h�����j
	int StrLength = 0;		//�ǂݍ��ރe�N�X�`���t�@�C�����̒����i�o�C�g���j

							// ������̒������擾���ă������m�ہi�I�[�𖾊m�ɂ��邽�� +1 ����B[\0]�ƂȂ�j
	StrLength = strlen(TEXTURE_FILE_DIR) + strlen(p_FileName);
	texture_dir_file_name = (char*)calloc(StrLength + 1, sizeof(char));

	//�e�N�X�`���t�@�C���ւ̃p�X�𐶐�����i�}���`�o�C�g�����j
	sprintf(texture_dir_file_name, "%s%s", TEXTURE_FILE_DIR, p_FileName);

	//���P�[������{�ɐݒ�
	setlocale(LC_CTYPE, "jpn");

	//�}���`�o�C�g�����̕��������擾���āA���C�h�����ɕϊ������ꍇ�̃o�C�g�����Z�o����
	StrLength = _mbstrlen(texture_dir_file_name) * 2;

	// ������̒������擾���ă������m�ہi�I�[�𖾊m�ɂ��邽�� +2(���C�h�����Ȃ̂�) ����B[\0]�ƂȂ�j
	w_texture_dir_file_name = (wchar_t*)calloc(StrLength + 2, sizeof(char));

	//�}���`�o�C�g������ �� ���C�h������ɕϊ��܂�
	mbstowcs(w_texture_dir_file_name, texture_dir_file_name, _mbstrlen(texture_dir_file_name));

	//////////////////////////////////////////
	// [GDI+]���g�p���ăe�N�X�`����ǂݍ���

	//GDI+�̏�����
	ULONG_PTR token;
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&token, &input, NULL);

	//�e�N�X�`���ǂݍ���
	Gdiplus::Bitmap* Texture = new Gdiplus::Bitmap(w_texture_dir_file_name);

	//�e�N�X�`����ǂݍ��񂾂̂Ńt�@�C���p�X��ۑ����Ă������������J������
	free(texture_dir_file_name);
	free(w_texture_dir_file_name);

	//�e�N�X�`���f�[�^�ǂݍ���
	Gdiplus::BitmapData BitmapData;
	if (0 != Texture->LockBits(0, Gdiplus::ImageLockModeRead, p_PixelFotmat, &BitmapData))
	{
		printf("���s\n");
		ERROR_MESSAGE("�e�N�X�`���t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n"\
			"�uResource�v�t�H���_�Ɋi�[����Ă��܂����H\n"\
			"�t�@�C�������Ԉ���Ă��܂��񂩁H");
		return;
	}

	/////////////////////////////////////////////////
	// �ԋp������̐ݒ�
	switch (p_PixelFotmat)
	{
	case PIXELFORMAT_24BIT_RGB:
		p_TextureData->internalFormat = GL_RGB;
		p_TextureData->format = GL_RGB;
		break;

	case PIXELFORMAT_32BIT_RGBA:
		p_TextureData->internalFormat = GL_RGBA;
		p_TextureData->format = GL_RGBA;
		break;
	default:
		printf("���s\n");
		ERROR_MESSAGE("�s�N�Z���t�H�[�}�b�g�̈������s���ł��B\n"\
			"p_PixelFotmat = %d", p_PixelFotmat);
		return;
	}

	p_TextureData->width = (GLsizei)BitmapData.Width;
	p_TextureData->height = (GLsizei)BitmapData.Height;
	p_TextureData->border = 0;
	p_TextureData->type = GL_UNSIGNED_BYTE;
	p_TextureData->data = (GLvoid*)calloc(BitmapData.Height * BitmapData.Stride, sizeof(byte));

	//���[�h�����e�N�X�`���́uBGR�v�Ŋi�[����Ă���̂ŁuRGB�v�ɕϊ����R�s�[����
	TextureDataBRGtoRGB(p_PixelFotmat, &BitmapData, p_TextureData);

	//�ǂݍ��񂾃e�N�X�`�����/�f�[�^��j������
	Texture->UnlockBits(&BitmapData);
	delete Texture;

	//GDI+�̏I��
	Gdiplus::GdiplusShutdown(token);

	printf("����\n");
}


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
void Texture::TextureDataBRGtoRGB(const int p_PixelFotmat, const Gdiplus::BitmapData* p_BitmapData, TextureData* p_TextureData)
{
	//1�F���̏��̃o�C�g��
	int ColorByte = 0;

	//�摜�̃t�H�[�}�b�g����1�F���̏��̃o�C�g��������
	if (PIXELFORMAT_24BIT_RGB == p_PixelFotmat)
	{
		ColorByte = 3;
	}
	else if (PIXELFORMAT_32BIT_RGBA)
	{
		ColorByte = 4;
	}

	//�����s�N�Z�����J��Ԃ�
	for (unsigned int Height = 0; Height < p_BitmapData->Height; Height++)
	{
		//���s�N�Z�� �~ �J���[�F���J��Ԃ��i�����̕ϊ��ʂƂȂ�j
		for (unsigned int Width = 0; Width < p_BitmapData->Width * ColorByte; Width = Width + ColorByte)
		{
			//�ϊ�����1��f�̐擪�ʒu���Z�o����
			//�i�摜��4 �o�C�g���E���ӎ����Ċi�[����Ă���̂ł�����l������j
			unsigned int DataPos = (Height * p_BitmapData->Stride) + Width;

			//R�������R�s�[
			memmove((byte*)p_TextureData->data + DataPos, (byte*)p_BitmapData->Scan0 + DataPos + 2, sizeof(byte));

			//G�������ꎞ�I�ɕۑ�
			memmove((byte*)p_TextureData->data + DataPos + 1, (byte*)p_BitmapData->Scan0 + DataPos + 1, sizeof(byte));

			//B�������ꎞ�I�ɕۑ�
			memmove((byte*)p_TextureData->data + DataPos + 2, (byte*)p_BitmapData->Scan0 + DataPos, sizeof(byte));
		}
	}
}