#version 300 es

//頂点データ
in mediump vec4 attr_pos;

//頂点カラー
in lowp vec4 attr_color;

//モデルビューマトリクス（オブジェクト移動用のマトリックス）
uniform mediump mat4 ModelView_matrix;

//プロジェクションマトリクス（3D空間にするためのマトリクス）
uniform mediump mat4 Proj_matrix;

//フラグメントシェーダへの変数
out lowp vec4 vary_color;

void main()
{

	//頂点設定
	gl_Position = Proj_matrix * ModelView_matrix * attr_pos;

	// 頂点カラー出力
	vary_color = attr_color;
}