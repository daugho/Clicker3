#pragma once
class FloorManager;
class ObjectManager;
class OreManager;

class PlayScene : public Scene
{
public:
    PlayScene();
    ~PlayScene();

    void Update() override;
    void Render() override;
    void PreRender() override;
    void PostRender() override;
    void GUIRender() override;
    void Edit();

private:
    void Init();

    FloorManager* floorManager;
    ObjectManager* objectManager;
    OreManager* oreManager;
	Player* player;

};