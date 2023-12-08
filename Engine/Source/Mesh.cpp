#include "Mesh.h"
#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleModel.h"
#include "SDL.h"
#include "GL/glew.h"
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE
#include "tiny_gltf.h"

void Mesh::RenderMesh()
{
	glUseProgram(App->GetModuleProgram()->GetShaderProgram());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void Mesh::LoadMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
{
	
	//LLmar a los otros load aqui
	LoadVBO(model, mesh, primitive);
	LoadEBO(model, mesh, primitive);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * vertexCount));
	glBindVertexArray(0);
}

void Mesh::LoadVBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
{
	const unsigned char* bufferPos = nullptr;
	const unsigned char* bufferTexCoord = nullptr;


	const auto& itPos = primitive.attributes.find("POSITION");
	if (itPos != primitive.attributes.end())
	{
		const tinygltf::Accessor& posAcc = model.accessors[itPos->second];
		vertexCount = posAcc.count;
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
		bufferPos = &(model.buffers[posView.buffer].data[posAcc.byteOffset + posView.byteOffset]);
	}

	const auto& itTexCoord = primitive.attributes.find("TEXCOORD_0");
	unsigned int textureCount = 0;
	if (itTexCoord != primitive.attributes.end())
	{
		const tinygltf::Accessor& texCoordAcc = model.accessors[itTexCoord->second];


		textureCount = texCoordAcc.count;
		assert(textureCount == vertexCount);
		SDL_assert(texCoordAcc.type == TINYGLTF_TYPE_VEC2);
		SDL_assert(texCoordAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& texCoordView = model.bufferViews[texCoordAcc.bufferView];
		bufferTexCoord = &(model.buffers[texCoordView.buffer].data[texCoordAcc.byteOffset + texCoordView.byteOffset]);

	}
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 2 *vertexCount, nullptr, GL_STATIC_DRAW);

	float* data = reinterpret_cast<float*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	unsigned int loopIndex = 0;
	for (size_t i = 0; i < vertexCount; ++i)
	{
		data[loopIndex++] = *reinterpret_cast<const float*>(bufferPos);
		bufferPos += sizeof(float);

		data[loopIndex++] = *reinterpret_cast<const float*>(bufferPos);
		bufferPos += sizeof(float);

		data[loopIndex++] = *reinterpret_cast<const float*>(bufferPos);
		bufferPos += sizeof(float);
		
	}

	for (size_t i = 0; i < textureCount; ++i)
	{
		data[loopIndex++] = *reinterpret_cast<const float*>(bufferTexCoord);
		bufferTexCoord += sizeof(float);

		data[loopIndex++] = *reinterpret_cast<const float*>(bufferTexCoord);
		bufferTexCoord += sizeof(float);
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
}


void Mesh::LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive) {
	if (primitive.indices >= 0)
	{


		const tinygltf::Accessor& indAcc = model.accessors[primitive.indices];
		indicesCount = indAcc.count;
		const tinygltf::BufferView& indView = model.bufferViews[indAcc.bufferView];

		const unsigned char* buffer = &(model.buffers[indView.buffer].data[indAcc.byteOffset + indView.byteOffset]);
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indAcc.count, nullptr, GL_STATIC_DRAW);
		unsigned int* ptr = reinterpret_cast<unsigned int*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
		if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT)
		{
			const uint32_t* bufferInd = reinterpret_cast<const uint32_t*>(buffer);
			for (uint32_t i = 0; i < indAcc.count; ++i) {
				ptr[i] = bufferInd[i];
			}
		}
		if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT)
		{
			const uint16_t* bufferInd = reinterpret_cast<const uint16_t*>(buffer);
			for (uint16_t i = 0; i < indAcc.count; ++i) {
				ptr[i] = bufferInd[i];
			}
		}
		if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE)
		{
		
			for (uint8_t i = 0; i < indAcc.count; ++i) {
				ptr[i] = buffer[i];
			}
		}
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}
}