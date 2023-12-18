#include "ModuleModel.h"
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"
#include "Mesh.h"
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleTexture.h"
#include <iostream>
#include "Math/float4x4.h"
#include "ComponentTransform.h"
#include "ModuleScene.h"
ModuleModel::ModuleModel()
{
	model = new tinygltf::Model();
}
ModuleModel::~ModuleModel()
{
	meshes.clear();
	delete model;
	model = nullptr;

}
const void ModuleModel::Load(const std::string& assetFileName)
{
	meshes.clear();
	
	tinygltf::TinyGLTF gltfContext;
	std::string error, warning;
	bool loadOk = gltfContext.LoadASCIIFromFile(model, &error, &warning, assetFileName);
	if (!loadOk)
	{
		LOG("Error loading %s: %s", assetFileName, error.c_str());
		return;
	}
	for (const auto& srcMesh : model->meshes)
	{
		for (const auto& primitive : srcMesh.primitives)
		{
			Mesh* mesh = new Mesh;
			mesh->LoadMesh(*(model), srcMesh, primitive);
			meshes.push_back(mesh);
		}

	}
	if (!model->textures.empty()) {
		

		LoadMaterials(*model);
	
	}

	for (const tinygltf::Scene& scene : model->scenes)
	{
		for (const int nodeID :scene.nodes) {
			model->nodes[nodeID];
		GameObject* modelGo= TraverseAllNodes(model->nodes[nodeID]);
		App->GetModuleScene()->GetRoot()->AddChild(modelGo);
		}
	}
}

GameObject* ModuleModel::TraverseAllNodes(tinygltf::Node node) {

	GameObject* go = new GameObject();
	float4x4 matrix;
	ComponentTransform* compTrans = static_cast<ComponentTransform*>(go->CreateComponent(TRANSFORM));
	if (node.matrix.size() == 16)
	{
		matrix = float4x4(
			node.matrix[0], node.matrix[1], node.matrix[2], node.matrix[3],
			node.matrix[4], node.matrix[5], node.matrix[6], node.matrix[7],
			node.matrix[8], node.matrix[9], node.matrix[10], node.matrix[11],
			node.matrix[12], node.matrix[13], node.matrix[14], node.matrix[15]
		);
		
		float3 pos;
		float3 scale;
		Quat rot;
		matrix.Decompose(pos, rot, scale);
		compTrans->SetPosition(pos);
		compTrans->SetRotation(rot);
		compTrans->SetScale(scale);
	}
	else {
		if (node.translation.size() == 3) {
			compTrans->SetPosition({ static_cast<float>(node.translation[0]),static_cast<float>(node.translation[1]), static_cast<float>(node.translation[2])});
		}
		if (node.rotation.size() == 4) {
			compTrans->SetRotation({ static_cast<float>(node.rotation[0]),static_cast<float>(node.rotation[1]), static_cast<float>(node.rotation[2]),static_cast<float>(node.rotation[3])});
		}
		if (node.scale.size() == 3) {
			compTrans->SetScale({ static_cast<float>(node.scale[0]),static_cast<float>(node.scale[1]), static_cast<float>(node.scale[2]) });
		}
	}
	if (node.mesh!=-1) {
		go->mesh = meshes[node.mesh];
	}
	if (node.children.size() > 0) {
		for (const int child : node.children) {
			go->AddChild(TraverseAllNodes(model->nodes[child]));
		}
	}
	
	return go;

}



void ModuleModel::LoadMaterials( const tinygltf::Model& srcModel)
{
	textures.clear();
	for (const auto& srcMaterial : srcModel.materials)
	{
		unsigned int textureId = 0;
		if (srcMaterial.pbrMetallicRoughness.baseColorTexture.index >= 0)
		{
			const tinygltf::Texture& texture = srcModel.textures[srcMaterial.pbrMetallicRoughness.baseColorTexture.index];
			const tinygltf::Image& image = srcModel.images[texture.source];
			textureId = (App->GetModuleTexture()->LoadTexture(image.uri));
		}
		textures.push_back(textureId);
	}

}