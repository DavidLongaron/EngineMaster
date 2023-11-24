#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"


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
	void* GetContext();
	void RenderVBO(unsigned vbo, unsigned program, unsigned vao);
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int texture1;
	unsigned int texture2;
	Frustum frustum;
	float4x4 proj;
	float3x4 view;
	float4x4 model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi/ 4.0f),
		float3(2.0f, 1.0f, 1.0f));

private:
	void* context;
};
