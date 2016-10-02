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

		/**
		 * Default Buffer Type to use if none has been set explicitly.
		 * Most relevant are GL_ARRAY_BUFFER for Vertex Buffer Objects
		 * and GL_ELEMENT_ARRAY_BUFFER for Index Buffer Objects.
		 */
		static const GLenum DEFAULT_BUFFER_TYPE;

		/**
		 * Default Draw Type to use if none has been set explicitly.
		 */
		static const GLenum DEFAULT_DRAW_TYPE;


		static const GLenum DEFAULT_DATA_TYPE;

		/**
		 * Creates a BufferObject of the default type and with default draw type.
		 * In order to make use of this BufferObject, its data has to be set via setData().
		 */
		BufferObject();

		/**
		 * Creates a BufferObject of the specified type and with default draw type.
		 * In order to make use of this BufferObject, its data has to be set via setData().
		 * @param bufferType A valid Buffer Type
		 */
		BufferObject(GLenum bufferType);

		/**
		 * Creates a BufferObject of the specified type and specified draw type.
		 * In order to make use of this BufferObject, its data has to be set via setData().
		 * @param bufferType A valid Buffer Type
		 * @param drawType A valid Draw Type
		 */
		BufferObject(GLenum bufferType, GLenum drawType);

		/**
		 * Change the type of this Buffer. This will only have an effect if
		 * called before the Buffer's data has been set, otherwise it will
		 * do nothing.
		 * @param bufferType A valid Buffer Type
		 */
		void setBufferType(GLenum bufferType);

		/**
		 * Change the draw type of this Buffer. This will only have an effect
		 * if called before the Buffer's data has been set, otherwise it will
		 * do nothing.
		 * @param drawType A valid Draw Type
		 */
		void setDrawType(GLenum drawType);

		/**
		 * Set this buffer's data. This will create and initialize this Buffer.
		 * Afterwards, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data An array of type GLbyte
		 * @param size The size of the data in bytes
		 */
		void setData(GLbyte data[], GLsizeiptr size);

		/**
		 * Set this buffer's data. This will create and initialize this Buffer.
		 * Afterwards, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data An array of type GLubyte
		 * @param size The size of the data in bytes
		 */
		void setData(GLubyte data[], GLsizeiptr size);

		/**
		 * Set this buffer's data. This will create and initialize this Buffer.
		 * Afterwards, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data An array of type GLshort
		 * @param size The size of the data in bytes
		 */
		void setData(GLshort data[], GLsizeiptr size);

		/**
		 * Set this buffer's data. This will create and initialize this Buffer.
		 * Afterwards, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data An array of type GLushort
		 * @param size The size of the data in bytes
		 */
		void setData(GLushort data[], GLsizeiptr size);

		/**
		 * Set this buffer's data. This will create and initialize this Buffer.
		 * Afterwards, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data An array of type GLint
		 * @param size The size of the data in bytes
		 */
		void setData(GLint data[], GLsizeiptr size);

		/**
		 * Set this buffer's data. This will create and initialize this Buffer.
		 * Afterwards, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data An array of type GLuint
		 * @param size The size of the data in bytes
		 */
		void setData(GLuint data[], GLsizeiptr size);

		/**
		 * Set this buffer's data. This will create and initialize this Buffer.
		 * Afterwards, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data An array of type GLfloat
		 * @param size The size of the data in bytes
		 */
		void setData(GLfloat data[], GLsizeiptr size);

		/**
		 * Set this buffer's data. This will create and initialize this Buffer.
		 * Afterwards, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data An array of type GLdouble
		 * @param size The size of the data in bytes
		 */
		void setData(GLdouble data[], GLsizeiptr size);

		/**
		 * Get this Buffer's id/name as registered with OpenGL.
		 * @return This Buffer's id (name)
		 */
		GLuint getId() const;

		/**
		 * Get this Buffer's data size.
		 * @return This Buffer's data size
		 */
		GLsizeiptr getSize() const;


		GLenum getDataType() const;

		/**
		 * Get this Buffer's type.
		 * @return This Buffer's type
		 */
		GLenum getBufferType() const;

		/**
		 * Get this Buffer's draw type.
		 * @return This Buffer's draw type
		 */
		GLenum getDrawType() const;

		/**
		 * Bind this Buffer in the OpenGL state machine in order
		 * to perform actions on/with it.
		 */
		void bind() const;

		/**
		 * Unbind this Buffer (as well as any other of the same type)
		 * from the OpenGL state machine.
		 */
		void unbind() const;

		/**
		 * Delete this Buffer from OpenGL. This will not delete this object,
		 * just the actual Buffer from OpenGL.
		 */
		void free();

		bool operator==(const BufferObject& other) const;

	protected:

		GLuint id;
		GLsizeiptr size;
		GLenum dataType;
		GLenum bufferType;
		GLenum drawType;

		/**
		 * Let OpenGL generate an id/name for this Buffer and remember it.
		 */
		void generateId();

		/**
		 * Set this buffer's data. This will create and initialize this Buffer.
		 * Afterwards, this Buffer will have an id and can be bound and drawn.
		 * If the data has been set before, this will do nothing.
		 * @param data A pointer to the data to be filled into the buffer
		 * @param size The size of the data in bytes
		 * @param type The type of the data
		 */
		void setData(GLvoid* data, GLsizeiptr size, GLenum type);

		/**
		 * Actually creates this Buffer from the given data.
		 * This will register the buffer with OpenGL and send its data to OpenGL.
		 * Afterwards, this Buffer will have an id and can be used for drawing.
		 * @param data A pointer to the data to be filled into the buffer
		 */
		virtual void init(GLvoid* data);

	};

}
