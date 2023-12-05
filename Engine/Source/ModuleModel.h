#pragma once
#include <vector>
namespace tinygltf {
	class Model;
}
class ModuleModel
{
public:
	const void Load(const char* assetFileName);
	void LoadMaterials(tinygltf::Model& srcModel);

private:
	std::vector<unsigned int> textures;
};

