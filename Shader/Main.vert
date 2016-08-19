#version 320 es

//頂点データ
in mediump vec4 attr_pos;

//頂点カラー
in lowp vec4 attr_color;

//ジオメトリシェーダへの変数
out lowp vec4 vary_color;

void main()
{

	//頂点設定
	gl_Position = attr_pos;

	// 頂点カラー出力
	vary_color = attr_color;
}