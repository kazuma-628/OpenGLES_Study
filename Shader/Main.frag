#version 320 es

//ジオメトリシェーダからのデータ
in lowp vec4 f_vary_color;

out mediump vec4 FragColor;

void main()
{
	//色の設定
	FragColor = f_vary_color;
}