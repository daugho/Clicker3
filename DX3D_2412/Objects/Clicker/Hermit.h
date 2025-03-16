#pragma once
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
};
class Hermit : public Cube
{
public:
	Hermit(string modelName);
	~Hermit();

	void Render() ; 
	void Update() ;
	void ByeOre();
	void SellItem();
	void Edit();
	bool IsRayCollision(const Ray& ray, RaycastHit* hit);
	HermitType GetType() const { return type; }
	const vector<shopData>& GetShopTable() const { return shopTable; }
private:
	void LoadShopTable();
private:

	Model* model;
	BoxCollider* collider;
	bool showCollider = true;
	vector<shopData> shopTable;
	HermitType type;
};