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
	void RenderVBO(unsigned vbo, unsigned program, unsigned vao);


	   auto* GetContext() const {
		 return context;
	 }
	 const unsigned int& GetTexture1() const {
		 return texture1;
	 }
	 const unsigned int& GetTexture2() const {
		 return texture2;
	 }

	


private:
	void* context;
	unsigned int texture1;
	unsigned int texture2;
};
