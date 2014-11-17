#pragma once
#ifndef SFZ_GL_UTILS_HPP
#define SFZ_GL_UTILS_HPP

#include <gl/glew.h>
#include <iostream>
#include <string>
#include <exception> // std::terminate()

namespace gl {

/**
 * @brief Checks the latest error returned by glGetError().
 * @return whether an error was found or not
 */
bool checkGLError() noexcept;

/**
 * @brief Checks all errors returned by glGetError() until GL_NO_ERROR is returned.
 * @return whether any errors where found or not
 */
bool checkAllGLErrors() noexcept;

/**
 * @brief Prints the error log returned by glShaderInfoLog().
 */
void printShaderInfoLog(GLuint program) noexcept;

/**
 * @brief Creates and compiles a vertex shader with the specified source.
 * Terminates program if shader compilation failed.
 * @param shaderSource the source code of the vertex shader
 * @return the newly created and compiled vertex shader object
 */
GLuint compileVertexShader(const std::string& shaderSource) noexcept;

/**
 * @brief Creates and compiles a fragment shader with the specified source.
 * Terminates program if shader compilation failed.
 * @param shaderSource the source code of the fragment shader
 * @return the newly created and compiled fragment shader object
 */
GLuint compileFragmentShader(const std::string& shaderSource) noexcept;

/**
 * @brief Links the specified program.
 * Terminates program if linking failed.
 * @param program the program
 */
void linkProgram(GLuint program) noexcept;

} // namespace gl

#endif