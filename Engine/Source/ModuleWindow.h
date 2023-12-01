#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();


	  SDL_Window* GetWindow() const {
		return window;
	}
	const int GetWidth() const {
		return width;
	}
	const int GetHeight() const {
		return height;
	}
	const SDL_Surface* GetScreen_Surface() const {
		return screen_surface;
	}

private:
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	int width;
	int height;
	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;

};

#endif // __ModuleWindow_H__