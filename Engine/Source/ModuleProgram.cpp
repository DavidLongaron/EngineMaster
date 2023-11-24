#include "ModuleProgram.h"
#include "SDL.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "GL/glew.h"

#define _USE_MATH_DEFINES

#include <cmath>
ModuleProgram::ModuleProgram()
{
}

// Destructor
ModuleProgram::~ModuleProgram()
{
}




char* LoadShaderSource(const char* shader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, shader_file_name, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		data = (char*)malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	return data;
}

unsigned CompileShader(unsigned type, const char* source)
{
	unsigned int shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, 0);
	glCompileShader(shader_id);
	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shader_id, len, &written, info);
			LOG("Log Info: %s", info);
			free(info);
		}
	}
	return shader_id;
}

unsigned  ModuleProgram::CreateProgram(unsigned vtx_shader, unsigned frg_shader)
{
	 shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vtx_shader);
	glAttachShader(shaderProgram, frg_shader);
	glLinkProgram(shaderProgram);
	int res;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(shaderProgram, len, &written, info);
			LOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	return shaderProgram;
}


// Called before render is available
bool ModuleProgram::Init()
{



	const char* vertexShaderSource = LoadShaderSource("Assets/Shaders/vertexShader.txt");
	const char* fragmentShaderSource = LoadShaderSource("Assets/Shaders/fragmentShader.txt");
	unsigned int vertexShader;
	unsigned int fragmentShader;
	vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	CreateProgram(vertexShader, fragmentShader);



	return true;
}

update_status ModuleProgram::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleProgram::Update()
{

	
	return UPDATE_CONTINUE;
}

update_status ModuleProgram::PostUpdate()
{

	return UPDATE_CONTINUE;
}
