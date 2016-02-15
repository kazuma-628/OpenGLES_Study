#############################################
#「CMakeの最低バージョン」を指定する
#############################################
cmake_minimum_required(VERSION 2.8)

#############################################
#「ソリューション名 と 言語」を指定する
#############################################
project(OpenGLES_Study CXX)

#############################################
#「プロジェクト名」と「読み込むソース」を指定する
#############################################
add_executable(
# 「プロジェクト名」を指定する
	Main

#「Source File」を指定する
	Source/Main.cpp

#「Header File」を指定する
	Header/Main.hpp

#「Shader File」を指定します
	Shader/Main.frag
	Shader/Main.vert
)

#############################################
#「プリプロセッサ」を指定する
#############################################
add_definitions(-DGLEW_STATIC)

#############################################
#「実行ファイル生成場所」を指定する（デバッグのみ）
#############################################
set_target_properties(
# 「ターゲット（プロジェクト名）」を指定する
	Main

#「プロパティと設定値」を指定する
	PROPERTIES	
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/Output
	RUNTIME_OUTPUT_NAME_DEBUG OpenGLES_Study
)

#############################################
#「Visual Studio上でのフォルダ」を指定する
#############################################
source_group(Source Source)
source_group(Header Header)
source_group(Shader Shader)

#############################################
#「インクルードするヘッダーの場所」を指定する
#############################################
include_directories(
	${CMAKE_SOURCE_DIR}/Header
	${CMAKE_SOURCE_DIR}/Library/GLEW/include/GL
	${CMAKE_SOURCE_DIR}/Library/GLFW/include/GLFW
)

#############################################
#「ライブラリ」を指定する（バージョンごとに切り替える）
#############################################

#Visual Studio 2010
if(${CMAKE_GENERATOR} MATCHES "Visual Studio 10")
	target_link_libraries(
	#使用する元の「プロジェクト名」を指定する
		Main

	#「ライブラリ」を指定する
		opengl32.lib
		${CMAKE_SOURCE_DIR}/Library/GLEW/lib/Release/Win32/glew32s.lib
		${CMAKE_SOURCE_DIR}/Library/GLFW/lib-vc2010/glfw3.lib
	)
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 10")

#Visual Studio 2012
if(${CMAKE_GENERATOR} MATCHES "Visual Studio 11")
	target_link_libraries(
	#使用する元の「プロジェクト名」を指定する
		Main

	#「ライブラリ」を指定する
		opengl32.lib
		${CMAKE_SOURCE_DIR}/Library/GLEW/lib/Release/Win32/glew32s.lib
		${CMAKE_SOURCE_DIR}/Library/GLFW/lib-vc2012/glfw3.lib
	)
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 11")

#Visual Studio 2013
if(${CMAKE_GENERATOR} MATCHES "Visual Studio 12")
	target_link_libraries(
	#使用する元の「プロジェクト名」を指定する
		Main

	#「ライブラリ」を指定する
		opengl32.lib
		${CMAKE_SOURCE_DIR}/Library/GLEW/lib/Release/Win32/glew32s.lib
		${CMAKE_SOURCE_DIR}/Library/GLFW/lib-vc2013/glfw3.lib
	)
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 12")

#Visual Studio 2015
if(${CMAKE_GENERATOR} MATCHES "Visual Studio 14")
	target_link_libraries(
	#使用する元の「プロジェクト名」を指定する
		Main

	#「ライブラリ」を指定する
		opengl32.lib
		${CMAKE_SOURCE_DIR}/Library/GLEW/lib/Release/Win32/glew32s.lib
		${CMAKE_SOURCE_DIR}/Library/GLFW/lib-vc2015/glfw3.lib
	)
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 14")