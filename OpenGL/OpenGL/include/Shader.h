#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>

class Shader
{
	//std::string vertexShader; 
	//std::string fragmentShader;
	

public:
	//Shader(const std::string &vs_, const std::string &fs_) : vertexShader(vs_), fragmentShader(fs_) {}
	unsigned int id;
	unsigned int compileShader(unsigned int type, const std::string &source)
	{
		id = glCreateShader(type);
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
	unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader)
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

	void setFloat(const std::string &name, float value)
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

};