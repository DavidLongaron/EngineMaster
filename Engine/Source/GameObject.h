#pragma once
#include <string>
#include <vector>

enum ComponentType;
class Component;
class Mesh;

class GameObject
{
public:
	GameObject();
	void Update();
	/*GameObject(GameObject&& other);*/
	Component* CreateComponent(ComponentType type);
	void AddChild(GameObject* obj);
	Mesh* mesh;
	std::vector<GameObject*> children;
	unsigned int text;
private:
	std::string name;
	std::vector<Component*> components;
	GameObject* parent;
	

	
};

