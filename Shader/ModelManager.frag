#version 300 es

//デフォルトの精度を設定
precision mediump float;

//モデルデータのフォーマット
//ここの定義を変更する場合は、「Model.h」のemun「FileFotmat」定義も同じように変更してください
#define	FILE_FORMAT_OBJ					1		//OBJ形式のモデルファイル（OBJファイルに指定があればMTLファイルも読み込まれる）
#define	ORIGINAL_FORMAT_PIERCED_CUBE	2		//オリジナルフォーマットで穴あきのキューブデータ（エッジ有り）
#define ORIGINAL_FORMAT_PIERCED_CUBE2	3		//オリジナルフォーマットで穴あきのキューブデータ（エッジ無し）

//入力
in mediump vec3 f_attr_Normal;				//法線
in mediump vec4 f_attr_Color;				//カラー
in mediump vec2 f_attr_TexCoord;			//テクスチャ座標

uniform lowp int unif_FileFotmat;			//モデルデータのフォーマット
uniform lowp vec3 unif_Ambient;				//アンビエント値
uniform lowp vec3 unif_Diffuse;				//ディフューズ値
uniform lowp vec3 unif_Specular;			//スペキュラ値
uniform lowp float unif_Shininess;			//シャイネス値
uniform lowp float unif_Alpha;				//アルファ値
uniform lowp int unif_AmbientTexFlag;		//テクスチャ（アンビエント） 有り・無しフラグ
uniform lowp int unif_DiffuseTexFlag;		//テクスチャ（ディフューズ） 有り・無しフラグ
uniform lowp int unif_SpecularTexFlag;		//テクスチャ（スペキュラ）有り・無しフラグ
uniform lowp int unif_BumpMapTexFlag;		//テクスチャ（バンプマップ）有り・無しフラグ
uniform sampler2D unif_AmbientTex;			//テクスチャ（アンビエント）
uniform sampler2D unif_DiffuseTex;			//テクスチャ（ディフューズ） 
uniform sampler2D unif_SpecularTex;			//テクスチャ（スペキュラ）
uniform sampler2D unif_BumpMapTex;			//テクスチャ（バンプマップ）

//出力
out mediump vec4 FragColor;

void main()
{
	//最終的な色情報
	mediump vec4 FinalColor = vec4(0.0, 0.0, 0.0, 1.0);

	switch(unif_FileFotmat)
	{
		//OBJファイル
		case FILE_FORMAT_OBJ:

			//マテリアルファイルにテクスチャが指定されていた場合
			if(1 == unif_DiffuseTexFlag)
			{
				//テクスチャ情報を読み込む
				FinalColor = texture(unif_DiffuseTex, vec2(f_attr_TexCoord.x, f_attr_TexCoord.y));
			}
			else
			{
				//暫定として法線を元に色情報を決定
				mediump float depth = dot(vec3(0.0, 0.0, 1.0), normalize(f_attr_Normal));
				FinalColor = vec4(0.0, depth, 0.0, 1.0);				
			}
			break;

		//オリジナルフォーマットで穴あきのキューブデータ（エッジ有り）
		case ORIGINAL_FORMAT_PIERCED_CUBE:
			FinalColor = f_attr_Color;
			break;

		//オリジナルフォーマットで穴あきのキューブデータ（エッジ有り）
		case ORIGINAL_FORMAT_PIERCED_CUBE2:
			FinalColor = f_attr_Color;
			break;

		default:
			//予期せぬファイルフォーマットの場合「赤」にする
			FinalColor = vec4(1.0, 0.0, 0.0, 1.0);
			break;
	}


	//色の設定
	FragColor = FinalColor;
}