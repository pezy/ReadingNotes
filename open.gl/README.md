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

-----

**数据是如何变成三维图形的？**

一切都要从 vertices 说起，我们给出的数据是一个三角形的三个顶点。存放在 vertices 数组中。它将要经历以下几段程序:

1. [***vertex shader***]
这货藏在显卡上，就是它将咱们的数据（那三个点）加载到显卡上的，我们给出的数据，可能是三维的，但我们的屏幕却是二维的，这货负责从三维到二维的转换(perspective transformation)，同时它还负责某些重要属性(如颜色和纹理坐标等)传输到pipeline中。

2. [***primitives***]
这货叫图元，就是基本的几何体，上面不是把顶点坐标传到显卡了吗？接下来它们就要被组装成一个一个基本图元，点、线、三角、四边形等等。还包括一些比较聪明的图元：triangle strip 和 line strips。这俩东西说白了就是偷懒偷出来的，啥意思呢？譬如两个三角形挨着，那么他们一定共用着一条线，我们想办法让这条线只画一次。于是就有了这些 strips.

3. [***geometry shader***]
这一步是可选的，这货也刚出世不久。和上面那些搬运工、装配工相比，它可不一般，它接收到 primitives 后，会对其进行存储、优化、修正等等一系列事情，然后可能产生更加全面的数据。咱都知道，GPU 和 CPU 之间传输效率是个瓶颈，但这货可以帮你权衡到底哪些才是 GPU 真正需要的。

4. [***rasterizer***]
当上述一系列图形都准备好，光栅器出场了，这家伙曾在[知乎](http://www.zhihu.com/question/24786878)上引出几位图形学大牛热烈的探讨，实现一个 rasterizer 应该算是图形学真正入门的标志。这货会将可视化的图形转换为像素片段(pixel-sized *fragments*)，如上面那张图画的那样，就连原本平滑变化的颜色也要计算插值，然后分布在各个片段上。

5. [***fragment shader***]
这货主要就是干插值的，将各种属性（诸如颜色、纹理，乃至光照与阴影），分配到各个像素片段上。它还能删减一些片段，让其看起来是透明效果。

6. [***blending and tests***]
最后就是混合调配，加上深度模板测试(depth and stencil testing)等等。譬如一个三角形被另一个三角形挡住，那么应该让上面那个显示在屏幕上。

就这样，我们输入的一个个数据，变成了三维图形。

-----

**Vertices**

glBufferData 最后一个参数：

- `GL_STATIC_DRAW`: The vertex data will be uploaded once and drawn many times (e.g. the world).
- `GL_DYNAMIC_DRAW`: The vertex data will be changed from time to time, but drawn many times more than that.
- `GL_STREAM_DRAW`: The vertex data will change almost every time it's drawn (e.g. user interface).

-----

两种绘制方式：Vertices and Uniforms

Uniforms 高级的地方在于，它可以提取 program 中定义为 uniform 类型的值(譬如颜色)，然后可以做到在循环渲染中不断改变，使图形呈现动态的效果。
```cpp
glGetUniformLocation // 取值
glUniform3f // 设值
```

-----

Vertices shader 和 fragment shader 可以用 in 和 out 同名参数来进行连接。

-----

**Element buffers**

这种方式有点像咱们在OSG里面的DrawElementsUInt，可以把你要绘制的所有点，都先放到 vertices 中，然后根据按照某种顺序连接部分点。这样就实现了点的**复用**。而这个顺序，就存在 elements 数组中。

```cpp
GLuint ebo;
glGenBuffers(1, &ebo);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
```

**vao, vbo, ebo**

我们总结一下，vao(Vertex Array Objects) 出现在程序的开始，作为顶点数组的缓存。vbo(Vertex Buffer Object) 和 ebo 类似，都是基于特定类型数组的绑定，是我们数据的来源。

-----

Exercise [01](Exercise/01/main.cpp) | [02](Exercise/02/main.cpp) | [03](Exercise/03/main.cpp)

-----

##Textures objects and parameters

>texture coordinates

```cpp
  _ _ _ (1,1)
 |     |
 |     |
 |_ _ _|
(0,0)  
```
(0, 0) -> (1, 1) 分别代表左下角和右上角

>sampling

取样, 根据纹理坐标检索像素颜色信息。

**(x, y, z) ---> (s, t, r)**

-----

>While linear interpolation gives a smoother result, it isn't always the most ideal option. Nearest neighbour interpolation is more suited in games that want to mimic 8 bit graphics, because of the pixelated look.

linear 更平滑，但 Nearest 更加适合游戏，因其像素化的展示。

更常用的是 mipmaps , 其处理结果不仅高质量，而且高效率。

```cpp
glGenerateMipmap(GL_TEXTURE_2D);
```

- `GL_NEAREST_MIPMAP_NEAREST` : 一个滤镜，近邻插值，更加贴近像素大小
- `GL_LINEAR_MIPMAP_NEAREST` : 一个滤镜，线性插值
- `GL_NEAREST_MIPMAP_LINEAR` : 两个滤镜，贴近像素大小，且线性插值
- `GL_LINEAR_MIPMAP_LINEAR` : 两个滤镜，线性插值

-----

**Loading texture images**

```cpp
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
							^     ^      ^   ^(0)  v       v        ^
						   LOD    |  width&height  |_______|________|
						 internal pixel format    format  type    array
```

## Transformations in OpenGL

    物体坐标系 -----> 世界坐标系 -----> 相机坐标系 -----> 投影坐标系
                ^                ^                 ^
         model matrix      view matrix      projection matrix

-----

**Field-of-view**

![FOV](https://open.gl/media/img/c4_fov.png)
