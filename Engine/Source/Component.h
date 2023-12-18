#pragma once
#include "Globals.h"
enum ComponentType
{
	TRANSFORM = 1,
	MESH,
	MATERIAL
};
class GameObject;
class Component
{
public:
	virtual void Enable();
	virtual void Update();
	virtual void Disable();


private:
	ComponentType type;
	bool isActive;
	GameObject* owner;

};

