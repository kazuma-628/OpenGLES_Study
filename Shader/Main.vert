#version 300 es

//���_�f�[�^
in mediump vec4 attr_pos;

//���_�J���[
in lowp vec4 attr_color;

//�t���O�����g�V�F�[�_�ւ̕ϐ�
out lowp vec4 vary_color;

void main()
{

	//���_�ݒ�
	gl_Position = attr_pos;

	// ���_�J���[�o��
	vary_color = attr_color;
}