#include "Framework.h"

Hermit::Hermit(string modelName) : Cube(Vector3(1, 2, 1))
{
	model = new Model(modelName);
	model->SetParent(this);

	collider = new BoxCollider(Vector3(1,2,1));
	collider->SetParent(this);

}

Hermit::~Hermit()
{
	delete collider;
}

void Hermit::Render()
{
	model->Render();
	//collider->Render();
}

void Hermit::Update()
{
	UpdateWorld();
	if (model)
		model->UpdateWorld();
	if (collider)
	{
		collider->SetLocalPosition(Vector3(0, 1, 0));
		collider->UpdateWorld();
	}
}

void Hermit::ByeOre()
{
}

void Hermit::SellItem()
{
}

void Hermit::Edit()
{
	model->Edit();
}

bool Hermit::IsRayCollision(const Ray& ray, RaycastHit* hit)
{
	return collider->IsRayCollision(ray, hit);
}

void Hermit::LoadShopTable()
{
    string filename;

    switch (type)
    {
    case HermitType::Merchant1:
        filename = "Resources/Data/HermitShop1.csv";
        break;
    case HermitType::Merchant2:
        filename = "Resources/Data/HermitShop2.csv";
        break;
    case HermitType::Merchant3:
        filename = "Resources/Data/HermitShop3.csv";
        break;
    case HermitType::Merchant4:
        filename = "Resources/Data/HermitShop4.csv";
        break;
    default:
        return;
    }

    FILE* file;
    fopen_s(&file, filename.c_str(), "r");

    if (!file)
    {
        OutputDebugStringA(("Failed to open: " + filename + "\n").c_str());
        return;
    }

    bool isFirstLine = true;
    while (!feof(file))
    {
        char temp[1024];
        fgets(temp, 1024, file);

        if (isFirstLine)
        {
            isFirstLine = false;
            continue;
        }

        string row = temp;
        Utility::Replace(row, "\n", "");

        vector<string> datas = Utility::SplitString(row, ",");

        if (datas.size() < 4) continue; // 데이터가 부족한 경우 무시

        shopData data;
        data.id = stoi(datas[0]);
        data.name = datas[1];
        data.descrip = Utility::ToWString(datas[2]);
        data.price = stoi(datas[3]);

        shopTable.push_back(data);
    }
    fclose(file);
}
