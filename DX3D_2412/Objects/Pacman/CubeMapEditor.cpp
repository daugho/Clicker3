#include "Framework.h"

CubeMapEditor::CubeMapEditor()
{	
	tileBuffer = new FloatValueBuffer();

	//Load();
	material->SetShader(L"Custom/MapEditor.hlsl");	
	floorManager = new FloorManager(Vector3(0, 0, 0), { 10, 10 }, this);
	//objectManager = new ObjectManager(floorManager);
}

CubeMapEditor::~CubeMapEditor()
{	
	delete floorManager;
	delete tileBuffer;
	delete objectManager;
	for (GameObject* object : objects)
		delete object;
	OreManager::Delete();
}

void CubeMapEditor::Update()
{
	if (player != nullptr)
	{
		//vector<BoxCollider*> hitCoins = objectManager->GetCollisionObjects(5.0f);
		//
		//for (BoxCollider* collider : objectManager->GetAllColliders())
		//{
		//	if (find(hitCoins.begin(), hitCoins.end(), collider) != hitCoins.end())
		//	{
		//		collider->SetColor(Float4(1.0f, 0.0f, 0.0f, 1.0f));
		//	}
		//	else
		//	{
		//		collider->SetColor(Float4(1, 1, 1, 1));
		//	}
		//}
	}
	if (KEY->Down(VK_NUMPAD7))
	{
		CAM->SetTarget(player);
		CAM->TargetOptionLoad("FPSMode");
	}
	if (player != nullptr)
		player->Update();
	for (pair<EditType, GameObject*> preview : previews)
		preview.second->Update();
	for (FloorManager* floor : floorManagers)
		floor->Update();
	//objectManager->Update();
	OreManager::Get()->Update();
	floorManager->Update();
}

void CubeMapEditor::Render()
{	
	for (FloorManager* floor : floorManagers)
		floor->Render();
	//objectManager->Render();
	OreManager::Get()->Render();
	tileBuffer->SetPS(10);
	//Cube::Render();
	for (GameObject* object : objects)
		object->Render();
	Environment::Get()->SetAdditive();
	for (pair<EditType, GameObject*> preview : previews)
		preview.second->Render();
	Environment::Get()->SetAlphaBlend(true);
	if (player != nullptr)
		player->Render();
	Environment::Get()->SetAlphaBlend(false);
}

void CubeMapEditor::Edit()
{
	ImGui::Text("MapEditor");

	if (ImGui::Button("Add Floor"))
	{
		static int width = 0;
		static int height = 0;
		const int maxWidth = 3;

		FloorManager* floor = new FloorManager(Vector3(width * 25.0f, 0, height * 25.0f), { 10, 10 }, this);

		floorManagers.push_back(floor);

		width++;

		if (width >= maxWidth)
		{
			width = 0;
			height++;
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Save"))
	{
		Save();
	}

	ImGui::SameLine();
	if (ImGui::Button("Load"))
	{
		Load();
	}

	if (ImGui::TreeNode("Floor Managers"))
	{
		for (int i = 0; i < floorManagers.size(); i++)
		{
			string label = "Floor " + to_string(i + 1);
			if (ImGui::TreeNode(label.c_str()))
			{
				floorManagers[i]->Edit();

				if (ImGui::Button("Remove Floor"))
				{
					delete floorManagers[i];
					floorManagers.erase(floorManagers.begin() + i);
					ImGui::TreePop();
					break;
				}

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
	material->Edit();
	//objectManager->Edit();
}

void CubeMapEditor::Save()
{
	string path = "Resources/TextData/";

	if (!filesystem::exists(path))
	{
		filesystem::create_directories(path);
	}

	BinaryWriter* writer = new BinaryWriter("Resources/TextData/Pacman.map");

	// 1?? 바닥 개수 저장
	int floorCount = static_cast<int>(floorManagers.size());
	writer->Data<int>(floorCount);

	for (FloorManager* floor : floorManagers)
	{
		Vector3 position = floor->GetLocalPosition();
		writer->Data<Vector3>(position); // 바닥 위치 저장

		POINT size = floor->GetMapSize();
		writer->Data<POINT>(size); // 바닥 크기 저장

		// 2?? 각 타일의 타입 저장
		for (int y = 0; y < size.y; y++)
		{
			for (int x = 0; x < size.x; x++)
			{
				int type = (int)floor->GetFloorType(x, y); // 타일 타입 가져오기

				if (type == None)
					continue;

				writer->Data<int>(type); // 타일 타입 저장


				if (type == FWall)
				{
					Vector3 wallSize = floor->GetWallSize(x, y);
					writer->Data<Vector3>(wallSize);
				}

				// ? FOre이면 광물 ID도 저장
				if (type == FOre)
				{
					int oreID = floor->GetOreID(x, y);
					writer->Data<int>(oreID);
				}
			}
		}
	}

	delete writer;
}
void CubeMapEditor::Load()
{
	std::string filePath = "Resources/TextData/Pacman.map";
	if (!std::filesystem::exists(filePath))
		return;

	BinaryReader* reader = new BinaryReader(filePath);

	// 기존 FloorManager 삭제
	for (FloorManager* floor : floorManagers)
		delete floor;
	floorManagers.clear();

	int floorCount = reader->Data<int>();

	for (int i = 0; i < floorCount; i++)
	{
		Vector3 position = reader->Data<Vector3>(); // 바닥 위치 불러오기
		POINT size = reader->Data<POINT>();         // 바닥 크기 불러오기

		FloorManager* floor = new FloorManager(position, size, this);
		floor->InitializerFloor();
		for (int y = 0; y < size.y; y++)
		{
			for (int x = 0; x < size.x; x++)
			{
				int type = reader->Data<int>();
				floor->SetFloorType(x, y, (FloorEditType)type);
			}
		}

		floor->SetLocalScale(1, 1, 1);
		floor->UpdateMesh();

		floorManagers.push_back(floor);
	}

	delete reader;
}

