//include��`
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <glew.h>
#include <glfw3.h>

//Define��`
#define WINDOW_HEIGHT				480			//�E�B���h�E�T�C�Y�i�����j
#define WINDOW_WIDTH				640			//�E�B���h�E�T�C�Y�i���j
#define SHADER_STRING_LINE_MAX		256			//�V�F�[�_�[��1�s�̍ő啶����
#define SHADER_STRING_ALL_MAX		10240		//�V�F�[�_�[�̑S���̍ő啶����
#define SHADER_FILE_NAME_MAX		64			//�V�F�[�_�[�̃t�@�C�����ő啶�����i�f�B���N�g�����܂ށj


//�֐���`
/*-------------------------------------------------------------------------------
*	�֐�����
*	�@OpenGL�̏��������s��
*	����
*	�@�Ȃ�
*	�߂�l
*	�@�E�B���h�E�n���h��
*-------------------------------------------------------------------------------*/
GLFWwindow *const OpenGLES_init();

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@���_�E�t���O�����g�V�F�[�_�[�������N���AShaderProgram���쐬����
*	����
*	�@vertex_shader_file	�F[I/ ]�@�o�[�e�b�N�X�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
*	�@fragment_shader_file	�F[I/ ]�@�t���O�����g�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
*	�߂�l
*	�@�����N�ς݂̃v���O����
*-------------------------------------------------------------------------------*/
GLuint Shader_CreateProgram(const char* vertex_shader_file, const char* fragment_shader_file);

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�V�F�[�_�[�t�@�C���̓ǂݍ��݂��s��
*	����
*	�@shader_file_name	�F[I/ ]�@�e�V�F�[�_�[�̃t�@�C�����iShader�t�H���_�Ɋi�[����Ă���K�v������܂��j
*	�@shader_source		�F[ /O]�@�e�V�F�[�_�[�̃\�[�X�f�[�^
*	�@source_size		�F[I/ ]�@�V�F�[�_�[�̑S���̍ő啶����
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
void Shader_FileLoad(const char* shader_file_name, char* shader_source, int source_size);

/*-------------------------------------------------------------------------------
*	�֐�����
*	�@�V�F�[�_�[�\�[�X�̓ǂݍ��݂��s��
*	����
*	�@shader_source		�F[I/ ]�@�e�V�F�[�_�[�̃\�[�X�f�[�^
*	�@gl_xxxx_shader	�F[I/ ]�@�쐬����V�F�[�_�[�I�u�W�F�N�g�i�o�[�e�b�N�X or �t���O�����g�j
*	�߂�l
*	�@�Ȃ�
*-------------------------------------------------------------------------------*/
GLint Shader_SourceLoad(const char* shader_source, const GLuint gl_xxxx_shader);