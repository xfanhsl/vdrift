#ifndef _OPENGL_UTILITY_H
#define _OPENGL_UTILITY_H

#ifdef __APPLE__
#include <GLExtensionWrangler/glew.h>
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include <string>
#include <iostream>
#include <cassert>

namespace OPENGL_UTILITY
{
	void CheckForOpenGLErrors(std::string activity_description, std::ostream & error_output);
}

#endif