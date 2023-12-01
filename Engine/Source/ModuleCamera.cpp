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
		float4x4::FromTRS(float3(0.0f, 1.0f, 0.5f),
			float4x4::RotateZ(DegToRad(90)),
			float3(1.0f, 1.0f, 1.0f));
	return true;
}

update_status ModuleCamera::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleCamera::Update()
{
	int speed = 1;

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		frustum.pos += speed*frustum.up;

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		frustum.pos -= speed * frustum.up;

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		frustum.pos -=  frustum.front.Cross(frustum.up).Normalized()* speed;

	if (App->GetModuleInput()->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		frustum.pos += frustum.front.Cross(frustum.up).Normalized() * speed;

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

void ModuleCamera::SetOrientation()
{
}
