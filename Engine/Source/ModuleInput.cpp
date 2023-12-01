#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleOpenGL.h"
#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "SDL_scancode.h"

typedef unsigned __int8 Uint8;

constexpr unsigned int MAX_KEYS = 300;
constexpr unsigned int MAX_BUTTONS = 2;
ModuleInput::ModuleInput()
{
    keyboard = new KeyState[MAX_KEYS];
    mouseButtons = new KeyState[MAX_BUTTONS];
    memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
    memset(mouseButtons, KEY_IDLE, sizeof(KeyState) * MAX_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
    delete[] keyboard;
    keyboard = nullptr;

    delete[] mouseButtons;
    mouseButtons = nullptr;
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    const Uint8* keys= SDL_GetKeyboardState(NULL);

    for (unsigned int i = 0; i < MAX_KEYS; i++)
    {
        if (keys[i] == 1) {
            if (keyboard[i] == KEY_IDLE) {
                keyboard[i] = KEY_DOWN;
            }
            else {
                keyboard[i] = KEY_REPEAT;
            }
        }
        else {
            if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN) {
                keyboard[i] = KEY_UP;
            }
            else {
                keyboard[i] = KEY_IDLE;
            }
        }
    }

    SDL_Event sdlEvent;
    
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_MOUSEBUTTONDOWN:
                if (mouseButtons[sdlEvent.button.button - 1] == KEY_DOWN) {
                    mouseButtons[sdlEvent.button.button - 1] = KEY_REPEAT;
                }
                else if (mouseButtons[sdlEvent.button.button - 1] == KEY_IDLE) {
                    mouseButtons[sdlEvent.button.button - 1] = KEY_DOWN;
                }
            case SDL_MOUSEBUTTONUP:
                if (mouseButtons[sdlEvent.button.button - 1] == KEY_UP) {
                    mouseButtons[sdlEvent.button.button - 1] = KEY_IDLE;
                }
                else if (mouseButtons[sdlEvent.button.button - 1] == KEY_REPEAT) {
                    mouseButtons[sdlEvent.button.button - 1] = KEY_UP;
                    }
                    
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->GetModuleOpenGL()->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                else if(sdlEvent.window.event== SDL_WINDOWEVENT_CLOSE)
                    return UPDATE_STOP;
                break;
        }
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
    }

   
   
    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
