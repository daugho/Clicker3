#include "Framework.h"

ClickerMapManager::ClickerMapManager()
{

	player = new Player();
	player->SetLocalPosition(-3, 2, 1);
	CAM->SetTarget(player);
	CAM->TargetOptionLoad("FPSMode");

	hermit1 = new Hermit("machine", HermitType::Merchant1);
	hermit1->SetLocalPosition(Vector3( 2, 1, 2));
	hermit1->SetLocalScale(Vector3( 2, 2, 2));

	room1 = new Room();
	CreateRoom1();
}

ClickerMapManager::~ClickerMapManager()
{
	delete player;
	delete hermit1;
	delete room1;
}

void ClickerMapManager::Update()
{
	player->Update();
	hermit1->Update();
	room1->Update();
	CheckCollision();
	//if (KEY->Down(VK_F2))
	//{
	//	isFreeView = true;
	//	CAM->SetTarget(nullptr);
	//	ShowCursor(true);
	//}
	//
	//if (KEY->Down(VK_F3))
	//{
	//	isFreeView = false;
	//	CAM->SetTarget(player);
	//	CAM->TargetOptionLoad("FPSMode");
	//	ShowCursor(false);
	//}
	//if (isFreeView)
	//{
	//	return;
	//}
	
	
}

void ClickerMapManager::Render()
{
	player->Render();
	hermit1->Render();
	room1->Render();
}

void ClickerMapManager::CreateRoom1()
{
	wstring baseTexture = L"Resources/Textures/Block/T_Ore9_Color.png";
	room1->AddCube(Vector3(11, 1, 31), Vector3(0, -0.5, 0), baseTexture,Vector2(2,15));
	room1->AddCube(Vector3(1, 6, 31), Vector3(5, 3, 0), baseTexture, Vector2(1,1));  // 오른쪽 벽
	room1->AddCube(Vector3(1, 6, 31), Vector3(-5, 3, 0), baseTexture, Vector2(1, 1)); // 왼쪽 벽
	room1->AddCube(Vector3(11, 6, 1), Vector3(0, 3, -15), baseTexture, Vector2(1, 1)); // 뒷벽
	room1->AddCube(Vector3(11, 6, 1), Vector3(0, 3, 15), baseTexture, Vector2(1, 1));  // 앞벽
	room1->AddCube(Vector3(11, 1, 31), Vector3(0, 6, 0), baseTexture, Vector2(1, 1));  // 천장

	// ?? Room1에 광물 추가
	room1->AddOre({2,0.5,4}, 0);
	//room1->AddOre({ 2, 2 }, { 10, 10 }, 1);
}

void ClickerMapManager::CreateRoom2()
{

}

void ClickerMapManager::CheckCollision()
{
	RaycastHit hit;

	if (hermit1->GetCollider()->PushSphere(player, &hit))
	{
		player->SetLocalPosition(player->GetGlobalPosition() + (hit.point * hit.distance));
	}

	for (Cube* cube : room1->GetCubes())
	{
		if (cube->GetCollider()->PushSphere(player,&hit))
		{
			player->SetLocalPosition(player->GetGlobalPosition() + (hit.point * hit.distance));
		}
	}
}
