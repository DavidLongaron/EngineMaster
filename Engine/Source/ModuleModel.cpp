#include "ModuleModel.h"
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"
#include "Mesh.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"

const void ModuleModel::Load(const char* assetFileName)
{
	tinygltf::TinyGLTF gltfContext;
	tinygltf::Model model;
	std::string error, warning;
	bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, assetFileName);
	assert(loadOk);
	if (!loadOk)
	{
		LOG("Error loading %s: %s", assetFileName, error.c_str());
	}
	for (const auto& srcMesh : model.meshes)
	{
		for (const auto& primitive : srcMesh.primitives)
		{
			Mesh* mesh = new Mesh;
			mesh->LoadMesh(model, srcMesh, primitive);
		}

	}
	if (!model.textures.empty()) {
		

		LoadMaterials(model);
	
	}
}



void ModuleModel::LoadMaterials( tinygltf::Model& srcModel)
{
	for (const auto& srcMaterial : srcModel.materials)
	{
		unsigned int textureId = 0;
		if (srcMaterial.pbrMetallicRoughness.baseColorTexture.index >= 0)
		{
			const tinygltf::Texture& texture = srcModel.textures[srcMaterial.pbrMetallicRoughness.baseColorTexture.index];
			const tinygltf::Image& image = srcModel.images[texture.source];
			/*	textureId = (App->GetModuleTexture()->Load(image.uri));*/
		}
		textures.push_back(textureId);
	}

}