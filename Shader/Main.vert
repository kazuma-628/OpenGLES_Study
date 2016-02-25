#version 300 es

//���_�f�[�^
in mediump vec4 attr_pos;

//���_�J���[
in lowp vec4 attr_color;

//���f���r���[�}�g���N�X�i�I�u�W�F�N�g�ړ��p�̃}�g���b�N�X�j
uniform mediump mat4 ModelView_matrix;

//�v���W�F�N�V�����}�g���N�X�i3D��Ԃɂ��邽�߂̃}�g���N�X�j
uniform mediump mat4 Proj_matrix;

//�t���O�����g�V�F�[�_�ւ̕ϐ�
out lowp vec4 vary_color;

void main()
{

	//���_�ݒ�
	gl_Position = Proj_matrix * ModelView_matrix * attr_pos;

	// ���_�J���[�o��
	vary_color = attr_color;
}