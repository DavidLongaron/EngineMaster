#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"


GameObject::GameObject() {}

GameObject::GameObject(GameObject&& other)
{
	this->children = std::move(other.children);
	this->name = std::move(other.name);
	this->components = std::move(other.components);
	this->parent = std::move(other.parent);
}

Component* GameObject::CreateComponent(ComponentType type)
{
	switch (type) {
	case TRANSFORM:
		ComponentTransform*  newComp = new ComponentTransform();
		components.push_back(newComp);
		return newComp;
	}
	



}

void GameObject::AddChild(GameObject* obj)
{
	children.push_back(obj);
}
