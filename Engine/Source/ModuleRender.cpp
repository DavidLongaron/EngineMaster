#include "ModuleRender.h"
#include "ModuleModel.h"
#include "Mesh.h"
#include "Globals.h"

ModuleRender::ModuleRender()
{
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	return true;
}

update_status ModuleRender::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	ModuleModel* model = new ModuleModel;
	model->Load("./Assets/Models/Triangle/Triangle");
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	
	return UPDATE_CONTINUE;
}
