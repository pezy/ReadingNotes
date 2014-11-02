##introduction

This guide just introduce `shader` (new parts of the OpenGL specification).

Prerequisites:

- creating the context and handling input: [SDL](https://www.libsdl.org/), [GLFW](https://github.com/glfw/glfw)
- use newer OpenGL functions: [GLEW](https://github.com/nigels-com/glew)
- vectors and matrices: [GLM](https://github.com/g-truc/glm)

##context

SDL:

- include
- lib: SDL2 and SDL2main
- dll: SDL2.dll, SDL2.so

GLEW：

- include
- lib (static): glew32s.lib (`GLEW_STATIC`)

Code:

```cpp
#include "stdio.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	glewInit();
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	printf("%u\n", vertexBuffer);

	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
			else if (windowEvent.type == SDL_KEYUP &&
				windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
		}

		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);

	SDL_Quit();
	return 0;
}
```

##The graphics pipeline

![](https://open.gl/media/img/c2_pipeline.png)
