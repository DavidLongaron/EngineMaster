#pragma once
#include "Module.h"
#include "Globals.h"
#include "Geometry\Frustum.h"
#include "Math/float4x4.h"
#include "Math/float3x4.h"


struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleOpenGL : public Module
{
public:
	ModuleOpenGL();
	~ModuleOpenGL();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);

	 void* GetContext () const {
		return context;
	}
	void SetCameraMatrix();
	void RenderVBO(unsigned vbo, unsigned program, unsigned vao);
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int texture1;
	unsigned int texture2;
	Frustum frustum;
	float4x4 proj;
	float4x4 cameraMatrix;
	float4x4 view;
	float4x4 model; 

private:
	void* context;
};
