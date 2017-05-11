#include "Model.h"
#include <vector>

Model::Model()
{
	vertArr = 0;
	vertBuf = 0;
}

Model::Model(std::string modelFile)
{
	filename = modelFile;
	vertArr = 0;
	vertBuf = 0;
}


Model::~Model()
{
}

bool Model::readFile()
{
	std::string tag;
	float x, y, z;
	unsigned int a, b, c;
	char slash;

	std::ifstream inStream(filename);
	if (!inStream.is_open()) {
		std::cout << "Error occured, obj file could not be opened" << std::endl;
		return false;
	}

	while (std::getline(inStream, line)) {
		std::stringstream lineStream(line);
		lineStream >> tag;

		if (tag == "v") {
			lineStream >> x >> y >> z;
			locations.push_back(vec3(x, y, z));
		}
		else if (tag == "vt") {
			lineStream >> x >> y;
			uvs.push_back(vec2(x, y));
		}
		else if (tag == "vn") {
			lineStream >> x >> y >> z;
			normals.push_back(vec3(x, y, z));
		}
		else if (tag == "f") {
			for (int i = 0; i < 3; i++) {
				lineStream >> a >> slash >> b >> slash >> c;
				a--;
				b--;
				c--;
				VertInd newVertInd;
				newVertInd.locInd = a;
				newVertInd.uvInd = b;
				newVertInd.normInd = c;
				vertIndices.push_back(newVertInd);
			}
		}
	}

	return true;
}

bool Model::buffer()
{
	std::vector<Vertex()>;

	//loads obj file and fills vertIndices
	if(!readFile()) return false;
	vertCount = vertIndices.size();

	//duplicate vertices into a single buffer (in same order as vertIndices)
	std::vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++) {
		vertBufData[i] = {
			locations[vertIndices[i].locInd],
			uvs[vertIndices[i].uvInd],
			normals[vertIndices[i].normInd]
		};
	}

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertex) * vertCount,
		&vertBufData[0],
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		0
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(vec3)
	);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(sizeof(vec3) + sizeof(vec2))
	);
	glBindVertexArray(0);

	return true;
}

bool Model::render()
{
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);
	return true;
}
