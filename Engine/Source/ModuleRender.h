#pragma once
#include "Module.h"
class ModuleTexture;
class ModuleModel;

class ModuleRender :
    public Module
{
public:
	ModuleRender();
	virtual ~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
private:
	ModuleModel* model = nullptr;
	ModuleTexture* texture = nullptr;

};



