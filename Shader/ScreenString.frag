#version 300 es

//デフォルトの精度を設定
precision mediump float;

//入力
in mediump vec2 f_attr_tex_coord;		//テクスチャ座標

uniform sampler2D unif_tex;				//テクスチャ
uniform lowp vec4 unif_string_color;	//文字のカラー
uniform lowp vec4 unif_back_color;		//背景のカラー

//出力
out mediump vec4 FragColor;

void main()
{
	//最終的な色情報
	highp vec4 finalColor;

	//文字列テクスチャを読み込み
	finalColor = texture(unif_tex, f_attr_tex_coord);

	if(0.0 == finalColor.r)
	{
		//文字じゃないピクセルは背景色を描画
		finalColor = unif_back_color;
	}
	else
	{
		//文字のピクセルは文字色を描画
		//ただし、文字の縁はぼかしがかかっているので、線形補間して背景色とも整合性をとる
		finalColor = mix(unif_back_color, unif_string_color, finalColor.r);
	}

	//色の設定
	FragColor = finalColor;
}