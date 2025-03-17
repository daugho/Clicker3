#include "Framework.h"

Hermit::Hermit(string modelName, HermitType type) : Cube(Vector3(1, 2, 1)) , type(type)
{
	model = new Model(modelName);
	model->SetParent(this);

	collider = new BoxCollider(Vector3(1,2,1));
	collider->SetParent(this);
    LoadShopTable();
}

Hermit::~Hermit()
{
	delete collider;
}

void Hermit::Render()
{
    model->Render();
    collider->Render();

    if (isShopOpen && shopUI)
    {
        shopUI->Render();
    }
}

void Hermit::Update()
{
    if (model)
        model->UpdateWorld();
    if (collider)
    {
        collider->SetLocalPosition(Vector3(0, 1, 0));
        collider->UpdateWorld();
    }

    if (shopUI)
    {
        shopUI->UpdateWorld();
    }
}

void Hermit::Shop1Slot()
{

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
        filename = "Resources/Tables/HermitShop1.csv";
        break;
    case HermitType::Merchant2:
        filename = "Resources/Tables/HermitShop2.csv";
        break;
    case HermitType::Merchant3:
        filename = "Resources/Tables/HermitShop3.csv";
        break;
    default:
        return;
    }

    FILE* file;
    fopen_s(&file, filename.c_str(), "r");

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

        shopData data;
        data.id = stoi(datas[0]);
        data.name = datas[1];
        data.descrip = Utility::ToWString(datas[2]);
        data.price = stoi(datas[3]);
        data.icon = Utility::ToWString(datas[4]);

        shopTable.push_back(data);
    }
    fclose(file);
}

void Hermit::LoadShopUI()
{
    wstring texturePath;

    switch (type)
    {
    case HermitType::Merchant1:
        texturePath = L"Resources/Textures/UI/Shop.png";
        break;
    case HermitType::Merchant2:
        texturePath = L"Resources/Textures/Bag.png";
        break;
    case HermitType::Merchant3:
        texturePath = L"Resources/Textures/Shop3.png";
        break;
    default:
        return;
    }

    shopUI = new Quad(texturePath);
    shopUI->SetLocalScale(CENTER);
    shopUI->SetLocalPosition(Vector3(0, 1, 0));
}
