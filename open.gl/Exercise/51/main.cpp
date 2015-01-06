//////////////////////////////////////////////////////////////////////////
// Try using a geometry shader in a 3D scenario to create more complex meshes like cubes from points.

#include <stdio.h>
#include <time.h>
#include <math.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLSL(src) "#version 150 core\n" #src

// Vertex shader
const char* vertexShaderSrc = GLSL(
	in vec3 pos;
	in vec3 color;

	out vec3 vColor;

	void main() {
		gl_Position = vec4(pos, 1.0);
		vColor = color;
	}
);

// Geometry shader
const char* geometryShaderSrc = GLSL(
	layout(points) in;
	layout(triangle_strip, max_vertices = 8) out;

	in vec3 vColor[];
	out vec3 fColor;

	void main() {
		fColor = vColor[0];

		gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1,-0.1, 0.0);
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4( 0.1, 0.1,-0.1, 0.0);
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.1, 0.0);
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4( 0.1, 0.1, 0.1, 0.0);
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4(-0.1,-0.1, 0.1, 0.0);
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4( 0.1,-0.1, 0.1, 0.0);
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4(-0.1,-0.1,-0.1, 0.0);
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4( 0.1,-0.1,-0.1, 0.0);
		EmitVertex();

		EndPrimitive();
	}
);

// Fragment shader
const char* fragmentShaderSrc = GLSL(
	in vec3 fColor;
	out vec4 outColor;
	void main() {
		outColor = vec4(fColor, 1.0);
	}
);

GLuint createShader(GLenum type, const GLchar* src) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		printf("\n%s\n", buffer);
	}

	return shader;
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE; //  force GLEW to use a modern OpenGL method for checking if a function is available.
	glewInit();

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSrc);
	GLuint geometryShader = createShader(GL_GEOMETRY_SHADER, geometryShaderSrc);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Create VBO with point coordinates
	GLuint vbo;
	glGenBuffers(1, &vbo);

	float points[] = {
		//	Coordinates		  Color		
		-0.45f,  0.45f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.45f,  0.45f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.45f, -0.45f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.45f, -0.45f, 0.0f, 1.0f, 1.0f, 0.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// Create VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Specify layout of point data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
			else if (windowEvent.type == SDL_KEYUP &&
				windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_POINTS, 0, 4);

		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);

	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	SDL_Quit();
	return 0;
}