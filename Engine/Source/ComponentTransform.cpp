#include "ComponentTransform.h"

ComponentTransform::ComponentTransform()
{
	position = { 0,0,0 };
	scale = { 1,1,1 };
	rotation = Quat::identity;
}

void ComponentTransform::SetPosition(float3 newPos)
{
	position = newPos;
}

void ComponentTransform::SetScale(float3 newScale)
{
	scale = newScale;
}

void ComponentTransform::SetRotation(Quat newRot)
{
	rotation = newRot;
}
