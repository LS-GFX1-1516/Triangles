#include "loadShader.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

// ------------------------------------------------------------------------------------------
// Variables globals
// ------------------------------------------------------------------------------------------

// Ample i alt de la finestra per defecte
int g_ViewportWidth = 512;
int g_ViewportHeight = 512;

// Color de fons
const glm::vec3 g_ColorFons(0.2f, 0.2f, 0.2f);

// Identificador del programa de shaders
GLuint g_ShaderProgram = 0;

// Identificador del Vertex Array Object (VAO) que conté la geometria
GLuint g_Vao = 0;

// Nombre de triangles de la malla
GLuint g_NumTriangles = 0;


// ------------------------------------------------------------------------------------------
// Crea tota la geometria que es desa al VAO
// ------------------------------------------------------------------------------------------
void creaGeometria()
{
	const GLfloat vertices[] = { 0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f };

	const GLfloat colors[] = { 1.0f, 0.0f, 0.0f,
		0.f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f };

	const GLuint indices[] = { 0, 1, 2, 0, 2, 3 };

	GLuint buffer;

	// Crea vao on posarem tota la geometria
	glGenVertexArrays(1, &g_Vao);
	glBindVertexArray(g_Vao);

	// Crea VBO per vèrtexs
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Activa atribut de vèrtexs
	GLuint vertexLoc = glGetAttribLocation(g_ShaderProgram, "vertexPos");
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Crea VBO per colors
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	// Activa atribut de color
	GLuint colorLoc = glGetAttribLocation(g_ShaderProgram, "color");
	glEnableVertexAttribArray(colorLoc);
	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Crea VBO per índexs
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	g_NumTriangles = sizeof(indices) / (sizeof(GLuint) * 3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ------------------------------------------------------------------------------------------
// Funció que carrega els recursos utilitzats en el programa
// ------------------------------------------------------------------------------------------
void loadResources()
{
	// Carrega els shaders i crea el programa de shaders
	g_ShaderProgram = loadShaders("shader.vert", "shader.frag");

	// Crea la geomtria i desa-la al VAO
	creaGeometria();
}


// --------------------------------------------------------------
// Callback de pintat
// --------------------------------------------------------------
void onDisplay()
{
	// Neteja el back buffer
	glClear( GL_COLOR_BUFFER_BIT );

	// Selecciona el programa i VAO que s'utilitzaran al pintar
	glUseProgram(g_ShaderProgram);
	glBindVertexArray(g_Vao);

	// Pinta al back buffer
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);

	// Copia back buffer al front buffer
	glutSwapBuffers();
}


// --------------------------------------------------------------
// Callback entrada teclat
// --------------------------------------------------------------
void onKeyUp(unsigned char key, int x, int y)
{
	if (key == 27 )		// ESC
	{
		// Surt del programa
		exit(EXIT_SUCCESS);
	}
}


// --------------------------------------------------------------
// Callback canvi mida de finestra
// --------------------------------------------------------------
void onReshape(int w, int h)
{
	g_ViewportWidth = w;
	g_ViewportHeight = h;

	// Modifica la mida del viewport per que cobreixi tota la superfície de la finestra
	glViewport(0, 0, g_ViewportWidth, g_ViewportHeight);
}


int main(int argc, char* argv[])
{
	// Inicialitzem el entorn de glut per tal de crear una finestra
	glutInit(&argc, argv);
	glutInitContextVersion( 2 , 0 );
	glutInitDisplayMode( GLUT_RGBA  | GLUT_DOUBLE );
	glutInitWindowSize(g_ViewportWidth, g_ViewportHeight);
	glutCreateWindow("Practica GFX");

	// Inicialitzem OpenGL
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK){
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	// Defineix el color de fons de la finestra
	glClearColor(g_ColorFons.x, g_ColorFons.y, g_ColorFons.z, 1.0f );

	// Carreguem els recursos
	loadResources();
  
    // Definim els callbacks
	glutDisplayFunc( onDisplay );
	glutKeyboardUpFunc( onKeyUp );
	glutReshapeFunc( onReshape );

	// Iniciem el bucle principal
	glutMainLoop();

	return EXIT_SUCCESS;
}

