#ifdef VERTEX_SHADER
layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 normal_pos;
layout(location = 2) in vec2 uv_pos;

out vec2 texcoord;
out vec3 outer;

void main(void)
{
	gl_Position = vec4(vertex_pos, 1);
	
	texcoord = uv_pos;
	outer = vertex_pos;
}
#endif

#ifdef FRAGMENT_SHADER
in vec3 outer;
in vec2 texcoord;
uniform sampler2D tex;
uniform vec4 addColor;

out vec4 color;
void main(void)
{
	color = vec4(outer.x, outer.y, outer.z, 1.0);
}
#endif