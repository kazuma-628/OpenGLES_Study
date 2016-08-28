#version 300 es

//デフォルトの精度を設定
precision mediump float;

//入力
in mediump vec4 attr_pos;	//頂点データ
in lowp vec4 attr_color;	//頂点カラー

uniform mediump mat4 ProjModel_matrix;		//座標変換マトリクス（プロジェクションマトリクス × モデルビューマトリックス）

//出力
out lowp vec4 f_attr_color;		//ジオメトリシェーダへの変数

void main()
{
	//頂点設定
	gl_Position = ProjModel_matrix * attr_pos;

	// 頂点カラー出力
	f_attr_color = attr_color;
}