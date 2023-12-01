#pragma once
#include "Module.h"
#include "Globals.h"
#include "Geometry\Frustum.h"
#include "Math/float4x4.h"
#include "Math/float3x4.h"

class ModuleCamera :public Module{
 public:
	ModuleCamera();
	~ModuleCamera();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	void SetFOV();
	void SetAspectRatio();
	void SetPlaneDistances();
	void SetPosition();
	void SetOrientation();

	const Frustum& GetFrustum()const  {
		return frustum;
	};
	  float4x4 GetViewMatrix()const {

		//float3 right = frustum.front.Cross(frustum.up).Normalized();
		//float4x4 camMatrix = {
		//	right.x, frustum.up.x, -(frustum.front.x), frustum.pos.x,
		//	right.y, frustum.up.y, -(frustum.front.y), frustum.pos.y,
		//	right.z, frustum.up.z, -(frustum.front.z), frustum.pos.z,
		//	0,           0,             0,                 1,
		//};

		//camMatrix.Inverse();
		//return camMatrix;

		return frustum.ViewMatrix();
	};
	 float4x4 GetProjectionMatrix()const {
		return frustum.ProjectionMatrix();
	};
	 float4x4 GetModelMatrix()const {
		return model;
	};


private:
	Frustum frustum;
	float4x4 model;
};

