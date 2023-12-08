#pragma once
#include "Module.h"
#include "Globals.h"
#include <string>
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
	 std::string GetDroppedFileDir() {
		if (droppedFileDir) {
			
			std::string fileDir(droppedFileDir);
			std::string assetStr = "Assets";
			size_t test = fileDir.find(assetStr);

			std::string fileDirShort = fileDir.substr(fileDir.find(assetStr), (fileDir.length() - fileDir.find(assetStr)));

			return fileDirShort;
		}
		std::string empty = "0";
		return empty;
	}
	void ResetDroppedFileDir() {
		droppedFileDir = nullptr;
	}
private:
	 KeyState* keyboard = nullptr;
	 KeyState* mouseButtons = nullptr;
	 int mouseWheel = 0;
	 float* mouseMotions = nullptr;
	 float* mouseCurrentPositions = nullptr;
	 float* mouseLastPosition = nullptr;
	 char* droppedFileDir = nullptr;

};