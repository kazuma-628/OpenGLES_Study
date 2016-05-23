#version 320 es

layout(triangles) in;
layout(triangle_strip, max_vertices = 100) out;

//���_�V�F�[�_����̕ϐ�
in lowp vec4 vary_color[];

//�t���O�����g�V�F�[�_�ւ̕ϐ�
out lowp vec4 f_vary_color;

//���f���r���[�}�g���N�X�i�I�u�W�F�N�g�ړ��p�̃}�g���b�N�X�j
uniform mediump mat4 ModelView_matrix;

//�v���W�F�N�V�����}�g���N�X�i3D��Ԃɂ��邽�߂̃}�g���N�X�j
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