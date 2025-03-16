#include "Framework.h"
#include "playScene.h"


PlayScene::PlayScene()
{
	Init();
}

PlayScene::~PlayScene()
{
    delete floorManager;
    delete objectManager;
}

void PlayScene::Init()
{
    // 10x10 �ٴ� ����
    floorManager = new FloorManager(Vector3(0, 0, 0), { 10, 10 }, nullptr);

    // ObjectManager ����
    objectManager = new ObjectManager(floorManager);

    // �߾ӿ� Ore0 ��ġ
    POINT centerTile = { 5, 5 };
    objectManager->CreateOre(centerTile, { 10, 10 }, 0);
}

void PlayScene::Update()
{
    floorManager->Update();
    objectManager->Update();

}

void PlayScene::Render()
{
    floorManager->Render();
    objectManager->Render();
}

void PlayScene::PreRender()
{
}

void PlayScene::PostRender()
{
}

void PlayScene::GUIRender()
{
}

void PlayScene::Edit()
{
	floorManager->Edit();
	objectManager->Edit();
}
