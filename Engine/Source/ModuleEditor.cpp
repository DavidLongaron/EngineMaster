#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <windows.h>
#include <shellapi.h>


ModuleEditor::ModuleEditor() : fpsLog(25), msLog(25)
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

	SDL_GL_MakeCurrent(App->GetModuleWindow()->GetWindow(), App->GetModuleOpenGL()->GetContext());

	ImGui_ImplSDL2_InitForOpenGL(App->GetModuleWindow()->GetWindow(), App->GetModuleOpenGL()->GetContext());
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
	static int counter = 0;

	msLog.push_back(App->miliSecondsFrame*1000);
	fpsLog[counter] = (1 / (msLog[counter]))*1000;
	counter++;
	if (counter > 24) {
			counter = 0;
		}
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->GetModuleWindow()->GetWindow());
	ImGui::NewFrame();

	/*bool show_demo_window = false;*/
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	//ImGui::ShowDemoWindow(&show_demo_window);
	static float f = 0.0f;


	ImGui::SetNextWindowSize(ImVec2(800, 800), ImGuiCond_FirstUseEver);
    OpenLog();
	OpenGeneralMenu();
	OpenTransformationMenu();
	OpenFPSMenu();
	ImGui::Render();
	

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

	void ModuleEditor::OpenGeneralMenu() {
		ImGui::Begin("Help");
			if (ImGui::MenuItem("Documentation")) {
				ShellExecute(0, 0,"https://github.com/MrDfu/EngineMaster", 0, 0, SW_SHOW);
			}
			if (ImGui::MenuItem("Download latest")) {
				ShellExecute(0, 0, "https://github.com/MrDfu/EngineMaster", 0, 0, SW_SHOW);
			}
			if (ImGui::MenuItem("About")) {
				ShellExecute(0, 0, "https://github.com/MrDfu/EngineMaster/blob/main/README.md", 0, 0, SW_SHOW);
			}

		ImGui::End();
	}

	void ModuleEditor::OpenTransformationMenu() {
		ImGui::Begin("Edit Model");
		ImGui::SliderFloat3("Transformation", &(App->GetModuleCamera()->viewSize.x), 0.0f, 50.0f);
		ImGui::SliderFloat3("Rotation", &(App->GetModuleCamera()->modelRot.x), -180.0f, 180.0f);
		ImGui::End();
	}
	void ModuleEditor::OpenFPSMenu() {
		char title[25];
		ImGui::Begin("Performance");
		sprintf_s(title, 25, "Framerate %.1f", fpsLog[fpsLog.size()-1]);
		ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Miliseconds %0.1f", msLog[msLog.size()-1]);
		ImGui::PlotHistogram("##framerate", &msLog[0], msLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		
		ImGui::End();
	}