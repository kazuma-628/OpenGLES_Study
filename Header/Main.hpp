//include��`
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <glew.h>
#include <glfw3.h>

//Define��`
#define SHADER_STRING_LINE_MAX		256			//�V�F�[�_�[��1�s�̍ő啶����
#define SHADER_STRING_ALL_MAX		10240		//�V�F�[�_�[�̑S���̍ő啶����
#define SHADER_FILE_NAME_MAX		64			//�V�F�[�_�[�̃t�@�C�����ő啶�����i�f�B���N�g�����܂ށj
#define WINDOW_HEIGHT				480
#define WINDOW_WIDTH				640

//�֐���`
GLFWwindow *const OpenGLES_init();		//OpenGL�̏��������s��
GLint Shader_SourceLoad(const char* shader_source, const GLenum GL_XXXX_SHADER);		//�V�F�[�_�[�\�[�X�̓ǂݍ��݂��s��
void Shader_FileLoad(const char* shader_name, char* shader_source, int source_size);	//�V�F�[�_�[�t�@�C���̓ǂݍ��݂��s��
GLuint Shader_CreateProgram(const char* vertex_shader_file, const char* fragment_shader_file);	//���_�E�t���O�����g�V�F�[�_�[�������N���AShaderProgram���쐬����