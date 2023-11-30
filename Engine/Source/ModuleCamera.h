#pragma once
#include "Module.h"
#include "Globals.h"
#include "Geometry\Frustum.h"
#include "Math/float4x4.h"
#include "Math/float3x4.h"

class ModuleCamera :public Module{
 public:
	ModuleCamera();
	~ModuleCamera();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	void SetFOV();
	void SetAspectRatio();
	void SetPlaneDistances();
	void SetPosition();
	void SetOrientation();
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();
	//bool CleanUp();
	//void WindowResized(unsigned width, unsigned height);
	//void* GetContext();
	//void RenderVBO(unsigned vbo, unsigned program, unsigned vao);


private:
	void* context;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int texture1;
	unsigned int texture2;
	Frustum frustum;
	float4x4 proj;
	float4x4 view;
	float4x4 model;
};

