#pragma once
#include "Module.h"
#include "Globals.h"

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};


class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	KeyState GetMouseButton(int id) const
	{
		return mouseButtons[id-1];
	}
	int const GetMouseWheel() const {
		return mouseWheel;
	}
	float* const GetMouseMotions() const {
		return mouseMotions;
	}
	float* const GetMouseCurrentPositions() const {
		return mouseCurrentPositions;
	}
	float* const GetMouseLastPosition() const {
		return mouseLastPosition;
	}
	void ResetMouseWheel() {
		mouseWheel = 0;
	}
	void ResetMouseMotions() {
		mouseMotions[0] = 0;
		mouseMotions[1] = 0;
		mouseMotions[2] = 0;
	}
private:
	 KeyState* keyboard = nullptr;
	 KeyState* mouseButtons = nullptr;
	 int mouseWheel = 0;
	 float* mouseMotions = nullptr;
	 float* mouseCurrentPositions = nullptr;
	 float* mouseLastPosition = nullptr;

};