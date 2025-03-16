#include "Framework.h"

ObjectManager::ObjectManager(FloorManager* floorManager)
{
	this->floorManager = floorManager;
}

ObjectManager::~ObjectManager()
{
	for (GameObject* wall : objects)
		delete wall;
	for (Hermit* hermit : hermits)
		delete hermit;
	for (BoxCollider* col : colliders)
		delete col;
	for (CapsuleCollider* cap : capcolliders)
		delete cap;
}

void ObjectManager::CreateHermit(POINT selectTile, POINT mapSize)
{
	int x = selectTile.x;
	int y = selectTile.y;


	if (floorManager->IsOccupied(x, y)) {return;}

	Vector3 startPos = Vector3(mapSize.x * -0.5f, 0.0f, mapSize.y * -0.5f);
	Vector3 pos = startPos + Vector3(selectTile.x + 0.5f, 1.0f, selectTile.y + 0.5f);

	Hermit* hermit = new Hermit("machine");
	hermit->SetLocalPosition(pos);
	hermit->Update();

	hermits.push_back(hermit);
	hermitCount++;

	floorManager->SetOccupied(x, y, true);
	hermits.push_back(hermit);
	floorManager->SetFloorType(x, y, FHermit);
}

void ObjectManager::CreateOre(POINT selectTile, POINT mapSize, int oreID)
{
	int x = selectTile.x;
	int y = selectTile.y;


	if (floorManager->IsOccupied(x, y)) {return;}

	OreManager::Get()->CreatOre(selectTile, mapSize, oreID);


	floorManager->SetFloorType(x, y, FOre);
	floorManager->SetOreID(x, y, oreID);
}

void ObjectManager::DeleteObject(int index)
{
}

void ObjectManager::Render()
{
	for (GameObject* obj : objects)
	{
		obj->Render();
	}
	for (Hermit* hermit : hermits)
		hermit->Render();
	for (BoxCollider* col : colliders)
		col->Render();
	for (CapsuleCollider* cap : capcolliders)
		cap->Render();

}

void ObjectManager::Edit()
{

	for (Hermit* hermit : hermits)
		hermit->Edit();
	for (BoxCollider* col : colliders)
		col->Edit();
	for (CapsuleCollider* cap : capcolliders)
		cap->Edit();
}

vector<BoxCollider*> ObjectManager::GetCollisionObjects(float distance)
{
	Ray ray = CAM->ScreenPointToRay(CENTER);

	vector<BoxCollider*> hitCoins;
	RaycastHit hit;

	for (BoxCollider* collider : colliders)
	{
		float dist = Vector3::Distance(collider->GetGlobalPosition(), CAM->GetGlobalPosition());

		if (dist > distance)
			continue;

		if (collider->IsRayCollision(ray, &hit))
		{
			hitCoins.push_back(collider);
		}
	}

	return hitCoins;
}
