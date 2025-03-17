#include "Framework.h"

Shop::Shop() : Quad(L"Resources/Textures/UI/Shop.png") {
    localPosition = CENTER;
    UpdateWorld();
    CreateSlots();
}

Shop::~Shop()
{
    for (ShopSlot* slot : slots) {
        delete slot;
    }
}

void Shop::Update()
{
}

void Shop::Render()
{
    if (!isActive) return;
    Quad::Render();
    for (ShopSlot* slot : slots) {
        slot->Render();
    }
}

void Shop::CreateSlots() {
    float interval = 10.0f;
    int numSlots = 6;
    for (int i = 0; i < numSlots; i++) {
        ShopSlot* slot = new ShopSlot();
        float xOffset = (slot->Size().x + interval) * (i % 3);
        float yOffset = (slot->Size().y + interval) * -(i / 3);

        Vector3 pos = localPosition + Vector3(xOffset, yOffset, 0);
        slot->SetLocalPosition(pos);
        slot->SetParent(this);
        slot->UpdateWorld();

        slots.push_back(slot);
    }
}
