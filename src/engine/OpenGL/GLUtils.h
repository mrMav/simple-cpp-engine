#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

// static class for checking gl errors
class GLUtils
{

public:

	static void CheckErrors()
	{
		GLenum err;
		const char* errstring;

		while ((err = glGetError()) != GL_NO_ERROR)
		{
			//errstring = gluErrorString(err);
			std::cout << "GL ERROR: "<< err << /* errstring << */ std::endl;
		}
	};

private:
	
	GLUtils();  // disable the creation of an instance

};

