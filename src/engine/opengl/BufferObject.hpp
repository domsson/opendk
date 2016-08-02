#pragma once

#include <iostream>
#include <typeinfo>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

namespace OpenDK
{

	class BufferObject
	{
	public:

		BufferObject();

		/**
		 * Creates a BufferObject of the specified type and with default draw type.
		 * In order to make use of this BufferObject, its data has to be set via setData().
		 * @param bufferType A valid Buffer Type (see VALID_BUFFER_TYPES for a list of valid types)
		 */
		BufferObject(GLenum bufferType);

		/**
		 * Creates a BufferObject of the specified type and specified draw type.
		 * In order to make use of this BufferObject, its data has to be set via setData().
		 * @param bufferType A valid Buffer Type (see VALID_BUFFER_TYPES for a list of valid types)
		 * @param drawType A valid Draw Type (see VALID_DRAW_TYPES for a list of valid types)
		 */
		BufferObject(GLenum bufferType, GLenum drawType);

		/**
		 * Creates a BufferObject from integer data, assuming that it is supposed to be an IBO.
		 * @param data An array of type int
		 */
		BufferObject(GLuint data[], GLsizeiptr size);

		/**
		 * Creates a BufferObject from float data, assuming that it is supposed to be a VBO
		 * @param data An array of type float
		 */
		BufferObject(GLfloat data[], GLsizeiptr size);

		/**
		 * Change the type of this Buffer. This will only have an effect if called before
		 * the Buffer's data has been set, otherwise it will do nothing.
		 * @param bufferType A valid Buffer Type
		 */
		void setBufferType(GLuint bufferType);

		/**
		 * Change the draw type of this Buffer. This will only have an effect if called before
		 * the Buffer's data has been set, otherwise it will do nothing.
		 * @param drawType A valid Draw Type
		 */
		void setDrawType(GLuint drawType);


		/**
		 * Set this buffer's data. This will trigger the actual creation of this Buffer.
		 * Once the data has been set, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data An array of type GLfloat
		 */
		void setData(GLfloat data[], GLsizeiptr size);

		/**
		 * Set this buffer's data. This will trigger the actual creation of this Buffer.
		 * Once the data has been set, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data An array of type GLuint
		 */
		void setData(GLuint data[], GLsizeiptr size);

		/**
		 * Get this Buffer's id/name as registered with OpenGL.
		 * @return This Buffer's id (name)
		 */
		GLuint getId();

		/**
		 * Get this Buffer's data size.
		 * @return This Buffer's data size
		 */
		GLsizeiptr getSize();

		/**
		 * Get this Buffer's type.
		 * @return This Buffer's type
		 */
		GLenum getBufferType();

		/**
		 * Get this Buffer's draw type.
		 * @return This Buffer's draw type
		 */
		GLenum getDrawType();

		/**
		 * Bind this Buffer in the OpenGL state machine in order to perform actions on/with it.
		 */
		void bind();

		/**
		 * Unbind this Buffer (as well as any other of the same type) from the OpenGL state machine.
		 */
		void unbind();

		/**
		 * Delete this Buffer from OpenGL. This will not delete this object, just the actual Buffer from OpenGL.
		 */
		void free();

		/**
		 * Let OpenGL generate an id/name for this Buffer and remember it.
		 */
		void generateId();

	protected:

		GLuint id;
		GLsizeiptr size;
		GLenum bufferType;
		GLenum drawType;

		/**
		 * Actually creates this Buffer from the given int data.
		 * This will register the buffer with OpenGL and send its data to OpenGL.
		 * Afterwards, this Buffer will have a valid id/name and can be used for drawing.
		 * @param data An array of type int
		 */
		void initBuffer(GLuint data[]);
	
		/**
		 * Actually creates this Buffer from the given float data.
		 * This will register the buffer with OpenGL and send its data to OpenGL.
		 * Afterwards, this Buffer will have a valid id/name and can be used for drawing.
		 * @param data An array of type float
		 */
		void initBuffer(GLfloat data[]);
	
	};

}
