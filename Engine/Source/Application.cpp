#pragma 
#define STB_IMAGE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include "stb_image.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "ModuleInput.h"
//#include "ModuleRenderExercise.h"
#include "ModuleDebugDraw.h"
#include "ModuleEditor.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(moduleWindow = new ModuleWindow());
	modules.push_back(moduleInput = new ModuleInput());
	modules.push_back(moduleCamera = new ModuleCamera());

	modules.push_back(moduleRender = new ModuleOpenGL());
	modules.push_back(moduleTexture = new ModuleTexture());
	//modules.push_back(renderExercise = new ModuleRenderExercise());
	modules.push_back(moduleProgram = new ModuleProgram());
	modules.push_back(moduleEditor = new ModuleEditor());
	modules.push_back(moduleDebugDraw = new ModuleDebugDraw());

}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}
