//include定義
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <glew.h>
#include <glfw3.h>

//Define定義
#define WINDOW_HEIGHT				480			//ウィンドウサイズ（高さ）
#define WINDOW_WIDTH				640			//ウィンドウサイズ（幅）
#define SHADER_STRING_LINE_MAX		256			//シェーダーの1行の最大文字数
#define SHADER_STRING_ALL_MAX		10240		//シェーダーの全文の最大文字数
#define SHADER_FILE_NAME_MAX		64			//シェーダーのファイル名最大文字数（ディレクトリ名含む）


//関数定義
/*-------------------------------------------------------------------------------
*	関数説明
*	　OpenGLの初期化を行う
*	引数
*	　なし
*	戻り値
*	　ウィンドウハンドル
*-------------------------------------------------------------------------------*/
GLFWwindow *const OpenGLES_init();

/*-------------------------------------------------------------------------------
*	関数説明
*	　頂点・フラグメントシェーダーをリンクし、ShaderProgramを作成する
*	引数
*	　vertex_shader_file	：[I/ ]　バーテックスシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	　fragment_shader_file	：[I/ ]　フラグメントシェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	戻り値
*	　リンク済みのプログラム
*-------------------------------------------------------------------------------*/
GLuint Shader_CreateProgram(const char* vertex_shader_file, const char* fragment_shader_file);

/*-------------------------------------------------------------------------------
*	関数説明
*	　シェーダーファイルの読み込みを行う
*	引数
*	　shader_file_name	：[I/ ]　各シェーダーのファイル名（Shaderフォルダに格納されている必要があります）
*	　shader_source		：[ /O]　各シェーダーのソースデータ
*	　source_size		：[I/ ]　シェーダーの全文の最大文字数
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void Shader_FileLoad(const char* shader_file_name, char* shader_source, int source_size);

/*-------------------------------------------------------------------------------
*	関数説明
*	　シェーダーソースの読み込みを行う
*	引数
*	　shader_source		：[I/ ]　各シェーダーのソースデータ
*	　gl_xxxx_shader	：[I/ ]　作成するシェーダーオブジェクト（バーテックス or フラグメント）
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
GLint Shader_SourceLoad(const char* shader_source, const GLuint gl_xxxx_shader);