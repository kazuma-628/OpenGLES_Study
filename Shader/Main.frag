#version 300 es

//���_�V�F�[�_����̃f�[�^
in lowp vec4 vary_color;

out mediump vec4 FragColor;

void main()
{
	//�F�̐ݒ�
	FragColor = vary_color;
}