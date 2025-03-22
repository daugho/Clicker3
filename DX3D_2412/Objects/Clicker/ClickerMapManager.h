#pragma once
class Room;
class ClickerMapManager : public Singleton<ClickerMapManager>
{
    friend class Singleton;
public:
    ClickerMapManager();
    ~ClickerMapManager();

    void Update();
    void Render();
    void CreateRoom1();
    void CreateRoom2();
    void CheckCollision();


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
    list<Block*> blocks;
    Room* room1;
};