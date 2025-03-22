#pragma once

class Room
{
public:
    Room();
    ~Room();

    void AddCube(Vector3 size, Vector3 position, const wstring& texturePath,Vector2 tiling);
    void AddOre(Vector3 pos, int oreID);
    void Render();
    void Update();

    vector<Cube*>& GetCubes() { return roomCubes; }

private:
    vector<Cube*> roomCubes;
    OreManager* oreManager;
};