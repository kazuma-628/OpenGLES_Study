##############################################################
#「CMakeの最低バージョン」を指定する

cmake_minimum_required(VERSION 2.8)

##############################################################
#「ソリューション名 と 言語」を指定する

project(OpenGLES_Study CXX)

##############################################################
#「ソリューションに追加するファイル」を指定する

#「Source File」を指定する
set(SOURCE
#	Source/old_Matrix.cpp		# GLMライブラリへの移行に伴い廃止
#	Source/old_Maths.cpp		# GLMライブラリへの移行に伴い廃止
	Source/Main.cpp
	Source/HelloModel.cpp
	Source/HelloWorld.cpp
	Source/ShaderManager.cpp
	Source/DeviceManager.cpp
	Source/WindowManager.cpp
	Source/Texture.cpp
	Source/ModelManager.cpp
	Source/ScreenString.cpp
	Source/OBJLoader.cpp
)

#「Header File」を指定する
set(HEADER
#	Header/old_Matrix.h			# GLMライブラリへの移行に伴い廃止
#	Header/old_Maths.h			# GLMライブラリへの移行に伴い廃止
	Header/Common.h
	Header/Main.h
	Header/HelloModel.h
	Header/HelloWorld.h
	Header/ShaderManager.h
	Header/DeviceManager.h
	Header/WindowManager.h
	Header/Texture.h
	Header/ModelManager.h
	Header/ScreenString.h
	Header/OBJLoader.h
)

#「Shader File」を指定する
set(SHADER
	Shader/HelloWorld.frag
	Shader/HelloWorld.vert
	Shader/ScreenString.vert
	Shader/ScreenString.frag
	Shader/ModelManager.vert
	Shader/ModelManager.frag
)

#「Model File」を指定する
set(MODEL
	Resource/Model/Handgun1/Copyright.txt
	Resource/Model/Handgun1/Handgun_obj.mtl
	Resource/Model/Handgun1/Handgun_obj.obj
	Resource/Model/Handgun1/Texture/handgun_C.jpg
	Resource/Model/Handgun1/Texture/handgun_N.jpg
	Resource/Model/Handgun1/Texture/handgun_S.jpg
)

#「Texture File」を指定する
set(TEXTURE
	Resource/Texture/Sample.JPG
)

#「Other File」を指定する
set(OTHER
  # Icon
	Resource/Icon/ExeIcon.rc
	Resource/Icon/ExeIcon.ico
)

##############################################################
#「実行可能ファイル（プロジェクト名 と ソース）」を指定する

add_executable(
# 「プロジェクト名」を指定する
	Main

#「Resource File」を指定する
	${SOURCE}
	${HEADER}
	${SHADER}
	${MODEL}
	${TEXTURE}
	${OTHER}
)

##############################################################
#「プリプロセッサ」を指定する

add_definitions(-DGLEW_STATIC)

##############################################################
#「実行ファイル生成場所」を指定する（デバッグのみ）

set_target_properties(
# 「ターゲット（プロジェクト名）」を指定する
	Main

#「プロパティと設定値」を指定する
	PROPERTIES	
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/Output
	RUNTIME_OUTPUT_NAME_DEBUG OpenGLES_Study
)

##############################################################
#「ビルド対象外のファイル」を指定する（自動的にビルド対象になるアイテムのみ）

#「モデルデータ」分ループ
foreach(ModelFile ${MODEL})

	#「.obj」ファイル（モデルデータ）をビルド対象外にする
	if(${ModelFile} MATCHES ".obj$")

		#ダミーのカスタムビルドを設定してビルド対象外に設定する
		add_custom_command(
			OUTPUT Dummy.txt
			COMMAND echo "Dummy Command Run"
			MAIN_DEPENDENCY ${ModelFile}
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		)
	endif(${ModelFile} MATCHES ".obj$")
endforeach(ModelFile)

##############################################################
#「Visual Studio上でのフォルダ」を指定する

source_group(Resource\\Icon REGULAR_EXPRESSION Resource/Icon)
source_group(Resource\\Texture REGULAR_EXPRESSION Resource/Texture)
source_group(Resource\\Model\\Handgun1 REGULAR_EXPRESSION Resource/Model/Handgun1)
source_group(Resource\\Model\\Handgun1\\Texture REGULAR_EXPRESSION Resource/Model/Handgun1/Texture)
source_group(Resource REGULAR_EXPRESSION Resource)
source_group(Shader REGULAR_EXPRESSION Shader)
source_group(Source REGULAR_EXPRESSION Source)
source_group(Header REGULAR_EXPRESSION Header)

##############################################################
#「インクルードするヘッダーの場所」を指定する

include_directories(
	${CMAKE_SOURCE_DIR}/Header
	${CMAKE_SOURCE_DIR}/Library/GLEW/include/GL
	${CMAKE_SOURCE_DIR}/Library/GLFW/include/GLFW
	${CMAKE_SOURCE_DIR}/Library/FreeType/include
	${CMAKE_SOURCE_DIR}/Library/GLM/glm
)

##############################################################
#「ライブラリ」を指定する（バージョンごとに切り替える）

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

#Visual Studio 2015
elseif(${CMAKE_GENERATOR} MATCHES "Visual Studio 14")
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

#サポートしていない「Vusual Studio(2012以前)」バージョンの場合はエラーメッセージを表示
else(${CMAKE_GENERATOR} MATCHES "Visual Studio 12")
	message(FATAL_ERROR "Unsupported \"Visual Studio\" version \n Please use the \"Visual Studio 2013(2015)\" version or later version")
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 12")

