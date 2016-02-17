//include定義
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <glew.h>
#include <glfw3.h>

//Define定義
#define SHADER_STRING_LINE_MAX		256			//シェーダーの1行の最大文字数
#define SHADER_STRING_ALL_MAX		10240		//シェーダーの全文の最大文字数
#define SHADER_FILE_NAME_MAX		64			//シェーダーのファイル名最大文字数（ディレクトリ名含む）
#define WINDOW_HEIGHT				480
#define WINDOW_WIDTH				640

//関数定義
GLFWwindow *const OpenGLES_init();		//OpenGLの初期化を行う
GLint Shader_SourceLoad(const char* shader_source, const GLenum GL_XXXX_SHADER);		//シェーダーソースの読み込みを行う
void Shader_FileLoad(const char* shader_name, char* shader_source, int source_size);	//シェーダーファイルの読み込みを行う
GLuint Shader_CreateProgram(const char* vertex_shader_file, const char* fragment_shader_file);	//頂点・フラグメントシェーダーをリンクし、ShaderProgramを作成する