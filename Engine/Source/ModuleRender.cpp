#include "ModuleRender.h"
#include "ModuleModel.h"
#include "ModuleCamera.h"
#include "Mesh.h"
#include "Globals.h"
#include "Application.h"
#include "GL/glew.h"
ModuleRender::ModuleRender()
{
	model = new ModuleModel;
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	
	model->Load("Assets/Models/Triangle/Triangle.gltf");

	return true;
}

update_status ModuleRender::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	auto model_matrix = App->GetModuleCamera()->GetModelMatrix();
	auto view_matrix = App->GetModuleCamera()->GetViewMatrix();
	auto projection_matrix = App->GetModuleCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(3, 1, GL_TRUE, &model_matrix[0][0]);
	glUniformMatrix4fv(4, 1, GL_TRUE, &view_matrix[0][0]);
	glUniformMatrix4fv(5, 1, GL_TRUE, &projection_matrix[0][0]);
	model->ERROR
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
