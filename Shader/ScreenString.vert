#version 320 es

//頂点座標
in mediump vec4 attr_pos;

//テクスチャ座標
in mediump vec2 attr_tex_coord;

//テクスチャ座標
out mediump vec2 f_attr_tex_coord;

void main()
{
	//頂点設定
	gl_Position = attr_pos;

	// 頂点カラー出力
	f_attr_tex_coord = attr_tex_coord;
}