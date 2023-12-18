#include "ModuleRender.h"
#include "ModuleModel.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleInput.h"
#include "ModuleCamera.h"
#include "Mesh.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"
#include "GL/glew.h"
ModuleRender::ModuleRender()
{
	model = new ModuleModel;
}

// Destructor
ModuleRender::~ModuleRender()
{
}

void RenderGoMeshes(GameObject* go) {
	if (go->mesh) {
		go->mesh->RenderMesh();
	}
	if (!go->children.empty()) {
		for (GameObject* goChild : go->children)
		{
			RenderGoMeshes(goChild);
		}
	}
}
// Called before render is available
bool ModuleRender::Init()
{
	
	model->Load("Assets/Models/BakerHouse/BakerHouse.gltf");

	return true;
}

update_status ModuleRender::PreUpdate()
{

	return UPDATE_CONTINUE;
}


// Called every draw update
update_status ModuleRender::Update()
{
	if (App->GetModuleInput()->GetDroppedFileDir() != "0") {
		model->Load(App->GetModuleInput()->GetDroppedFileDir());
		App->GetModuleInput()->ResetDroppedFileDir();
	}
	auto model_matrix = App->GetModuleCamera()->GetModelMatrix();
	auto view_matrix = App->GetModuleCamera()->GetViewMatrix();
	auto projection_matrix = App->GetModuleCamera()->GetProjectionMatrix();
	glUseProgram(App->GetModuleProgram()->GetShaderProgram());
	glUniformMatrix4fv(3, 1, GL_TRUE, &model_matrix[0][0]);
	glUniformMatrix4fv(4, 1, GL_TRUE, &view_matrix[0][0]);
	glUniformMatrix4fv(5, 1, GL_TRUE, &projection_matrix[0][0]);

	// Aqui es donde va a loopear por todos los gameobjects y todos sus hijos y renderizar los que tengan mesh


	if (App->GetModuleScene()->GetRoot()) {
		RenderGoMeshes(App->GetModuleScene()->GetRoot());
	}


	//if (!model->GetMeshes().empty()) {

	//	for (auto& mesh : model->GetMeshes())
	//	{

	//		mesh->RenderMesh();
	//	}
	//}
		/*
		Añadir array de meshes en el model y llamarlos desde el modulerenderer para llamar render en el update.
		
		*/
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	
	return UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	return true;
}
