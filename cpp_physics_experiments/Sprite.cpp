#include "Sprite.h"

Sprite::Sprite() {
	_vboID = 0;
}

Sprite::~Sprite() {
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (_vboID == 0) {
		glGenBuffers(1, &_vboID); //Generate buffer
	}

	float vertexData[12];//Two values for 6 points, square is made of 2 triangles
	//First triangle
	vertexData[0] = x + width;
	vertexData[1] = y + height;

	vertexData[2] = x;
	vertexData[3] = y + height;

	vertexData[4] = x;
	vertexData[5] = y;

	//Second triangle
	vertexData[6] = x;
	vertexData[7] = y;

	vertexData[8] = x + width;
	vertexData[9] = y;

	vertexData[10] = x + width;
	vertexData[11] = y + height;

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID); //Binds vertex buffer (VBO) that contains vertex data

	glEnableVertexAttribArray(0); //Enable vertex attribute at location 0, see vertex shader

	//Tell OpenGL how to interpret the data in bound VBO
	//0: Matches layout(location=0) in shader
	//2: Each vertex has 2 floats, x,y
	//Each component is a float
	//Do not normalize
	//Stride of 0, no gaps between data
	//Pointer offset of 0, start at beginning
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); //This is where to start when draw
	
	//Treat each group of 3 vertices as triangle, start at 0, 6 vertices total (2 triangles)
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0); //Disable attribute array at location 0, not necessary but good hygiene

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Release buffer
}