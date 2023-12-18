#pragma once
#include "Module.h"
#include <vector>
class GameObject;
class ModuleScene :public Module
{
public:
	ModuleScene();
	virtual ~ModuleScene();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	inline GameObject* GetRoot()const {
		return root;
	};
	GameObject CreateGameObject() ;

private:
	GameObject* root;
};

