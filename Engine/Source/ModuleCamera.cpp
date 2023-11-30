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


void ModuleCamera::SetCameraMatrix()
{

	float3 right = frustum.front.Cross(frustum.up).Normalized();
	float4x4 camMatrix = {
		right.x, frustum.up.x, -(frustum.front.x), frustum.pos.x,
		right.y, frustum.up.y, -(frustum.front.y), frustum.pos.y,
		right.z, frustum.up.z, -(frustum.front.z), frustum.pos.z,
		0,           0,             0,                 1,
	};

	cameraMatrix = camMatrix;
	view = camMatrix;
	view.Inverse();

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

	float aspect = static_cast<float>(App->GetWindow()->width) / static_cast<float>(App->GetWindow()->height);
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspect);
	proj = frustum.ProjectionMatrix();
	SetCameraMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*view.v);

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

	if (App->GetInput()->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->GetWindow()->camera.y += speed;

	if (App->GetInput()->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->renderer->camera.y -= speed;

	if (App->GetInput()->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->renderer->camera.x += speed;

	if (App->GetInput()->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->renderer->camera.x -= speed;

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

float4x4 ModuleCamera::GetProjectionMatrix()
{
	return float4x4();
}

float4x4 ModuleCamera::GetViewMatrix()
{
	return float4x4();
}
