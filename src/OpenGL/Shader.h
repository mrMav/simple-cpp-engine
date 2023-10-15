#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GLUtils.h"

namespace Engine
{
	/*
	 * This is a helper class that handles all the shader stuff.
	 * It loads all the source code from the given files, and compiles it to a gl program.
	 * It will output any encountered errors.
	 * see https://learnopengl.com/
	 */
	class Shader {

	public:

		// program ID
		GLuint program;

		Shader() { };

		Shader(bool fromSource, const char* vertexSource, const char* fragmentSource)
		{
			CreateShader(vertexSource, fragmentSource);
		}

		// constructor
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

			using namespace std;

			string vertexCode;
			string fragmentCode;

			ifstream vShaderFile;
			ifstream fShaderFile;

			// ensure ifstream objects can throw exceptions
			vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
			fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

			try {

				stringstream vShaderStream, fShaderStream;

				// open files
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);

				// reads file buffers to streams
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();

				vShaderFile.close();
				fShaderFile.close();

				// get string from buffer
				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();

			}
			catch (ifstream::failure e) {

				cout << "ERROR:SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << endl;
				exit(EXIT_FAILURE);

			}

			CreateShader(vertexCode.c_str(), fragmentCode.c_str());

		}

		// active this shader
		void use() {

			glUseProgram(this->program);

		}

		void setInt(const std::string& name, const int value) {

			glUniform1i(glGetUniformLocation(program, name.c_str()), value);

		}

		void setFloat(const std::string& name, const float value) {

			glUniform1f(glGetUniformLocation(program, name.c_str()), value);

		}

		void setVec3(const std::string& name, const glm::vec3& value) const
		{
			glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
		}

		void setVec3(const std::string& name, float x, float y, float z) const
		{
			glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
		}

		void setVec4(const std::string& name, const glm::vec4& value) const
		{
			glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
		}

		void setMat4(const std::string& name, const glm::mat4& mat) const
		{
			glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}


		private:
		void CreateShader(const char* vertexSource, const char* fragmentSource)
		{
			using namespace std;

			const char* vShaderCode = vertexSource;
			const char* fShaderCode = fragmentSource;

			// compile shaders
			GLuint vertex, fragment;
			int success;
			char infoLog[512];

			// vertex shader
			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

			if (!success) {

				glGetShaderInfoLog(vertex, 512, NULL, infoLog);
				cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;

			}

			// fragment shader
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

			if (!success) {

				glGetShaderInfoLog(fragment, 512, NULL, infoLog);
				cout << "ERROR::SHADER::FRAGMENT:COMPILATION_FAILED\n" << infoLog << endl;

			}

			this->program = glCreateProgram();
			glAttachShader(this->program, vertex);
			glAttachShader(this->program, fragment);
			glLinkProgram(this->program);

			glGetProgramiv(this->program, GL_LINK_STATUS, &success);

			if (!success) {

				glGetProgramInfoLog(this->program, 512, NULL, infoLog);
				cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;

			}

			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}


	};

}