#include "ModuleCamera.h"
#include "GL/glew.h"
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
	//frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	//frustum.SetViewPlaneDistances(0.1f, 200.0f);
	//frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, 1.3f);
	//frustum.SetPos(float3(0.0f, 1.0f, -2.0f));
	//frustum.front=float3::unitZ;
	//frustum.up= float3::unitY;
	//float4x4 projectionGL = frustum.ProjectionMatrix().Transposed(); // < --Important to transpose!
	//	//Send the frustum projection matrix to OpenGL
	//	// direct mode would be:
	//glMatrixMode(GL_PROJECTION);
	//glLoadMatrixf(*projectionGL.v);
	return true;
}

update_status ModuleCamera::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleCamera::Update()
{

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
