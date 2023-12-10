#pragma once
#include <vector>
#include <string>
namespace tinygltf {
	class Model;
}
class Mesh;
class ModuleModel
{
public:
	const void Load(const std::string& assetFileName);
	void LoadMaterials(tinygltf::Model& srcModel);
	inline const std::vector<Mesh*> GetMeshes() const { return meshes; }
private:
	std::vector<unsigned int> textures;
	std::vector<Mesh*> meshes;

};

