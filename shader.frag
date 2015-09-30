#version 330

out vec4 fragColor;

in vec3 colorInt;

void main(void)
{
	// Utilitza el color interpolat que prové del vertex shader
	fragColor =  vec4(colorInt, 1.0);
}
