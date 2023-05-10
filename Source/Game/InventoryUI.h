#pragma once
#include "MainCharacter.h"

using namespace game_framework;

namespace game_framework
{

    class InventoryUI : public GameObject
    {
    public:
        InventoryUI* SetInventory(Inventory *inventory);
        InventoryUI* SetBag(bool);
        InventoryUI* SetMainCharacter(MainCharacter*);
        InventoryUI* SetIndex(int);
        void showAmount();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects, int mouseX, int mouseY);
        void Render(GameObject *mainObject);
        void OnClick(vector<GameObject*>& gameObjects);
        Inventory* GetInventory();

    private:
        Inventory *inventory;
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
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects, int mouseX, int mouseY);

    private:
        MainCharacter *mainCharacter;
        InventoryUI *inventoryUI[24];
    };
};