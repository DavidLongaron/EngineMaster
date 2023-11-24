#pragma once
#include "Module.h"
#include "vector"
#include "imgui.h"
class ModuleEditor :public Module
{

  public:
	ModuleEditor();
	~ModuleEditor();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OpenLog();
	std::vector<char*> appLog;
};

