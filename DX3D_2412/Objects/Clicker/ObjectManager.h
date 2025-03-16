#pragma once

class Ore;

class ObjectManager :public Cube
{
public:
	ObjectManager(FloorManager* floorManager);
	~ObjectManager();

	void CreateHermit(POINT selectTile, POINT mapSize);
	void CreateOre(POINT selectTile, POINT mapSize, int oreID);
	void DeleteObject(int index);

	void Render();
	void Edit();
	const list<BoxCollider*>& GetAllColliders() { return colliders; }
	vector<BoxCollider*> GetCollisionObjects(float distance);

private:
	int hermitCount = 0;

	FloorManager* floorManager;

	list<GameObject*> objects;
	map<int, GameObject*> objectData;

	list<Hermit*> hermits;
	map<int, Hermit*> hermitdata;

	list<BoxCollider*> colliders;
	map<int, BoxCollider*> colliderdata;

	list<CapsuleCollider*> capcolliders;
	map<int, CapsuleCollider*> capcolliderdata;
};