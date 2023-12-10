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
	void OpenGeneralMenu();
	void OpenTransformationMenu();
	void OpenFPSMenu();
	std::vector<char*> appLog;
  private:
	  unsigned int currentTicks;
	  unsigned int deltaTicks;
	  unsigned int fps = 0;
	 /*std::vector<float> fpsLog(25);*/
	std::vector<float> fpsLog{0,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 };
	std::vector<float> msLog{ 0,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 };

};

