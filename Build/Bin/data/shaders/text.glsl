#ifdef VERTEX_SHADER
layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 normal_pos;
layout(location = 2) in vec2 uv_pos;
uniform mat4 mvp;
out vec2 texcoord;

void main(void)
{
	gl_Position = mvp * vec4(vertex_pos, 1.0);
	texcoord = uv_pos;
}
#endif

#ifdef FRAGMENT_SHADER
in vec2 texcoord;
uniform sampler2D tex;
uniform vec4 addColor;


out vec4 color;
const float smoothing = 1.0/16.0;
void main(void)
{
	//signed distance field
	float dist = texture(tex, texcoord).r;
	float alpha = smoothstep(0.5 - smoothing, 0.5 + smoothing, dist);
	color = vec4(addColor.rgb, alpha*addColor.a);
}
#endif