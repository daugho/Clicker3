#include "Framework.h"

ClickerMapManager::ClickerMapManager()
{

	player = new Player();
	player->SetLocalPosition(2, 3, -5);
	CAM->SetTarget(player);
	CAM->TargetOptionLoad("FPSMode");
	//OreManager::Get()->CreatOre({ 5, 5 }, { 10, 10 }, 0);
	CreateRoom1();
	CreateRoom2();
	oreManager = OreManager::Get();
	oreManager->CreatOre({ 5, 5 }, { 10, 10 }, 0);

	hermit1 = new Hermit("machine", HermitType::Merchant1);
	hermit1->SetLocalPosition(-4, 0.5, 2);
	hermit1->SetLocalRotation(0, 0, 0);
	floor = new Cube(Vector3(10,1,30),Vector2(2,6));
	floor->GetMaterial()->SetDiffuseMap(L"Resources/Textures/Block/T_Ore9_Color.png");
	floor->GetMaterial()->SetSpecularMap(L"Resources/Textures/Block/T_Ore9_Mask.png");
	floor->GetMaterial()->SetNormalMap(L"Resources/Textures/Block/T_Ore9_Normal.png");
}

ClickerMapManager::~ClickerMapManager()
{
	OreManager::Delete();
	delete player;
	for (Cube* cube : roomCubes)
		delete cube;
	for (BoxCollider* collider : wallColliders)
		delete collider;
	for (BoxCollider* collider : floorColliders)
		delete collider;
}

void ClickerMapManager::Update()
{
	if (KEY->Down(VK_F2))
	{
		isFreeView = true;
		CAM->SetTarget(nullptr);
		ShowCursor(true);
	}

	if (KEY->Down(VK_F3))
	{
		isFreeView = false;
		CAM->SetTarget(player);
		CAM->TargetOptionLoad("FPSMode");
		ShowCursor(false);
	}
	if (isFreeView)
	{
		return;
	}
	hermit1->Update();
	oreManager->Update();
	for (BoxCollider* collider : wallColliders)
		collider->Update();
	for (BoxCollider* collider : floorColliders)
		collider->Update();
	for (Cube* cube : roomCubes)
		cube->Update();

	Vector3 nextPos = player->GetLocalPosition() + player->GetVelocity();

	if (CheckCollision(nextPos))
	{
		player->Update();
		//player->SetVelocity(Vector3(0, player->GetVelocity().y, 0));  // �̵��� ����
		player->SetLocalPosition(nextPos);  // ���� ��ġ�� �ǵ���
	}
	else
	{
		player->Update();
	}
}

void ClickerMapManager::Render()
{
	floor->Render();
	hermit1->Render();
	player->Render();
	oreManager->Render();
	for (Cube* cube : roomCubes)
		cube->Render();
	for (BoxCollider* collider : floorColliders)
		collider->Render();
	for (BoxCollider* collider : wallColliders)
		collider->Render();
}

void ClickerMapManager::CreateCube(Cube*& cube, Vector3 size, Vector3 position, const wstring& texturePath)
{
	cube = new Cube(size);
	cube->SetLocalPosition(position);
	cube->GetMaterial()->SetDiffuseMap(texturePath);
	cube->GetMaterial()->SetNormalMap(texturePath.substr(0, texturePath.find(L"_Color")) + L"_Normal.png");
	cube->GetMaterial()->SetSpecularMap(texturePath.substr(0, texturePath.find(L"_Color")) + L"_Mask.png");
	roomCubes.push_back(cube);

	BoxCollider* collider = new BoxCollider(size);
	collider->SetParent(cube);
	collider->SetLocalPosition(0,0,0);
}

void ClickerMapManager::CreateRoom1()
{
	wstring baseTexture = L"Resources/Textures/Block/T_Ore9_Color.png";

	Cube* tempCube = nullptr;
	// �ٴ� ���� (isFloor = true)

	// �� ���� (isFloor = false)
	CreateCube(tempCube, Vector3(1, 6, 30), Vector3(5, 3, 0), baseTexture);  // ������ ��
	CreateCube(tempCube, Vector3(1, 6, 30), Vector3(-5, 3, 0), baseTexture); // ���� ��
	CreateCube(tempCube, Vector3(10, 6, 1), Vector3(0, 3, -15), baseTexture); // �޺�
	CreateCube(tempCube, Vector3(10, 6, 1), Vector3(0, 3, 15), baseTexture);  // �պ�
	CreateCube(tempCube, Vector3(10, 1, 30), Vector3(0, 6, 0), baseTexture);  // õ��

}

void ClickerMapManager::CreateRoom2()
{
	//wstring baseTexture = L"Resources/Textures/Landscape/Dirt2.png";
	//
	//Cube* tempCube = nullptr;
	//// �ٴ� ���� (isFloor = true)
	//CreateCube(tempCube, Vector3(10, 1, 10), Vector3(10, 10, 10), baseTexture, true);
	//
	//// �� ���� (isFloor = false)
	////CreateCube(tempCube, Vector3(10, 6, 1), Vector3(0, 3, -5), baseTexture, false);
	////CreateCube(tempCube, Vector3(1, 6, 10), Vector3(-5, 3, 0), baseTexture, false);
	////CreateCube(tempCube, Vector3(1, 6, 10), Vector3(5, 3, 0), baseTexture, false);
	////CreateCube(tempCube, Vector3(10, 6, 1), Vector3(0, 3, 5), baseTexture, false);
	////CreateCube(tempCube, Vector3(10, 1, 10), Vector3(0, 6, 0), baseTexture, false); // õ��
	//hermit1 = new Hermit("machine");
	//hermit1->SetLocalPosition(15, 0, 15);
}

bool ClickerMapManager::CheckCollision(Vector3 nextPos)
{
	Collider* playerCollider = player->GetCollider();
	playerCollider->SetLocalPosition(nextPos);

	// ������ �浹�� �˻� (�ٴ� ����)
	for (BoxCollider* collider : wallColliders)
	{
		if (playerCollider->IsCollision(collider))
		{
			return true;  // �浹 �߻� (�̵� �Ұ�)
		}
	}

	return false;  // �浹�� ������ �̵� ����
}
//if (colliders[0]->IsCollision(colliders[1]))
//{
//	colliders[0]->SetColor(1, 0, 0);
//	colliders[1]->SetColor(1, 0, 0);
//}
//else
//{
//	colliders[0]->SetColor(0, 1, 0);
//	colliders[1]->SetColor(0, 1, 0);
//}