#pragma once

class ShopSlot;

class Shop : public Quad {
public:
    Shop();
    ~Shop();

    void Update();
    void Render();
    void CreateSlots();
    bool IsActive() const { return isActive; }

private:
    vector<ShopSlot*> slots;
    bool isActive = false;
};

