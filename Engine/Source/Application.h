#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRender;
class ModuleDebugDraw;
class ModuleEditor;
class ModuleProgram;
class ModuleCamera;
class ModuleTexture;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    ModuleOpenGL* GetModuleOpenGL() const { return moduleOpenGL; }
    ModuleTexture* GetModuleTexture() const { return moduleTexture; }
    ModuleWindow* GetModuleWindow() const { return moduleWindow; }
    ModuleInput*  GetModuleInput() const { return moduleInput; }
    ModuleRender* GetModuleRender() { return moduleRender; }
    ModuleDebugDraw* GetModuleDebugDraw() const { return moduleDebugDraw; }
    ModuleEditor* GetModuleEditor() const { return moduleEditor; }
    ModuleProgram* GetModuleProgram() const { return moduleProgram; }
    ModuleCamera* GetModuleCamera() const { return moduleCamera; }

private:

    ModuleOpenGL* moduleOpenGL = nullptr;
    ModuleWindow* moduleWindow = nullptr;
    ModuleInput* moduleInput = nullptr;
    ModuleRender* moduleRender = nullptr;
    ModuleDebugDraw* moduleDebugDraw = nullptr;
    ModuleEditor* moduleEditor = nullptr;    
    ModuleProgram* moduleProgram = nullptr;
    ModuleCamera* moduleCamera = nullptr;
    ModuleTexture* moduleTexture = nullptr;
    std::list<Module*> modules;

};

extern Application* App;
