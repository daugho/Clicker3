#pragma once

class ClickerMapManager : public Singleton<ClickerMapManager>
{
    friend class Singleton;
public:
    ClickerMapManager();
    ~ClickerMapManager();

    void Update();
    void Render();
    void CreateCube(Cube*& cube, Vector3 size, Vector3 position, const wstring& texturePath);
    void CreateRoom1();
    void CreateRoom2();
    bool CheckCollision(Vector3 nextPos);

private:
    Player* player;
    OreManager* oreManager;
    //OreInventory* inventory;
    vector<Cube*> roomCubes;
    Cube* floor;
    vector<BoxCollider*> wallColliders;
    vector<BoxCollider*> floorColliders;
    bool isFreeView = false;
    Hermit* hermit1;
};