#pragma once

namespace tinygltf {
	class Model;
	struct Mesh;
	struct Primitive;
}

class Mesh{
public:
	void RenderMesh();
	void LoadMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void LoadVBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	const unsigned int& GetVBO() const {
		return VBO;
	}
	const unsigned int& GetVAO() const {
		return VAO;
	}
	const unsigned int& GetEBO() const {
		return EBO;
	}

private:
	unsigned int indicesCount;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int vertexCount;

};

