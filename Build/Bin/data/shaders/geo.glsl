#ifdef VERTEX_SHADER
layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 normal_pos;
layout(location = 2) in vec2 uv_pos;
uniform mat4 mvp;

out vec2 texcoord;
out vec3 outer;

void main(void)
{
	gl_Position = mvp * vec4(vertex_pos, 1);
	
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
 	//vec2 flipped_texcoord = vec2(texcoord.x, 1.0 - texcoord.y);
	color = vec4(0.5, outer.y, outer.z, 1.0);
	//color = texture2D(tex, texcoord);
	
	
	//if(color.r < 0.1)
	//{
	//	discard;
	//}
}
#endif