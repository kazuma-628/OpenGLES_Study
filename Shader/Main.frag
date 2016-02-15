#version 300 es

//頂点シェーダからのデータ
in lowp vec4 vary_color;

out mediump vec4 FragColor;

void main()
{
	//色の設定
	FragColor = vary_color;
}