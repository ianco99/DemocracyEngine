#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 texCoord;

uniform mat4 MVP = mat4(1.0f);

out vec4 v_Color;
out vec2 v_TexCoord;

void main()
{
	gl_Position = MVP * vec4(aPos, 1.0);
	v_Color = aColor;
	v_TexCoord = vec2(texCoord.x, texCoord.y);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, v_TexCoord) * v_Color;
}