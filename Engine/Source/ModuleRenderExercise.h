#pragma once
#include "Module.h"
//#include "MathGeoLib/include/Geometry/Frustum.h"
//#include "Math/float3x4.h"
//#include "Math/float4x4.h"

class ModuleRenderExercise :public Module
{
	private:
	 unsigned int VBO;
	 unsigned int VAO;
	 unsigned int shaderProgram;
	 void* context;
	public:
	 ModuleRenderExercise();
	 virtual ~ModuleRenderExercise();

	 bool Init();
	 update_status PreUpdate();
	 update_status Update();
	 update_status PostUpdate();
	 //Frustum frustum;
	 //float4x4 proj;
	 //float3x4 view;

};

