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

    void SetCursorColor(const Float4& color);
    void ResetCursorColor();

private:
    void CreateUI();

private:
    bool isInventoryOpen = false;

    Quad* cursor;
    Quad* miningEffect;
    Quad* resourcePanel;

    OreInventory* inventory;

    BlendState* blendState[2];

    Float4 originalCursorColor = Float4(1, 1, 1, 1);
};