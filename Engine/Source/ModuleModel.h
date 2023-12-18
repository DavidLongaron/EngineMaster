#pragma once
#include <vector>
#include <string>
namespace tinygltf {
	class Model;
	class Node;
}
class Mesh;
class GameObject;
class ModuleModel
{
public:
	ModuleModel();
	~ModuleModel();
	const void Load(const std::string& assetFileName);
	void LoadMaterials(const tinygltf::Model& srcModel);
	inline const std::vector<Mesh*>& GetMeshes() const { return meshes; }
	
private:
	std::vector<unsigned int> textures;
	std::vector<Mesh*> meshes;
	GameObject* TraverseAllNodes(tinygltf::Node node);
	tinygltf::Model* model=nullptr;
};


