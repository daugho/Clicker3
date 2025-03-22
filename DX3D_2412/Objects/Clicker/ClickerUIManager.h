#pragma once
class ClickerUIManager : public Singleton<ClickerUIManager>
{
    friend class Singleton;
public:
    ClickerUIManager();
    ~ClickerUIManager();

    void Update();
    void Render();
    void Edit();
    void ToggleInventory();
    //void ShowMiningEffect();
    OreInventory* GetInventory() { return inventory; }
    bool IsInventoryOpen() const { return isInventoryOpen;}
    bool IsShopOpen() const { return isShopOpen;}

    void SetCursorColor(const Float4& color);
    void ResetCursorColor();

private:
    void CreateUI();
    void HandleUIToggle();

private:
    bool isInventoryOpen = false;
    bool isShopOpen = false;

    Quad* cursor;
    Quad* miningEffect;
    Quad* resourcePanel;

    OreInventory* inventory;
    Shop* shopOpen;
    BlendState* blendState[2];

    Float4 originalCursorColor = Float4(1, 1, 1, 1);
};