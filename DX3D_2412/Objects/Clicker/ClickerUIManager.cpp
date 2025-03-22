#include "Framework.h"

ClickerUIManager::ClickerUIManager()
{
    CreateUI();

    inventory = new OreInventory();
    inventory->SetActive(false);
    shopOpen = new Shop();
    shopOpen->SetActive(false);
}

ClickerUIManager::~ClickerUIManager()
{
    delete cursor;
    delete inventory;
}

void ClickerUIManager::Update()
{
    HandleUIToggle();

    if (isInventoryOpen)
        inventory->Update();

    if (isShopOpen)
        shopOpen->Update();
}

void ClickerUIManager::Render()
{
    //Environment::Get()->SetAlphaBlend(true);

    cursor->Render();
    inventory->Render();
    shopOpen->Render();
}

void ClickerUIManager::Edit()
{
    inventory->Edit();
}

void ClickerUIManager::ToggleInventory()
{
   // isInventoryOpen = !isInventoryOpen;
   // inventory->SetActive(isInventoryOpen);
   //
   // if (isInventoryOpen)
   // {
   //     ShowCursor(true); // ? ���콺 Ŀ�� Ȱ��ȭ
   //     //CAM->IsActive(true); // ? ī�޶� ������ ���
   // }
   // else
   // {
   //     ShowCursor(false); // ? ���콺 Ŀ�� ��Ȱ��ȭ
   //    // CAM->IsActive(false); // ? ī�޶� ������ ����
   // }
}

void ClickerUIManager::SetCursorColor(const Float4& color)
{
    cursor->GetMaterial()->GetData()->diffuse = color;
}

void ClickerUIManager::ResetCursorColor()
{
    cursor->GetMaterial()->GetData()->diffuse = originalCursorColor;
}

void ClickerUIManager::CreateUI()
{
    cursor = new Quad(L"Resources/Textures/UI/cursor.png");
    cursor->SetLocalPosition(CENTER);
    cursor->UpdateWorld();    
}

void ClickerUIManager::HandleUIToggle()
{
    if (KEY->Down('I'))
    {
        isInventoryOpen = !isInventoryOpen;
        ShowCursor(isInventoryOpen);
        inventory->SetActive(isInventoryOpen);
    }

    if (KEY->Down('B'))
    {
        isShopOpen = !isShopOpen;
        ShowCursor(isShopOpen);
        shopOpen->SetActive(isShopOpen);
    }
}
