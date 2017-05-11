#include "Shader.h"
#include <iostream>


char * Shader::readBinaryFile(std::string filename)
{
	//open in binary reading mode
	std::ifstream instream(filename, std::ios::binary);

	if (!instream.is_open()) return nullptr;

	//get length
	instream.seekg(0, std::ios::end);
	int length = (int)instream.tellg();
	instream.seekg(0, std::ios::beg);


	char* bytes = new char[length + 1];
	bytes[length] = '\0';
	instream.read(bytes, length);

	//close
	instream.close();

	return bytes;
}

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::load(string v, string f)
{
	filenamev = v;
	filenamef = f;

	bool good = compile(GL_VERTEX_SHADER);
	if (!good) return false;
	good = compile(GL_FRAGMENT_SHADER);
	if (!good) return false;

	program = glCreateProgram();
	glAttachShader(program, vprogram);
	glAttachShader(program, fprogram);

	glLinkProgram(program);

	GLint results;

	glGetProgramiv(program, GL_LINK_STATUS, &results);

	if (results != GL_FALSE) return true;

	//finds info log and prints it out if failed to link
	GLint logLength;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

	char* log = new char[logLength];
	glGetProgramInfoLog(program, logLength, 0, log);
	std::cout << log << std::endl;
	glDeleteProgram(program);
	delete[] log;
	return false;
}

bool Shader::compile(GLenum shaderType)
{
	char* sourcecode = nullptr;
	

	if (shaderType == GL_VERTEX_SHADER) {
		sourcecode = readBinaryFile(filenamev);
		//checks if file loaded properly
		if (sourcecode == nullptr) {
			std::cout << "File was not loaded properly." << std::endl;
			return false;
		}

		vprogram = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vprogram, 1, &sourcecode, NULL);
		glCompileShader(vprogram);

		delete[] sourcecode;

		GLint results;
		glGetShaderiv(vprogram, GL_COMPILE_STATUS, &results);

		if (results == GL_FALSE) {
			GLint logLength;
			glGetShaderiv(vprogram, GL_INFO_LOG_LENGTH, &logLength);

			char* log = new char[logLength];
			glGetShaderInfoLog(vprogram, logLength, 0, log);
			std::cout << log << std::endl;
			glDeleteShader(vprogram);
			delete[] log;
			return false;
		}
	}
	else if (shaderType == GL_FRAGMENT_SHADER) {
		sourcecode = readBinaryFile(filenamef);
		//checks if file loaded properly
		if (sourcecode == nullptr) {
			std::cout << "File was not loaded properly." << std::endl;
			return false;
		}

		fprogram = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fprogram, 1, &sourcecode, NULL);
		glCompileShader(fprogram);

		delete[] sourcecode;

		GLint results;
		glGetShaderiv(fprogram, GL_COMPILE_STATUS, &results);

		if (results == GL_FALSE) {
			GLint logLength;
			glGetShaderiv(fprogram, GL_INFO_LOG_LENGTH, &logLength);

			char* log = new char[logLength];
			glGetShaderInfoLog(fprogram, logLength, 0, log);
			std::cout << log << std::endl;
			glDeleteShader(fprogram);
			delete[] log;
			return false;
		}
	}

	return true;
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::unload()
{
	glDeleteProgram(program);
	glDeleteShader(vprogram);
	glDeleteShader(fprogram);

	program = 0;
	vprogram = 0;
	fprogram = 0;
}
