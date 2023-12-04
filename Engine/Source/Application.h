#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
//class ModuleRenderExercise;
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

    ModuleOpenGL* GetModuleOpenGL() const { return moduleRender; }
    ModuleTexture* GetModuleTexture() const { return moduleTexture; }
    ModuleWindow* GetModuleWindow() const { return moduleWindow; }
    ModuleInput*  GetModuleInput() const { return moduleInput; }
    //ModuleRenderExercise* GetRenderExercise() { return renderExercise; }
    ModuleDebugDraw* GetModuleDebugDraw() const { return moduleDebugDraw; }
    ModuleEditor* GetModuleEditor() const { return moduleEditor; }
    ModuleProgram* GetModuleProgram() const { return moduleProgram; }
    ModuleCamera* GetModuleCamera() const { return moduleCamera; }

private:

    ModuleOpenGL* moduleRender = nullptr;
    ModuleWindow* moduleWindow = nullptr;
    ModuleInput* moduleInput = nullptr;
    //ModuleRenderExercise* renderExercise = nullptr;
    ModuleDebugDraw* moduleDebugDraw = nullptr;
    ModuleEditor* moduleEditor = nullptr;    
    ModuleProgram* moduleProgram = nullptr;
    ModuleCamera* moduleCamera = nullptr;
    ModuleTexture* moduleTexture = nullptr;
    std::list<Module*> modules;

};

extern Application* App;
