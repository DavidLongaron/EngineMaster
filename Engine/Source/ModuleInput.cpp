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
constexpr unsigned int MAX_BUTTONS = 3;
ModuleInput::ModuleInput()
{
    keyboard = new KeyState[MAX_KEYS];
    mouseButtons = new KeyState[MAX_BUTTONS];
    mouseCurrentPositions = new float[2];
    mouseMotions = new float[2];
    mouseLastPosition = new float[2];
    mouseLastPosition[0] = 0;
    mouseLastPosition[1] = 0;
    memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
    memset(mouseButtons, KEY_IDLE, sizeof(KeyState) * MAX_BUTTONS);
    memset(mouseCurrentPositions, KEY_IDLE, sizeof(KeyState) * 2);
    memset(mouseMotions, KEY_IDLE, sizeof(KeyState) * 2);
}

// Destructor
ModuleInput::~ModuleInput()
{
    delete[] keyboard;
    keyboard = nullptr;

    delete[] mouseButtons;
    mouseButtons = nullptr;

    delete[] mouseCurrentPositions;
    mouseCurrentPositions = nullptr;

    delete[] mouseMotions;
    mouseMotions = nullptr;

    delete[] mouseLastPosition;
    mouseLastPosition = nullptr;
    delete[] droppedFileDir;
    droppedFileDir = nullptr;
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


update_status ModuleInput::PreUpdate()
{
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    


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
    };

    for (unsigned int i = 0; i < MAX_BUTTONS; i++)
    {
    
            if (mouseButtons[i] == KEY_DOWN) {
               mouseButtons[i] = KEY_REPEAT;
            }

            if (mouseButtons[i] == KEY_UP) {
                mouseButtons[i] = KEY_IDLE;
            }
   
    };

    int mouseXPosition;
    int mouseYPosition;
    SDL_GetMouseState(&mouseXPosition, &mouseYPosition);
    mouseCurrentPositions[0] = mouseXPosition;
    mouseCurrentPositions[1] = mouseYPosition;

    mouseMotions[0] = 0;
    mouseMotions[1] = 0;


    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            return UPDATE_STOP;

        case SDL_MOUSEBUTTONDOWN:

            mouseButtons[sdlEvent.button.button - 1] = KEY_DOWN;

            break;

        case SDL_MOUSEBUTTONUP:
                mouseButtons[sdlEvent.button.button - 1] = KEY_UP;
            break;

        case SDL_WINDOWEVENT:
            if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                App->GetModuleOpenGL()->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
            else if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE)
                return UPDATE_STOP;
            break;

        case SDL_MOUSEMOTION:
            mouseCurrentPositions[0] = sdlEvent.motion.x;
            mouseCurrentPositions[1] = sdlEvent.motion.y;
            break;
        case SDL_MOUSEWHEEL:
            mouseWheel = sdlEvent.wheel.y;
            break;
        case SDL_DROPFILE:
            droppedFileDir = sdlEvent.drop.file;


            break;
        }

        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
    }


    return UPDATE_CONTINUE;
}


// Called every draw update
update_status ModuleInput::Update()
{
    
   
   
    return UPDATE_CONTINUE;
}

update_status ModuleInput::PostUpdate()
{
    mouseLastPosition[0] = mouseCurrentPositions[0];
    mouseLastPosition[1] = mouseCurrentPositions[1];


    return UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
