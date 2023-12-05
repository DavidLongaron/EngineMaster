#pragma once
#include <vector>
namespace tinygltf {
	class Model;
}
class Mesh;
class ModuleModel
{
public:
	const void Load(const char* assetFileName);
	void LoadMaterials(tinygltf::Model& srcModel);
	const std::vector<Mesh*> GetMeshes() const { return meshes; }
private:
	std::vector<unsigned int> textures;
	std::vector<Mesh*> meshes;

};

