#include "ModuleScene.h"
#include "GameObject.h"
#include "Component.h"



ModuleScene::ModuleScene()
{
	/*root = &(CreateGameObject());*/
	root = new GameObject();
	root->CreateComponent(TRANSFORM);
}

ModuleScene::~ModuleScene()
{
}




GameObject ModuleScene::CreateGameObject()
{
	 GameObject test;
	test.CreateComponent(TRANSFORM);
	return test;
}





bool ModuleScene::Init()
{

	return true;
}

update_status ModuleScene::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleScene::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate()
{

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	delete root;
	return true;
}
