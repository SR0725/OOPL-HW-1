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
        void showAmount();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects);
        void Render(GameObject *mainObject);

    private:
        Inventory *inventory;
        bool bagOpen;
        bool isBag;
    };

    class InventoriesUI : public GameObject
    {
    public:
        InventoriesUI* Init(MainCharacter *mainCharacter, vector<GameObject *> &gameObjects);
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects);

    private:
        MainCharacter *mainCharacter;
        InventoryUI *inventoryUI[24];
    };
};