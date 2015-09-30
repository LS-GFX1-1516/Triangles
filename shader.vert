#version 330
 
in vec3 vertexPos;
in vec3 color;

out vec3 colorInt;

void main()
{
	// Posici� del v�rtex actual
	gl_Position = vec4( vertexPos , 1.0 );

	// Passa el color cap al fragment shader
	colorInt = color;
}

