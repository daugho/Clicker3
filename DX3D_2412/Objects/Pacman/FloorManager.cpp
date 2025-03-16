#include "Framework.h"

FloorManager::FloorManager(Vector3 position, POINT size, CubeMapEditor* editor) : floorPos(position), floormapSize(size), editorRef(editor)
{
	InitializerFloor();

	objectManager = new ObjectManager(this);
	floortileBuffer = new FloatValueBuffer();

	material->SetShader(L"Custom/MapEditor.hlsl");

	SetLocalScale(1, 1, 1);
	SetLocalPosition(position);

	collider = new BoxCollider(Vector3(floormapSize.x, 1, floormapSize.y));
	collider->SetParent(this);
	collider->SetLocalPosition(Vector3(0, 0, 0));
}

FloorManager::~FloorManager()
{
	delete floortileBuffer;
	delete collider;
	delete objectManager;

	for (GameObject* object : floorsobjects)
		delete object;
	for (GameObject* ceiling : ceilingCubes)
		delete ceiling;
}

void FloorManager::Render()
{
	floortileBuffer->SetPS(10);
	objectManager->Render();
	collider->Render();

	Cube::Render();

	for (GameObject* obj : floorsobjects)
		obj->Render();

	//Environment::Get()->SetAdditive();
	//Environment::Get()->SetAlphaBlend(false);

	if (showCeiling)
	{
		for (GameObject* cube : ceilingCubes)
			cube->Render();
	}
}

void FloorManager::Edit()
{
	ImGui::Begin("Floor Manager Setting");
	ImGui::Text("Allocated Matrix Size: X: %d, Z: %d", floorOccupied);
	ImGui::Text("FloorMapEditor");
	int posSize[3] = { (int)floorPos.x, (int)floorPos.y, (int)floorPos.z };
	ImGui::DragInt2("FloorPos", (int*)&posSize);
	ImGui::DragInt2("SelectTile", (int*)&floorselectTile);

	if (ImGui::DragInt2("MapSize", (int*)&floormapSize), 1, 1, 100)
	{
		//size = Vector3(floormapSize.x, 1.0f, floormapSize.y);
		UpdateMesh();
	}

	if (ImGui::DragInt2("Tiling", (int*)&floormapTiling), 1, 1, 100)
	{
		tiling = floormapTiling;
		UpdateMesh();
	}

	material->Edit();

	const char* list[] = {"Wall", "Hermit", "Ore", "Item" };
	if (ImGui::Combo("Type", (int*)&floorEditType, list, 4))
	{
	}
	int wallSizeInt[3] = { (int)wallSize.x, (int)wallSize.y, (int)wallSize.z };
		if (floorEditType == FWall)
		{
			ImGui::DragInt3("Wall Size", wallSizeInt, 1, 1, 10);
			{
				wallSize = Vector3((float)wallSizeInt[0], (float)wallSizeInt[1], (float)wallSizeInt[2]);
			}
		}
		if (floorEditType == FOre)
		{
			const char* orelist[] = { "Ore0", "Ore1", "Ore2", "Ore3", "Ore4", "Ore5" };
			ImGui::Combo("OreType", &oreID, orelist, 6);
		}

		
	ImGui::Text("CeilingEditor");

		ImGui::Checkbox("Show Ceiling", &showCeiling);

		if (ImGui::DragInt2("ceilingSize", (int*)&cilingSize), 1, 1, 100)
		{
			if (showCeiling) UpdateCeilingMesh();
		}

		if (ImGui::DragInt2("ceilingTiling", (int*)&cilingTiling), 1, 1, 100)
		{
			tiling = cilingTiling;
			if (showCeiling) UpdateCeilingMesh();
		}
		ImGui::End();
		for (GameObject* obj : floorsobjects)
		{
			obj->Edit();
		}
}

void FloorManager::Update()
{

	//floorselectTile = editorRef->GetSelectTile();
	UpdateWorld();
	SetSelectTile();
	SetEdit();
	collider->Update();
	objectManager->Update();
}

void FloorManager::UpdateMesh()
{
	if (floormapSize.x == 0 || floormapSize.y == 0)
		return;

	size = Vector3(floormapSize.x, 1.0f, floormapSize.y);

	SetVertices();
	MakeNormal();
	MakeTangent();
	mesh->UpdateVertices();
	collider->UpdateMesh(size);

	InitializerFloor();
}

void FloorManager::UpdateCeilingMesh()
{
	if (!showCeiling) return;


	ceilingCubes.clear();

	Cube* ceiling = new Cube(Vector3(cilingSize.x, 1, cilingSize.y), Vector2(cilingTiling.x, cilingTiling.y));
	ceiling->SetLocalPosition(Vector3(floorPos.x, floorPos.y + 7.0f, floorPos.z));
	ceiling->GetMaterial()->SetDiffuseMap(L"Resources/Textures/Block/T_Ore1_Color.png");
	ceiling->SetVertices();
	ceiling->MakeNormal();
	ceiling->MakeTangent();
	ceiling->Update();
	mesh->UpdateVertices();

	ceilingCubes.push_back(ceiling);
}

void FloorManager::SetEdit()
{
	if (KEY->Down(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse)
	{
		int r = floorselectTile.x;  // ? 선언 추가
		int q = floorselectTile.y;
		switch (floorEditType)
		{
		case FWall:
			CreateWall(wallSize, r, q);
			break;
		case FHermit:
			objectManager->CreateHermit(floorselectTile,floormapSize);
			break;
		case FOre:
			objectManager->CreateOre(floorselectTile, floormapSize,oreID);
			break;
		case FItem:
			break;
		default:
			break;
		}
	}
}

void FloorManager::SetSelectTile()
{
	Ray ray = CAM->ScreenPointToRay(mousePos);
	RaycastHit hit;

	if (collider->IsRayCollision(ray, &hit))
	{
		Vector2 size = floormapSize;
		Vector2 pos = { hit.point.x, hit.point.z };
		pos += size * 0.5f;
		floorselectTile = { (int)pos.x, (int)pos.y };

		floortileBuffer->Get()[0] = (float)floorselectTile.x / floormapSize.x * floormapTiling.x;
		floortileBuffer->Get()[1] = (floormapSize.y - (float)floorselectTile.y - 1) / floormapSize.y * floormapTiling.y;
	}
}

void FloorManager::CreateWall(Vector3 size, int x, int y)
{

	int adjustedX = floorselectTile.x - (int)floorPos.x;
	int adjustedy = floorselectTile.y - (int)floorPos.y;
	int z = floorselectTile.x;
	int w = floorselectTile.y;
	if (IsOccupied(x, y)) return;




	Vector3 startPos = Vector3(floormapSize.x * -0.5f, 0.0f , floormapSize.y * -0.5f);
	Vector3 pos = startPos + Vector3(z + 0.5f, 0.5f+(wallSize.y/2) , w + 0.5f);


	Cube* wall = new Cube(Vector3(wallSize.x, wallSize.y, wallSize.z),Vector2(wallTiling.x,wallTiling.y));
	wall->SetLocalPosition(pos);
	wall->GetMaterial()->SetDiffuseMap(L"Resources/Textures/Landscape/Dirt3.png");
	wall->SetVertices();
	wall->MakeNormal();
	wall->MakeTangent();
	wall->Update();
	mesh->UpdateVertices();

	floorsobjects.push_back(wall);
	SetFloorType(adjustedX, adjustedy, FWall);
	SetOccupied(adjustedX, adjustedy, true);
	SetWallSize(adjustedX, adjustedy, size);

}

void FloorManager::InitializerFloor()
{
	floorOccupied.clear();
	floortypes.clear();
	if (floormapSize.x <= 0 || floormapSize.y <= 0) { return; }

	floorOccupied.resize(floormapSize.y, vector<bool>(floormapSize.x, false));
	floortypes.resize(floormapSize.y, vector<FloorEditType>(floormapSize.x, FloorEditType::None));
}

bool FloorManager::IsOccupied(int x, int y)
{
	if (x < 0 || x >= floormapSize.x || y < 0 || y >= floormapSize.y)
		return true;

	return floorOccupied[y][x];
}

void FloorManager::SetOccupied(int x, int y, bool state)
{
	if (x < 0 || x >= floormapSize.x || y < 0 || y >= floormapSize.y)
		return;

	floorOccupied[y][x] = state;
}

void FloorManager::SetFloorType(int x, int y,FloorEditType type)
{
	if (y < 0 || y >= (int)floortypes.size() || x < 0 || x >= (int)floortypes[y].size())
		return;

	floortypes[y][x] = type;
}

FloorEditType FloorManager::GetFloorType(int x, int y) const
{
	if (y < 0 || y >= (int)floortypes.size() || x < 0 || x >= (int)floortypes[y].size())
		return FloorEditType::None;

	return floortypes[y][x];
}
Vector3 FloorManager::GetWallSize(int x, int y)
{
	return wallSizes[{x, y}];
}
void FloorManager::SetWallSize(int x, int y, Vector3 size)
{
	wallSizes[{x, y}] = size;
}
int FloorManager::GetOreID(int x, int y)
{
	return oreIDs[{x, y}];
}
void FloorManager::SetOreID(int x, int y, int id)
{
	oreIDs[{x, y}] = id;
}

