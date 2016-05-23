#version 320 es

layout(triangles) in;
layout(triangle_strip, max_vertices = 100) out;

//頂点シェーダからの変数
in lowp vec4 vary_color[];

//フラグメントシェーダへの変数
out lowp vec4 f_vary_color;

void main()
{
	for (int index = 0; index < gl_in.length(); index++)
	{
		gl_Position = gl_in[index].gl_Position;
		f_vary_color = vary_color[index];
		EmitVertex();
	}

	EndPrimitive();
}