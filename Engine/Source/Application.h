#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"
#include "SDL.h"
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
class ModuleScene;
class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    inline ModuleOpenGL* GetModuleOpenGL() const { return moduleOpenGL; }
    inline ModuleTexture* GetModuleTexture() const { return moduleTexture; }
    inline ModuleWindow* GetModuleWindow() const { return moduleWindow; }
    inline ModuleInput*  GetModuleInput() const { return moduleInput; }
    inline ModuleRender* GetModuleRender() { return moduleRender; }
    inline ModuleDebugDraw* GetModuleDebugDraw() const { return moduleDebugDraw; }
    inline ModuleEditor* GetModuleEditor() const { return moduleEditor; }
    inline ModuleProgram* GetModuleProgram() const { return moduleProgram; }
    inline ModuleCamera* GetModuleCamera() const { return moduleCamera; }
    inline ModuleScene* GetModuleScene() const { return moduleScene; }
    Uint64 currentTicks;
    unsigned int deltaTicks;
    unsigned int fps = 0;
    float miliSecondsFrame = 0;
    Uint64 microSecondsEnd=0;
    Uint64 microSecondsBegin = 0;
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
    ModuleScene* moduleScene = nullptr;
    std::list<Module*> modules;

};

extern Application* App;
