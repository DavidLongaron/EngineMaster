#pragma once
#include <vector>
namespace tinygltf {
	class Model;
}
class ModuleModel
{
public:
	const void Load(const char* assetFileName)const;
	void LoadMaterials(const tinygltf::Model& srcModel);

private:
	std::vector<unsigned int> textures;
};

