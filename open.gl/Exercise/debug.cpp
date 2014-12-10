// check the compile
GLint vertex_status;
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertex_status);
if (vertex_status != GL_TRUE)
{
	char vertex_buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, vertex_buffer);
	printf("\n%s\n", vertex_buffer);
}

// check the compile
GLint fragment_status;
glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragment_status);
if (fragment_status != GL_TRUE)
{
	char fragment_buffer[512];
	glGetShaderInfoLog(fragmentShader, 512, NULL, fragment_buffer);
	printf("\n%s\n", fragment_buffer);
}
