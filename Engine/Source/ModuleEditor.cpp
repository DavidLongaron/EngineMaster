#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

ModuleEditor::ModuleEditor()
{
}

// Destructor
ModuleEditor::~ModuleEditor()
{
}

// Called before render is available
bool ModuleEditor::Init()
{
	ImGui::CreateContext();


	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	//ImGuiStyle& style = ImGui::GetStyle();
	//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//	style.WindowRounding = 0.0f;
	//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	//}

	SDL_GL_MakeCurrent(App->GetWindow()->window, App->GetOpenGL()->GetContext());

	ImGui_ImplSDL2_InitForOpenGL(App->GetWindow()->window, App->GetOpenGL()->GetContext());
	ImGui_ImplOpenGL3_Init("#version 460");


	return true;
}

update_status ModuleEditor::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->GetWindow()->window);
	ImGui::NewFrame();

	bool show_demo_window = true;
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGui::ShowDemoWindow(&show_demo_window);
	static float f = 0.0f;
	static int counter = 0;

	ImGui::SetNextWindowSize(ImVec2(800, 800), ImGuiCond_FirstUseEver);
    OpenLog();

	ImGui::Render();
	

	/*SDL_GL_MakeCurrent(App->GetWindow()->window, App->GetOpenGL()->GetContext());*/


	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
	SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{

	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown(); 
	ImGui::DestroyContext();
	return true;
}


    void ModuleEditor::OpenLog() {
    ImGui::Begin("My Log");
    ImGui::SameLine();
    bool clear= ImGui::Button("Clear");
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
  
    if (clear) {
        appLog.clear();
    }
    if (copy) {
        ImGui::LogToClipboard();
    }

    for (char* text : appLog) {
        ImGui::TextUnformatted(text);
    }
    ImGui::End();
}
