#pragma once
class ObjectManater;

enum FloorEditType
{
	FWall, FHermit, FOre, FItem, None
};
struct WallData
{
	Vector3 position;  // 벽 위치
	FloorEditType type;  // 벽 타입
	Vector3 size;  // 벽 크기
};
class FloorManager : public Cube
{
	friend class ObjectManager;


public:
	FloorManager(Vector3 position, POINT size, CubeMapEditor* editor);
	~FloorManager();

	void Render();
	void Edit();
	void Update();
	void UpdateMesh();
	void UpdateCeilingMesh();
	void SetEdit();
	void SetSelectTile();
	void CreateWall(Vector3 size, int x, int y);
	void InitializerFloor();
	bool IsOccupied(int x, int y);
	void SetOccupied(int x, int y, bool state);

	int GetWallCount() { return (int)walls.size(); }
	WallData GetWallData(int index) { return walls[index]; }
	void AddWall(WallData wall) { walls.push_back(wall); }

	POINT GetMapSize() { return floormapSize; }
	POINT GetSelectTile() { return editorRef->GetSelectTile(); }

	FloorEditType GetFloorType(int x, int y) const;
	void SetFloorType(int x, int y, FloorEditType type);

	// ? 벽 크기 관리 함수
	Vector3 GetWallSize(int x, int y);
	void SetWallSize(int x, int y, Vector3 size);

	// ? 광물 ID 관리 함수
	int GetOreID(int x, int y);
	void SetOreID(int x, int y, int id);


private:
	CubeMapEditor* editorRef;
	ObjectManager* objectManager;
	POINT floormapTiling = { 1,1 };
	POINT floormapSize ;
	map<pair<int, int>, Vector3> wallSizes;
	POINT cilingTiling = { 1,1 };
	POINT cilingSize;
	POINT floorselectTile;
	POINT wallTiling = { 1,1 };
	Vector3 wallSize = { 1,1,1 };

	FloorEditType floorEditType;

	FloatValueBuffer* floortileBuffer;

	list<GameObject*> floorsobjects;
	map<int, GameObject*> floorobjectData;

	vector<vector<FloorEditType>> floortypes;
	vector<vector<bool>> floorOccupied;

	Vector3 floorPos;

	vector<GameObject*> ceilingCubes;
	bool showCeiling = false;

	int oreID = 0;
	vector<WallData> walls;

	map<pair<int, int>, int> oreIDs;
};