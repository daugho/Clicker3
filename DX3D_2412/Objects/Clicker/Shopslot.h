#pragma once
#include "ShopSlot.h"

struct ShopItemData {
    int id;
    string name;
    wstring texturePath;
    int price;
};
class ShopSlot : public Button {
public:
    ShopSlot();
    ~ShopSlot();

    void Update();
    void Render();
    void SetItem(const ShopItemData& item);
    void OnClick();

private:
    ShopItemData item;
    bool occupied = false;
};
