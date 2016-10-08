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

#「Resource File」を指定する
	Resource/Icon/ExeIcon.rc
	Resource/Icon/ExeIcon.ico
	Resource/Texture/Sample.JPG

#「Source File」を指定する
#	Source/old_Matrix.cpp		# GLMライブラリへの移行に伴い廃止
#	Source/old_Maths.cpp		# GLMライブラリへの移行に伴い廃止
	Source/Main.cpp
	Source/HelloWorld.cpp
	Source/ShaderManager.cpp
	Source/DeviceManager.cpp
	Source/WindowManager.cpp
	Source/Texture.cpp
	Source/ModelManager.cpp
	Source/ScreenString.cpp
	Source/OBJLoader.cpp

#「Header File」を指定する
#	Header/old_Matrix.h			# GLMライブラリへの移行に伴い廃止
#	Header/old_Maths.h			# GLMライブラリへの移行に伴い廃止
	Header/Common.h
	Header/Main.h
	Header/HelloWorld.h
	Header/ShaderManager.h
	Header/DeviceManager.h
	Header/WindowManager.h
	Header/Texture.h
	Header/ModelManager.h
	Header/ScreenString.h
	Header/OBJLoader.h

#「Shader File」を指定する
	Shader/HelloWorld.frag
	Shader/HelloWorld.vert
	Shader/ScreenString.vert
	Shader/ScreenString.frag
	Shader/ModelManager.vert
	Shader/ModelManager.frag
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
source_group(Resource\\Icon REGULAR_EXPRESSION Resource/Icon)
source_group(Resource\\Texture REGULAR_EXPRESSION Resource/Texture)
source_group(Resource REGULAR_EXPRESSION Resource)
source_group(Shader REGULAR_EXPRESSION Shader)
source_group(Source REGULAR_EXPRESSION Source)
source_group(Header REGULAR_EXPRESSION Header)

#############################################
#「インクルードするヘッダーの場所」を指定する
#############################################
include_directories(
	${CMAKE_SOURCE_DIR}/Header
	${CMAKE_SOURCE_DIR}/Library/GLEW/include/GL
	${CMAKE_SOURCE_DIR}/Library/GLFW/include/GLFW
	${CMAKE_SOURCE_DIR}/Library/FreeType/include
	${CMAKE_SOURCE_DIR}/Library/GLM/glm
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
		gdiplus.lib
		${CMAKE_SOURCE_DIR}/Library/GLEW/lib/Release/Win32/glew32s.lib
		${CMAKE_SOURCE_DIR}/Library/GLFW/lib-vc2010/glfw3.lib
		${CMAKE_SOURCE_DIR}/Library/FreeType/lib/freetype265MT.lib
	)
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 10")

#Visual Studio 2012
if(${CMAKE_GENERATOR} MATCHES "Visual Studio 11")
	target_link_libraries(
	#使用する元の「プロジェクト名」を指定する
		Main

	#「ライブラリ」を指定する
		opengl32.lib
		gdiplus.lib
		${CMAKE_SOURCE_DIR}/Library/GLEW/lib/Release/Win32/glew32s.lib
		${CMAKE_SOURCE_DIR}/Library/GLFW/lib-vc2012/glfw3.lib
		${CMAKE_SOURCE_DIR}/Library/FreeType/lib/freetype265MT.lib
	)
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 11")

#Visual Studio 2013
if(${CMAKE_GENERATOR} MATCHES "Visual Studio 12")
	target_link_libraries(
	#使用する元の「プロジェクト名」を指定する
		Main

	#「ライブラリ」を指定する
		opengl32.lib
		gdiplus.lib
		${CMAKE_SOURCE_DIR}/Library/GLEW/lib/Release/Win32/glew32s.lib
		${CMAKE_SOURCE_DIR}/Library/GLFW/lib-vc2013/glfw3.lib
		${CMAKE_SOURCE_DIR}/Library/FreeType/lib/freetype265MT.lib
	)
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 12")

#Visual Studio 2015
if(${CMAKE_GENERATOR} MATCHES "Visual Studio 14")
	target_link_libraries(
	#使用する元の「プロジェクト名」を指定する
		Main

	#「ライブラリ」を指定する
		opengl32.lib
		gdiplus.lib
		${CMAKE_SOURCE_DIR}/Library/GLEW/lib/Release/Win32/glew32s.lib
		${CMAKE_SOURCE_DIR}/Library/GLFW/lib-vc2015/glfw3.lib
		${CMAKE_SOURCE_DIR}/Library/FreeType/lib/freetype265MT.lib
	)
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 14")