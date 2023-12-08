#pragma once
#include "Module.h"
#include <string>
class ModuleTexture :public Module
{
public:
	ModuleTexture();
	virtual ~ModuleTexture();

	bool Init();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	unsigned int LoadTexture(std::string texturePath);
	const unsigned int& GetTexture1() const {
		return texture;
	}
	private:
		unsigned int texture;
		wchar_t* textureLocation;
};


