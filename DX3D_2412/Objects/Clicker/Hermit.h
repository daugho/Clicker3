#pragma once
#include "Hermit.h"

class CapsuleCollider;

	enum class HermitType {
		Merchant1,
		Merchant2,
		Merchant3,
		Merchant4
	};
	struct shopData
	{
		int id;
		string name;
		wstring descrip;
		int price;
		wstring icon;
	};
class Hermit : public Cube
{
public:
	Hermit(string modelName, HermitType type);
	~Hermit();

	void Render() ; 
	void Update() ;
	void Shop1Slot();

	bool IsRayCollision(const Ray& ray, RaycastHit* hit);

	const vector<shopData>& GetShopTable() const { return shopTable; }
	HermitType GetType() const { return type; }

private:
	void LoadShopTable();
	void LoadShopUI();
	void ByeOre();
	void SellItem();
	void Edit();
private:

	Model* model;
	BoxCollider* collider;
	bool showCollider = true;
	vector<shopData> shopTable;
	HermitType type;

	Quad* shopUI = nullptr;
	bool isShopOpen = false;
};