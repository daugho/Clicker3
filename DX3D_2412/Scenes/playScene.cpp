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
    // 10x10 바닥 생성
    floorManager = new FloorManager(Vector3(0, 0, 0), { 10, 10 }, nullptr);

    // ObjectManager 생성
    objectManager = new ObjectManager(floorManager);

    // 중앙에 Ore0 배치
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
