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
	float3 GenerateDirection(float yaw, float pitch);

	inline const Frustum& GetFrustum()const  {
		return frustum;
	};
	inline float4x4 GetViewMatrix()const {

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
	  inline float4x4 GetProjectionMatrix()const {
		return frustum.ProjectionMatrix();
	};
	 inline float4x4 GetModelMatrix()const {
		return model;
	};
	 inline float GetYaw()const {
		 return yaw;
	 }
	 inline  float GetPitch()const {
		 return pitch;
	 }
	 void RotateXAxis(int angle);
	 void RotateYAxis(int angle);
	 void RotateZAxis(int angle);
	 void RotateAxis();
	 inline float3& getViewSize() {
		 return viewSize;
	 }
	 float3 viewSize = float3(10.0f, 10.0f, 10.0f);
	 float3  modelRot = float3(0.0f, 0.0f, 0.0f);
private:
	Frustum frustum;
	float4x4 model;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float sensitivity = 0.5;
	
};


