#ifndef SHADERCREATEPROGRAM_H
#define SHAdERCREATEPROGRAM_H

//include��`
#include "Common.h"

//Define��`
#define SHADER_STRING_LINE_MAX		256			//�V�F�[�_�[��1�s�̍ő啶����
#define SHADER_STRING_ALL_MAX		10240		//�V�F�[�_�[�̑S���̍ő啶����
#define SHADER_FILE_NAME_MAX		64			//�V�F�[�_�[�̃t�@�C�����ő啶�����i�f�B���N�g�����܂ށj

class ShaderManager
{

public:

	//�R���X�g���N�^
	ShaderManager::ShaderManager();

	//�f�X�g���N�^
	ShaderManager::~ShaderManager();

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@���_�E�t���O�����g�V�F�[�_�[�������N���AShaderProgram���쐬����
	*	����
	*	�@p_vertex_shader_file		�F[I/ ]�@�o�[�e�b�N�X�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
	*	�@p_fragment_shader_file	�F[I/ ]�@�t���O�����g�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void CreateShaderProgram(const char* p_vertex_shader_file, const char* p_fragment_shader_file);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@Attribute�ϐ��̃��P�[�V����ID�𐶐��i�ق� glGetAttribLocation �Ɠ����ł��j
	*	�@������₷���悤�Ɉ��������Ȃ������̂ƁA�G���[�Ǘ����ꌳ�������_���Ⴄ�݂̂ł��B
	*	����
	*	�@p_attribute_name			�F[I/ ]�@�V�F�[�_�[�Ŏg�p����Attribute�ϐ��̖��O
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	GLint GetAttribLocation(const GLchar* p_attribute_name);

	//�V�F�[�_�[�v���O�����ԋp
	inline GLint GetShaderProgram()	{ return m_ShaderProgram; }

private:

	//�ϐ���`
	GLint m_ShaderProgram;		//�v���O�����I�u�W�F�N�g
	char m_vertex_shader_file[SHADER_FILE_NAME_MAX];	//�o�[�e�b�N�X�V�F�[�_�[�t�@�C����
	char m_fragment_shader_file[SHADER_FILE_NAME_MAX];	//�t���O�����g�V�F�[�_�[�t�@�C����

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�V�F�[�_�[�t�@�C���̓ǂݍ��݂��s��
	*	����
	*	�@p_shader_file_name	�F[I/ ]�@�e�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
	*	�@p_shader_source		�F[ /O]�@�e�V�F�[�_�[�̃\�[�X�f�[�^
	*	�@p_source_size			�F[I/ ]�@�V�F�[�_�[�̑S���̍ő啶����
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	void Shader_FileLoad(const char* p_shader_file_name, char* p_shader_source, const int p_source_size);

	/*-------------------------------------------------------------------------------
	*	�֐�����
	*	�@�V�F�[�_�[�\�[�X�̓ǂݍ��݂��s��
	*	����
	*	�@p_shader_source		�F[I/ ]�@�e�V�F�[�_�[�̃\�[�X�f�[�^
	*	�@p_gl_xxxx_shader		�F[I/ ]�@�쐬����V�F�[�_�[�I�u�W�F�N�g�i�o�[�e�b�N�X or �t���O�����g�j
	*	�߂�l
	*	�@�Ȃ�
	*-------------------------------------------------------------------------------*/
	GLint Shader_SourceLoad(const char* p_shader_source, const GLuint p_gl_xxxx_shader);
};
#endif