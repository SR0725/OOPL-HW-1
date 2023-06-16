#pragma once
#include "Item.h"


using namespace game_framework;

namespace game_framework
{

	class CraftItem : public GameObject
	{
	public:
		CraftItem();
		~CraftItem();
		CraftItem* Init(vector<string> filename);
		CraftItem* SetRawMaterials(vector<ItemTable*>&);
		CraftItem* SetProducts(vector<ItemTable*>&);
		CraftItem* SetOnlyTable(bool onlyTable);
		CraftItem* SetOnlyWaterPurifier(bool onlyWaterPurifier);
		CraftItem* SetProductTitle(string);
		CraftItem* SetRawMaterialTitle(string);
		void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
		void Render(GameObject* mainObject);
		void OnClick(vector<GameObject*>& gameObjects);

		bool isOpen;
		bool isOpenInTable;
		bool isOpenInWaterPurifier;
		bool onlyTable = false;
		bool onlyWaterPurifier = false;
		string productTitle;
		string rawMaterialsTitle;
	private:
		vector<ItemTable*> rawMaterials = vector<ItemTable*>();
		vector<ItemTable*> products = vector<ItemTable*>();
	};


	class CraftTable : public GameObject
	{
	public:
		CraftTable();
		~CraftTable();
		CraftTable* Init(vector<GameObject*>& uiObjects);
		void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
		void Render(GameObject* mainObject);
		void ShowCraftInfo();
	private:
		vector<CraftItem*> craftItems = vector<CraftItem*>();
		GameObject* craft_background = new GameObject();
		bool isBagOpen;
		bool isTableOpen;
		bool isWaterPurifier;
		string showProductTitle = "";
		string showRawMaterialsTitle = "";
	};

};