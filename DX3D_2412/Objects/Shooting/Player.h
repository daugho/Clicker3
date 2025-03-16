#pragma once

class OreManager;
struct DropData;
class OreInventory;
class Player : public SphereCollider
{
private:
	const float GRAVITY = 9.8f;
	const float JUMP_POWER = 3.0f;

public:
	Player();
	~Player();

	void Update();
	void Render();
	void PostRender();

	void SetVelocity(const Vector3& newVelocity);
	void Mining();
	void ToggleInventory();
	//void CheckInteraction();
	Vector3 GetVelocity();
	SphereCollider* GetCollider() { return collider; }
	void ToggleLight();

private:
	void Control();

	void Jump();
	void Move();

	void SetCursor();


private:
	float moveSpeed = 5.0f;
	float rotSpeed = 1.0f;
	int playerDamage = 5;

	Vector3 velocity;

	POINT clientCenterPos;

	LightBuffer::Light* light;

	OreInventory* oreInventory;

	float miningCooldown = 1.0f;  //Ã¤±¼ Äð´Ù¿î (ÃÊ´ç 1È¸)
	float miningTimer = 0.0f;

	bool isInventoryOpen = false;
	SphereCollider* collider;
	bool isLightOn = true;
	float miningRange = 3.0f;
};