#version 300 es

//���_�f�[�^
in mediump vec4 attr_pos;

//���_�J���[
in lowp vec4 attr_color;

//�I�u�W�F�N�g�ړ��p�̃}�g���b�N�X
uniform mediump mat4 move_matrix;

//�t���O�����g�V�F�[�_�ւ̕ϐ�
out lowp vec4 vary_color;

void main()
{

	//���_�ݒ�
	gl_Position = move_matrix * attr_pos;

	// ���_�J���[�o��
	vary_color = attr_color;
}