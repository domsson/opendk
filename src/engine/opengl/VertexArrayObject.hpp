#pragma once

#include "VertexBufferObject.hpp"
#include "ShaderAttribute.hpp"

namespace OpenDK
{

	class VertexArrayObject
	{
	public:

		VertexArrayObject();
		
		/**
		 * Add a VBO to this VAO and enable it in the OpenGL state machine.
		 * @param vbo The VBO that you want to add to this VAO
		 * @param shaderAttribute The ShaderAttribute that the VBO belongs to
		 */
		void addVBO(VertexBufferObject vbo, ShaderAttribute shaderAttribute);

		/**
		 * Get a VBO that has been previously added to this VAO.
		 * @param shaderAttribute The ShaderAttribute to which the VBO belongs
		 * @return The VBO belonging to the given ShaderAttribute or null
		 */
		VertexBufferObject getVBO(ShaderAttribute shaderAttribute);
		
		/**
		 * Get this VAO's ID as registered with OpenGL.
		 * @return This VAO's ID
		 */
		GLuint getId();

		/**
		 * Bind this VAO in the OpenGL state machine.
		 * After binding, you may perform actions on it, for example drawing it.
		 */
		void bind();

		/**
		 * Unbind the currently bound VAO from the OpenGL state machine.
		 */
		void unbind();

		/**
		 * Delete this VAO from OpenGL / the GPU.
		 * This will not delete this object, but render it useless.
		 */
		void free();

	private:

		/**
		 * The name of this OpenGL object.
		 */
		GLuint id;

		/**
		 * Request a VAO ID from OpenGL and set it as this VAO's ID.
		 * This will do nothing if this VAO already has an ID.
		 */
		void generateId();

	};

}
