#include "ModuleCamera.h"
#include "GL/glew.h"
#include "Math/MathFunc.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL.h"


ModuleCamera::ModuleCamera()
{
}

// Destructor
ModuleCamera::~ModuleCamera()
{
}




// Called before render is available
bool ModuleCamera::Init()
{
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = { 0.0f, 1.0f, 4.0f };
	frustum.front = -float3::unitZ;
	//frustum.front = (float3::zero-frustum.pos);
	frustum.front.Normalize();
	frustum.up = float3::unitX.Cross(frustum.front).Normalized();
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = (float)M_PI / 4.0f;

	float aspect = static_cast<float>(App->GetModuleWindow()->GetWidth()) / static_cast<float>(App->GetModuleWindow()->GetHeight());
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspect);

	model = /*float3x3::identity;*/
		float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f),
			float4x4::RotateZ(DegToRad(0)),
			float3(20.0f, 20.0f, 20.0f));
	return true;
}

update_status ModuleCamera::PreUpdate()
{

	return UPDATE_CONTINUE;
}


// Called every draw update
update_status ModuleCamera::Update()
{
	float speed = 0.5f;

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
		frustum.pos += speed*frustum.up;

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
		frustum.pos -= speed * frustum.up;

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		frustum.pos -=  frustum.front.Cross(frustum.up).Normalized()* speed;

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		frustum.pos += frustum.front.Cross(frustum.up).Normalized() * speed;

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		frustum.pos[2] += speed;
		
	}

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		frustum.pos[2] -= speed;
		
	}

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		pitch += speed;
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		

		RotateXAxis(pitch);
		
	}
	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		pitch -= speed;
		if (pitch < -89.0f) {
			pitch = -89.0f;
		}

		RotateXAxis(pitch);

	
	}
	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		yaw += speed;


		RotateYAxis(yaw);


	}
	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		yaw -= speed;

		RotateYAxis(yaw);
	

	}

	if (App->GetModuleInput()->GetMouseWheel() > 0) {
		frustum.pos[2] += speed;
		App->GetModuleInput()->ResetMouseWheel();
		}
	if (App->GetModuleInput()->GetMouseWheel() < 0) {
		frustum.pos[2] -= speed;
		App->GetModuleInput()->ResetMouseWheel();
		}
	if (App->GetModuleInput()->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
		//float2 offset;
		//offset.x = App->GetModuleInput()->GetMouseCurrentPositions()[0] - App->GetModuleInput()->GetMouseLastPosition()[0];
		//offset.y = App->GetModuleInput()->GetMouseCurrentPositions()[1] - App->GetModuleInput()->GetMouseLastPosition()[1];
		//yaw += offset.x;
		//pitch += offset.y;

		//if (pitch > 89.0f)
		//	pitch = 89.0f;
		//if (pitch < -89.0f)
		//	pitch = -89.0f;


		RotateAxis();

		//RotateXAxis(pitch);
		//RotateYAxis(yaw);
		//App->GetModuleInput()->ResetMouseMotions();
	}


	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{

	return UPDATE_CONTINUE;
}

void ModuleCamera::SetFOV()
{
}

void ModuleCamera::SetAspectRatio()
{
}

void ModuleCamera::SetPlaneDistances()
{
}

void ModuleCamera::SetPosition()
{
}

float3 ModuleCamera::GenerateDirection(float yaw, float pitch)
{
	float3 direction;
	direction.x = cos(DegToRad(yaw)) * cos(DegToRad(pitch));
	direction.y = sin(DegToRad(pitch));
	direction.z = sin(DegToRad(yaw)) * cos(DegToRad(pitch));
	return direction;
}


void ModuleCamera::RotateAxis() {
	float2 offset;
	offset.x = App->GetModuleInput()->GetMouseCurrentPositions()[0] - App->GetModuleInput()->GetMouseLastPosition()[0];
	offset.y = App->GetModuleInput()->GetMouseCurrentPositions()[1] - App->GetModuleInput()->GetMouseLastPosition()[1];
	yaw += -offset.x*sensitivity;
	pitch += offset.y * sensitivity;;
	
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	float3 newFront;
	newFront.x = cosf(DegToRad(yaw)) * cosf(DegToRad(pitch));
	newFront.y = sinf(DegToRad(pitch));
	newFront.z = sinf(DegToRad(yaw)) * cosf(DegToRad(pitch));
	frustum.front = newFront;
	float3 right = frustum.front.Cross(float3::unitY).Normalized();
	frustum.up = right.Cross(frustum.front).Normalized();

}

void ModuleCamera::RotateXAxis(int angle) {




	float3x3 rotationMatrix = float3x3::RotateAxisAngle(frustum.WorldRight(),DegToRad(angle));
	frustum.front = (rotationMatrix * frustum.front).Normalized();
	frustum.up = (rotationMatrix * frustum.up).Normalized();
}

void ModuleCamera::RotateYAxis(int angle) {
	float3x3 rotationMatrix = float3x3::RotateAxisAngle(frustum.up, DegToRad(angle));
	frustum.front = (rotationMatrix * frustum.front).Normalized();
	frustum.up = (rotationMatrix * frustum.up).Normalized();

}
//void ModuleCamera::RotateZAxis(int angle) {
//	float3x3 rotMatrix = {
//		cos(angle), -sin(angle), 0,
//		sin(angle),cos(angle),   0,
//		0,             0,        1,
//	};
//	frustum.front.Normalize();
//	frustum.front = rotMatrix.MulDir(frustum.front);
//
//	frustum.up.Normalize();
//	frustum.up = rotMatrix.MulDir(frustum.up);
//
//}
//
