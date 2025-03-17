#pragma once

class ShopSlot;

class Shop : public Quad {
public:
    Shop();
    ~Shop();

    void Update();
    void Render();
    void CreateSlots();
    void SetActive(bool active) { isActive = active; }
    bool IsActive() const { return isActive; }

private:
    vector<ShopSlot*> slots;
    bool isActive = false;
};

