#pragma once
#include "Module.h"


class ModuleProgram :public Module{
 public:
	ModuleProgram();
	virtual ~ModuleProgram();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);
	unsigned int shaderProgram;


};

