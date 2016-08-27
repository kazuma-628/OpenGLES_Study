#version 300 es

//入力
in lowp vec4 f_attr_color;		//フラグメントシェーダからのデータ

//出力
out mediump vec4 FragColor;		//ピクセルの色

void main()
{
	//色の設定
	FragColor = f_attr_color;
}