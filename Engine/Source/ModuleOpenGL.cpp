#include "Globals.h"
#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "GL/glew.h"
#include "stb_image.h"
#include "Math/MathFunc.h"

ModuleOpenGL::ModuleOpenGL()
{

}

// Destructor
ModuleOpenGL::~ModuleOpenGL()
{
}
/*
fragment shader with uniform
#version 460
out vec4 squareColor;
uniform vec4 color;
void main()
{
squareColor= color;
}


*/

float vertices[] = {
	 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // top right
	-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,// top left 
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,// bottom right


};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};


void __stdcall OurOpenGLErrorFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	const char* tmp_source = "", * tmp_type = "", * tmp_severity = "";
	switch (source) {
	case GL_DEBUG_SOURCE_API: tmp_source = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: tmp_source = "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: tmp_source = "Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY: tmp_source = "Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION: tmp_source = "Application"; break;
	case GL_DEBUG_SOURCE_OTHER: tmp_source = "Other"; break;
	};
	switch (type) {
	case GL_DEBUG_TYPE_ERROR: tmp_type = "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: tmp_type = "Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: tmp_type = "Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY: tmp_type = "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE: tmp_type = "Performance"; break;
	case GL_DEBUG_TYPE_MARKER: tmp_type = "Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP: tmp_type = "Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP: tmp_type = "Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER: tmp_type = "Other"; break;
	};
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH: tmp_severity = "high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM: tmp_severity = "medium"; break;
	case GL_DEBUG_SEVERITY_LOW: tmp_severity = "low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: tmp_severity = "notification"; break;
	};
	LOG("<Source:%s> <Type:%s> <Severity:%s> <ID:%d> <Message:%s>\n", tmp_source, tmp_type, tmp_severity, id, message);
}



void ModuleOpenGL::RenderVBO(unsigned vbo, unsigned program, unsigned vao)
{	
	glUseProgram(program);

	glUniformMatrix4fv(3, 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(4, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(5, 1, GL_TRUE, &proj[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//glUniform1i(glGetUniformLocation(App->GetModuleProgram()->shaderProgram, "texture1"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	//glUniform1i(glGetUniformLocation(App->GetModuleProgram()->shaderProgram, "texture2"), 1);
	glBindVertexArray(vao);


	// 2 triangle to draw = 6 vertices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}


// Called before render is available
bool ModuleOpenGL::Init()
{
	LOG("Creating Renderer context");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits
	context = SDL_GL_CreateContext(App->GetWindow()->window);
	SDL_GL_MakeCurrent(App->GetWindow()->window, context);
	SDL_GL_SetSwapInterval(1);
	GLenum err = glewInit();
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
	glDebugMessageCallback(&OurOpenGLErrorFunction, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,true);
	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("Assets/Textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("Failed to load texture")
	}
	stbi_image_free(data);

	//texture 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	unsigned char* data2 = stbi_load("Assets/Textures/crow.jpg", &width, &height, &nrChannels, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("Failed to load texture")
	}
	stbi_image_free(data2);
	//glUniform1i(glGetUniformLocation(App->GetModuleProgram()->shaderProgram, "texture1"), 0);
	//glUniform1i(glGetUniformLocation(App->GetModuleProgram()->shaderProgram, "texture2"), 1);

	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = { 0.0f, 1.0f, 4.0f };
	frustum.front = -float3::unitZ;
	//frustum.front = (float3::zero-frustum.pos);
	frustum.front.Normalize();
	frustum.up = float3::unitX.Cross(frustum.front).Normalized();
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = (float)M_PI / 4.0f;

	float aspect = static_cast<float>(App->GetWindow()->width) / static_cast<float>(App->GetWindow()->height);
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspect);
	proj = frustum.ProjectionMatrix();
	view = float4x4(frustum.ViewMatrix());

	model = /*float3x3::identity;*/	
		float4x4::FromTRS(float3(0.0f, 1.0f, 0.5f),
		float4x4::RotateZ(DegToRad(90)),
		float3(1.0f, 1.0f, 1.0f));
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture atribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	float vec[] = { 1.0f, 0.0f, 0.0f, 1.0f };




	return true;
}

update_status ModuleOpenGL::PreUpdate()
{
	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise

	glClearColor(0.4f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleOpenGL::Update()
{

	RenderVBO(VBO, App->GetModuleProgram()->shaderProgram, VAO);

	//float timeValue = (float)SDL_GetTicks()/1000;
	//float timeValue2 = (float)SDL_GetTicks() / 900;
	//float timeValue3 = (float)SDL_GetTicks() / 800;
	//float randomValue = sin(timeValue) / 2.0f + 0.5f;
	//float randomValue2 = sin(timeValue2) / 2.0f + 0.5f;
	//float randomValue3 = sin(timeValue3) / 2.0f + 0.5f;

	//int vertexColorLocation = glGetUniformLocation(App->GetModuleProgram()->shaderProgram, "color");
	//glUniform4f(vertexColorLocation, randomValue, randomValue2, randomValue3, 1.0f);
	return UPDATE_CONTINUE;
}

update_status ModuleOpenGL::PostUpdate()
{
	SDL_GL_SwapWindow(App->GetWindow()->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleOpenGL::CleanUp()
{
	LOG("Destroying renderer");
	SDL_GL_DeleteContext(context);
	//Destroy window

	return true;
}

void ModuleOpenGL::WindowResized(unsigned width, unsigned height)
{
	glViewport(0, 0, width, height);
}

void* ModuleOpenGL::GetContext()
{
	return context;
}



