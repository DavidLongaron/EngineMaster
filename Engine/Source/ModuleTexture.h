#pragma once
#include "Module.h"
class ModuleTexture :public Module
{
public:
	ModuleTexture();
	virtual ~ModuleTexture();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	const unsigned int& GetTexture1() const {
		return texture1;
	}
	const unsigned int& GetTexture2() const {
		return texture2;
	}
	private:
		unsigned int texture1;
		unsigned int texture2;

};

