#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <glew.h>
#include <glfw3.h>


#define SHADER_STRING_LINE_MAX		256			//シェーダーの1行の最大文字数
#define SHADER_STRING_ALL_MAX		10240		//シェーダーの全文の最大文字数
#define SHADER_FILE_NAME_MAX		64			//シェーダーのファイル名最大文字数（ディレクトリ名含む）
#define WINDOW_HEIGHT				480
#define WINDOW_WIDTH				640
#define M_PI 3.14159265359
#define degree2radian(degree) ((degree * M_PI) / 180.0)