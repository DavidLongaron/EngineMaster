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

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    ModuleOpenGL* GetOpenGL() { return render; }
    ModuleWindow* GetWindow() { return window; }
    ModuleInput*  GetInput() { return input; }
    //ModuleRenderExercise* GetRenderExercise() { return renderExercise; }
    ModuleDebugDraw* GetModuleDebugDraw() { return debugDraw; }
    ModuleEditor* GetModuleEditor() { return editor; }
    ModuleProgram* GetModuleProgram() { return program; }
private:

    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    //ModuleRenderExercise* renderExercise = nullptr;
    ModuleDebugDraw* debugDraw = nullptr;
    ModuleEditor* editor = nullptr;    
    ModuleProgram* program = nullptr;
    std::list<Module*> modules;

};

extern Application* App;
