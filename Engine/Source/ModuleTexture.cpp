#define _CRT_SECURE_NO_WARNINGS
#include "ModuleTexture.h"

#include "Application.h"
#include "ModuleCamera.h"
#include "SDL.h"
#include "GL/glew.h"

#include "Math/MathFunc.h"
#include "DirectXTex.h"
#include <stdlib.h>
ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}
bool ModuleTexture::Init()
{
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	//int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true);
	//unsigned char* data = stbi_load("Assets/Textures/container.jpg", &width, &height, &nrChannels, 0);

	const char* port = "Assets/Textures/container.jpg";
	size_t size = strlen(port) + 1;
	wchar_t* textureLocation = new wchar_t[size];
	size_t outSize;

	mbstowcs_s(&outSize, textureLocation, size, port, size - 1);

	DirectX::ScratchImage data;
	DirectX::LoadFromDDSFile(textureLocation, DirectX::DDS_FLAGS_NONE, nullptr, data);
	
	if (!data.GetImageCount()) {
		DirectX::LoadFromTGAFile(textureLocation, DirectX::TGA_FLAGS_NONE,nullptr, data);
	}
	if (!data.GetImageCount()) {
		DirectX::LoadFromWICFile(textureLocation, DirectX::WIC_FLAGS_NONE, nullptr, data);
	}

	if (data.GetImageCount())
	{

		GLint internalFormat;
		GLenum format;
		GLenum type;
		switch (data.GetMetadata().format)
		{
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			type = GL_UNSIGNED_BYTE;
			break;
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		case DXGI_FORMAT_B8G8R8A8_UNORM:
			internalFormat = GL_RGBA8;
			format = GL_BGRA;
			type = GL_UNSIGNED_BYTE;
			break;
		case DXGI_FORMAT_B5G6R5_UNORM:
			internalFormat = GL_RGB8;
			format = GL_BGR;
			type = GL_UNSIGNED_BYTE;
			break;
		default:
			assert(false && "Unsupported format");
		}



		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, data.GetMetadata().width, data.GetMetadata().height, 0, format, type, data.GetPixels());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("Failed to load texture")
	}
	/*stbi_image_free(data);*/


	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	//unsigned char* data2 = stbi_load("Assets/Textures/crow.jpg", &width, &height, &nrChannels, 0);
	//if (data2)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	LOG("Failed to load texture")
	//}
	//stbi_image_free(data2);
	return true;
}

update_status ModuleTexture::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleTexture::Update()
{
	auto model_matrix = App->GetModuleCamera()->GetModelMatrix();
	auto view_matrix = App->GetModuleCamera()->GetViewMatrix();
	auto projection_matrix = App->GetModuleCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(3, 1, GL_TRUE, &model_matrix[0][0]);

	glUniformMatrix4fv(4, 1, GL_TRUE, &view_matrix[0][0]);
	glUniformMatrix4fv(5, 1, GL_TRUE, &projection_matrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);


	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2);
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate()
{

	return UPDATE_CONTINUE;
}
