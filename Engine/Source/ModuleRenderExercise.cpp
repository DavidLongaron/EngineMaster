#include "ModuleRenderExercise.h"
#include "ModuleDebugDraw.h"
#include "SDL.h"
#include "GL/glew.h"
#include "Application.h"
#include "ModuleWindow.h"
#define _USE_MATH_DEFINES

#include <cmath>
//// Vertex Shader source code
const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout(location = 0)uniform mat4 model;\n"
"layout(location = 1) uniform mat4 view;\n"
"layout(location = 2) uniform mat4 proj;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

//Frustum frustum;
ModuleRenderExercise::ModuleRenderExercise()
{
}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{
}

// Called before render is available
bool ModuleRenderExercise::Init()
{
	//frustum.type = FrustumType::PerspectiveFrustum;
	//frustum.pos = float3::zero;
	//frustum.front = -float3::unitZ;
	//frustum.up = float3::unitY;
	//frustum.nearPlaneDistance = 0.1f;
	//frustum.farPlaneDistance = 100.0f;
	//frustum.verticalFov = static_cast<float>(M_PI / 4.0f);
	//frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * static_cast<float>(App->GetWindow()->height / App->GetWindow()->width));
	//proj = frustum.ProjectionMatrix();
	//view = frustum.ViewMatrix();
	float vertices[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
	};


    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	    unsigned int vertexShader;
	    vertexShader = glCreateShader(GL_VERTEX_SHADER);
	    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	    glCompileShader(vertexShader);
	    unsigned int fragmentShader;
	    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	    glCompileShader(fragmentShader);
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
		glUseProgram(shaderProgram);


	
	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRenderExercise::Update()
{
	
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{

	return UPDATE_CONTINUE;
}
