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

		/**
		 * Reads and creates a shader from the given source file, then adds
		 * that Shader to this ShaderProgram. Once all Shaders have been added
		 * in this way, you need to call link() in order to actually create the
		 * functioning ShaderProgram from these individual Shaders.
		 * @param file
		 */
		void addShader(const GLchar* file, const GLenum shaderType);

		void addShader(const Shader shader);

		/**
		 * Binds the given attribute variable ('in ...') of this ShaderProgram
		 * to the given location.
		 * @param location The location to which the attr. var. should be bound
		 * @param attrName The name of the attribute variable in the shaders
		 */
		void bindAttribute(const ShaderAttribute location, const GLchar* attrName);

		/**
		 * Get the location of a uniform variable within this ShaderProgram.
		 * @return The location of the uniform with the given name or -1
		 */
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
		bool link(const bool deleteShaders = true);

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
