#include "ResourceManager.h"

//�R���X�g���N�^
ResourceManager::ResourceManager()
{
	m_AttribInfoIndex = 0;
	memset(m_TextureData, 0, sizeof(m_TextureData));
}

//�f�X�g���N�^
ResourceManager::~ResourceManager()
{
	//�ǂݍ��ݍς݂�����������
	for (int index = 0; index < TEXTURE_DATA_MAX; index++)
	{
		if (0 == strlen(m_TextureData[index].Name))
		{
			//�ǂݍ��ݍς݂̉摜�f�[�^�͊J������
			free(m_TextureData[index].PixelData);
		}
	}
}

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
TextureData* ResourceManager::TextureDataLoad(const char* p_FileName, const PixelFotmat p_PixelFotmat)
{

	//�ꎞ�I�Ɏg�p����e�N�X�`���f�[�^�ϐ�
	TextureData* t_TextureData;

	//���ɉ摜�t�@�C������e�N�X�`���f�[�^�̓ǂݍ��݂��������Ă��邩����
	t_TextureData = TextureDataSearch(p_FileName);

	//���ɓǂݍ��ݍς݂̏ꍇ
	if (NULL != t_TextureData)
	{
		//�ǂݍ��ݍς݂̃e�N�X�`���f�[�^��ԋp
		return t_TextureData;
	}
	else
	{
		printf("�e�N�X�`���u%s�v�̐V�K�ǂݍ��݂��J�n���܂�...", p_FileName);

		//GDI+�̏�����
		ULONG_PTR token;
		Gdiplus::GdiplusStartupInput input;
		Gdiplus::GdiplusStartup(&token, &input, NULL);

		char Dir_FileName[TEXTURE_FILE_NAME_MAX] = SHADER_FILE_DIR;

		strcat(Dir_FileName, p_FileName);

		//�e�N�X�`�����ǂݍ��݁i�}���`�o�C�g������ �� ���C�h������ɕϊ��܂ށj
		wchar_t wchar_FileName[TEXTURE_FILE_NAME_MAX] = { 0 };
		size_t length;
		mbstowcs_s(&length, wchar_FileName, Dir_FileName, TEXTURE_FILE_NAME_MAX);
		Gdiplus::Bitmap* Texture = new Gdiplus::Bitmap(wchar_FileName);

		//�e�N�X�`���f�[�^�ǂݍ���
		Gdiplus::BitmapData BitmapData;
		if (0 != Texture->LockBits(0, Gdiplus::ImageLockModeRead, p_PixelFotmat, &BitmapData))
		{
			printf("���s\n");
			ERROR_MESSAGE("�e�N�X�`���t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n"\
				"�uResource�v�t�H���_�Ɋi�[����Ă��܂����H\n"\
				"�t�@�C�������Ԉ���Ă��܂��񂩁H");
		}

		/////////////////////////////////////////////////
		// �ԋp������̐ݒ�

		memmove(m_TextureData[m_AttribInfoIndex].Name, p_FileName, strlen(p_FileName));
		m_TextureData[m_AttribInfoIndex].Width = BitmapData.Width;
		m_TextureData[m_AttribInfoIndex].Height = BitmapData.Height;
		m_TextureData[m_AttribInfoIndex].PixelFormat = BitmapData.PixelFormat;
		m_TextureData[m_AttribInfoIndex].PixelData = calloc(BitmapData.Height * BitmapData.Stride, sizeof(byte));

		//���[�h�����e�N�X�`���́uBGR�v�Ŋi�[����Ă���̂ŁuRGB�v�ɕϊ����R�s�[����
		TextureDataBRGtoRGB(&BitmapData, m_TextureData, p_PixelFotmat);

		//����ݒ肵���̂Ńe�N�X�`���ϐ��Ǘ��p�̃C���f�b�N�X�l���C���N�������g����
		m_AttribInfoIndex++;

		//�ǂݍ��񂾃e�N�X�`�����/�f�[�^��j������
		Texture->UnlockBits(&BitmapData);
		delete Texture;

		//GDI+�̏I��
		Gdiplus::GdiplusShutdown(token);

		printf("����\n");
	}

	//����ݒ肵���f�[�^��ԋp
	return &m_TextureData[m_AttribInfoIndex - 1];
}

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@���ɉ摜�t�@�C������e�N�X�`���f�[�^�̓ǂݍ��݂��������Ă��邩�������܂�
*	�@�ǂݍ��݂��������Ă���ꍇ�͂��̃f�[�^��Ԃ��܂�
*	����
*	�@p_FileName	�F[I/ ]�@�ǂݍ��݂��s���g���q�t���̉摜�t�@�C�����i[��] texture.png�j�@
*	�߂�l
*	�@�e�N�X�`���f�[�^�����ɓǂݍ���ł���ꍇ
*		���e�N�X�`���f�[�^�i��,����,�s�N�Z���f�[�^�Ȃ� �� �ڍׂ�[TextureData]�\���̎Q�Ɓj
*	�@�e�N�X�`���f�[�^���܂��ǂݍ��܂�Ă��Ȃ��ꍇ
*		��NULL
*-------------------------------------------------------------------------------*/
TextureData* ResourceManager::TextureDataSearch(const char* p_FileName)
{
	//�ǂݍ��ݍς݂�����������
	for (int index = 0; index < TEXTURE_DATA_MAX; index++)
	{
		if (0 == strncmp(m_TextureData[index].Name, p_FileName, TEXTURE_FILE_NAME_MAX))
		{
			return &m_TextureData[index];
		}
	}

	return NULL;
}

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
void ResourceManager::TextureDataBRGtoRGB(const Gdiplus::BitmapData* p_BitmapData, TextureData* p_TextureData, const int p_PixelFotmat)
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
			memmove((byte*)m_TextureData[m_AttribInfoIndex].PixelData + DataPos, (byte*)p_BitmapData->Scan0 + DataPos + 2, sizeof(byte));

			//G�������ꎞ�I�ɕۑ�
			memmove((byte*)m_TextureData[m_AttribInfoIndex].PixelData + DataPos + 1, (byte*)p_BitmapData->Scan0 + DataPos + 1, sizeof(byte));

			//B�������ꎞ�I�ɕۑ�
			memmove((byte*)m_TextureData[m_AttribInfoIndex].PixelData + DataPos + 2, (byte*)p_BitmapData->Scan0 + DataPos, sizeof(byte));
		}
	}
}