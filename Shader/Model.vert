#version 300 es

//デフォルトの精度を設定
precision mediump float;

//入力
in mediump vec4 attr_Position;			//頂点座標
in mediump vec3 attr_Normal;			//法線
in mediump vec4 attr_Color;				//カラー
in mediump vec2 attr_TexCoord;			//テクスチャ座標

uniform mediump mat4 unif_ProjModelMat;	//「プロジェクション × モデルビュー」を乗算済みの行列

//出力
out mediump vec3 f_attr_Normal;			//法線
out mediump vec4 f_attr_Color;			//カラー
out mediump vec2 f_attr_TexCoord;		//テクスチャ座標

void main()
{
	//フラグメントシェーダーに送る
	f_attr_Normal = attr_Normal;			//法線
	f_attr_Color = attr_Color;				//カラー
	f_attr_TexCoord = attr_TexCoord;		//テクスチャ座標

	//頂点設定
	gl_Position = unif_ProjModelMat * attr_Position;
}