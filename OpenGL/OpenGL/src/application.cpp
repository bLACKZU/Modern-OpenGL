#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

static unsigned int compileShader(unsigned int type, const std::string &source)
{
	unsigned int id = glCreateShader(GL_VERTEX_SHADER);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);


	//Exception Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Compile error" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}


	return id;
}
static unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vS = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fS = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vS);
	glAttachShader(program, fS);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vS);
	glDeleteShader(fS);
	return program;
}
int main(void)
{
	GLFWwindow* window;

	//glewExperimental = GL_TRUE;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	//glewInit();

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	
	glfwMakeContextCurrent(window);
	glewInit();
	float vertices[6] = {

		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_LINES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}