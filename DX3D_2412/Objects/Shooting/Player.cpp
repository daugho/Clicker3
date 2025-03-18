#include "Framework.h"

Player::Player()
{
	tag = "Player";

	localPosition.y = radius;

	clientCenterPos = { SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1 };
	ClientToScreen(hWnd, &clientCenterPos);
	SetCursorPos(clientCenterPos.x, clientCenterPos.y);
	ShowCursor(false);

	//CAM->SetLocalPosition(0, 0, 0);
	//CAM->SetLocalRotation(0, 0, 0);
	//CAM->SetParent(this);

	light = Environment::Get()->GetLight(0);
	light->type = 2;
	light->color = { 1, 1, 1, 1 };
	light->isActive = 0;

	oreInventory = new OreInventory();
	collider = new SphereCollider(1.0f); // ������ 1.0 ����
	collider->SetParent(this);
}

Player::~Player()
{
	delete collider;
}

void Player::Update()
{
	if (ClickerUIManager::Get()->IsInventoryOpen())
		return;

	collider->SetLocalPosition(GetLocalPosition());
	collider->UpdateWorld();

	light->position = localPosition;
	light->direction = CAM->GetForward();
	ForceOpenShopUI();
	SetCursor();
	Control();
	ToggleLight();
	Jump();
	Move();

	UpdateWorld();
	Mining();
	ToggleInventory();
}

void Player::Render()
{
	//Collider::Render();

}

void Player::PostRender()
{
}

void Player::SetVelocity(const Vector3& newVelocity)
{
	velocity = newVelocity;
}

void Player::Mining()
{
	miningTimer += DELTA;

	if (miningTimer < miningCooldown)
		return;

	Ray ray = CAM->ScreenPointToRay(CENTER);
	RaycastHit hit;

	Ore* closestOre = OreManager::Get()->GetClosestOre(ray, &hit);
	float distance = FLT_MAX;

	if (closestOre)
	{
		distance = Vector3::Distance(hit.point, CAM->GetGlobalPosition());

		if (distance <= miningRange)
		{
			ClickerUIManager::Get()->SetCursorColor(Float4(0, 1, 0, 1));
		}
		else
		{
			ClickerUIManager::Get()->ResetCursorColor();
		}

		if (KEY->Press(VK_LBUTTON) && distance <= miningRange)
		{
			closestOre->TakeDamage(playerDamage);
			miningTimer = 0.0f;
		}
	}
	else
	{
		ClickerUIManager::Get()->ResetCursorColor();
	}
}
void Player::ToggleInventory()
{
	if (KEY->Down('I'))
	{
		isInventoryOpen = !isInventoryOpen;
		oreInventory->SetActive(isInventoryOpen);
	}
}

void Player::ForceOpenShopUI()
{
	if (KEY->Down('B'))
	{
		isShopOpen = !isShopOpen;
		shopOpne->SetActive(isShopOpen);
	}
}


Vector3 Player::GetVelocity()
{
	return velocity * moveSpeed * DELTA;
}

void Player::ToggleLight()
{
	if (KEY->Down('F'))
	{
		isLightOn = !isLightOn;

		if (isLightOn)
		{
			light->color = { 1, 1, 1, 1 };
			light->isActive = 1;
		}
		else
		{
			light->color = { 0, 0, 0, 0 };
			light->isActive = 0;
		}
	}
}

void Player::OpenMerchant1Shop()
{

}

void Player::Control()
{
	Vector3 dir;

	if (KEY->Press('W'))
		dir += GetForward();
	if (KEY->Press('S'))
		dir += GetBack();
	if (KEY->Press('A'))
		dir += GetLeft();
	if (KEY->Press('D'))
		dir += GetRight();

	dir.Normalize();

	velocity.x = dir.x;
	velocity.z = dir.z;

	Vector3 delta = mousePos - CENTER;

	Rotate(Vector3::Up(), delta.x * rotSpeed * DELTA);
	CAM->Rotate(Vector3::Left(), delta.y * rotSpeed * DELTA);

	if (KEY->Down(VK_SPACE))
	{
		velocity.y = JUMP_POWER;
	}
}



void Player::Jump()
{
	velocity.y -= GRAVITY * DELTA;

	float bottomHeight = BlockManager::Get()->GetHeight(localPosition);

	if (velocity.y < 0 && localPosition.y - radius <= bottomHeight)
	{
		velocity.y = 0.0f;
	}
}

void Player::Move()
{
	if (UIManager::Get()->IsPopup())
		return;

	Translate(velocity * moveSpeed * DELTA);
}

void Player::SetCursor()
{
	//if(UIManager::Get()->)

	SetCursorPos(clientCenterPos.x, clientCenterPos.y);
}

