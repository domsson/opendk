#pragma once

#include <map>
#include <string>

#include <GL/glew.h>

#include "Shader.hpp"
#include "ShaderAttribute.hpp"

namespace OpenDK
{

	class ShaderProgram
	{
	public:

		ShaderProgram();

		void addShader(const GLchar* file, GLenum shaderType);

		void bindAttribute(ShaderAttribute location, const GLchar* attrName);

		GLint getUniformLocation(const std::string& name);

		/**
		 * Get the name / id of this ShaderProgram as registered with the GL.
		 * @return The id of this program as registered with OpenGL
		 */
		GLuint getId() const;

		/**
		 * Links all previously added Shaders into an executable ShaderProgram.
		 * This requires at least a compiled vertex and fragment Shader.
		 * If successful, the ShaderProgram can then be used for rendering.
		 * @return true if linking succeeded, otherwise false
		 */
		bool link(bool deleteShaders = true);

		/**
		 * Installs this ShaderProgram as part of the current rendering state.
		 */
		void use();

		/**
		 * Frees the GPU memory and invalidates the names associated with
		 * every shader that has been added to this ShaderProgram.
		 */
		void free();

	private:

		GLuint id;
		GLint linkStatus;
		std::map <GLenum, Shader> shaders;
		std::map <std::string, GLint> uniforms;

		GLint fetchUniformLocation(const std::string& name);

		void freeShaders() const;

		void generateId();

	};

}
