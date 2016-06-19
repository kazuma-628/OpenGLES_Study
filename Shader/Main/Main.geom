#version 320 es

layout(triangles) in;
layout(triangle_strip, max_vertices = 100) out;

//頂点シェーダからの変数
in lowp vec4 vary_color[];

//フラグメントシェーダへの変数
out lowp vec4 f_vary_color;

//モデルビューマトリクス（オブジェクト移動用のマトリックス）
uniform mediump mat4 ModelView_matrix;

//プロジェクションマトリクス（3D空間にするためのマトリクス）
uniform mediump mat4 Proj_matrix;

void main()
{
	for (int index = 0; index < gl_in.length(); index++)
	{
		gl_Position = Proj_matrix * ModelView_matrix * gl_in[index].gl_Position;
		f_vary_color = vary_color[index];
		EmitVertex();
	}

	EndPrimitive();
}