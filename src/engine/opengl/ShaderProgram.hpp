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

		/**
		 * Creates an empty, uninitialized ShaderProgram.
		 * Before it can be used, you need to add at least add
		 * a vertex and a fragment shader and then call link().
		 */
		ShaderProgram();

		/**
		 * Reads and creates a shader from the given source file, then adds
		 * that Shader to this ShaderProgram. Once all Shaders have been added
		 * in this way, you need to call link() in order to actually create the
		 * functioning ShaderProgram from these individual Shaders.
		 * @param file The shader's source file
		 * @param shaderType The type of the shader
		 */
		void addShader(const GLchar* file, const GLenum shaderType);

		/**
		 * Adds a Shader to this ShaderProgram. Once all Shaders have been added
		 * in this way, you need to call link() in order to actually create the
		 * functioning ShaderProgram from these individual Shaders.
		 * @param shader The Shader to be added to this ShaderProgram
		 */
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
		 * @return true if this ShaderProgram has been successfully linked,
		 * 			false otherwise
		 */
		bool linked() const;

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

		// This program's OpenGL name/id (0 if not yet assigned)
		GLuint id;

		// Link status: GL_TRUE = linked, GL_FALSE = not (yet) linked
		GLint linkStatus;

		// All Shaders that have been added to this ShaderProgram
		std::map <GLenum, Shader> shaders;

		// Stores fetched uniform variables and their locations
		std::map <std::string, GLint> uniforms;

		// Query the location of a given uniform variable within Shaders
		GLint fetchUniformLocation(const std::string& name);

		// Delete all individual Shaders from OpenGL and the `shaders` map
		void freeShaders() const;

		// Get a name/id for this program from OpenGL
		void generateId();

	};

}
