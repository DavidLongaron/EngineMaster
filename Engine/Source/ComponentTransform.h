#pragma once
#include "Component.h"
#include "Math/float3.h"
#include "Math/Quat.h"

class ComponentTransform :public Component
{
public:
	ComponentTransform();
	~ComponentTransform();
	void SetPosition( float3 newPos);
	void SetScale(float3 newScale);
	void SetRotation(Quat newRot);

private:
	float3 position;
	float3 scale;
	Quat rotation;
};

