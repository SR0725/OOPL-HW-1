#pragma once
#include "MainCharacter.h"

using namespace game_framework;

namespace game_framework
{

    class InventoryUI : public GameObject
    {
    public:
        Inventory* GetInventory();
        InventoryUI* SetBag(bool);
        InventoryUI* SetMainCharacter(MainCharacter*);
        InventoryUI* SetIndex(int);
        void showAmount();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        void Render(GameObject *mainObject);
        void OnClick(vector<GameObject*>& gameObjects);

    private:
        MainCharacter* mainCharacter;
        int index = 0;
        bool bagOpen;
        bool isBag;
        bool isDrag;
        float originX = -9999;
        float originY = -9999;
    };

    class InventoriesUI : public GameObject
    {
    public:
        InventoriesUI* Init(MainCharacter *mainCharacter, vector<GameObject *> &gameObjects);
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        void Render(GameObject* mainObject);
        void ShowInventoryInfo();

    private:
        MainCharacter *mainCharacter;
        InventoryUI *inventoryUI[28];
        GameObject* inventory_background = new GameObject();
        bool isBagOpen;
        string showInventoryTitle = "";
    };
};