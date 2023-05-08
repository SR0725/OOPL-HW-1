#pragma once
#include "MainCharacter.h"

using namespace game_framework;

namespace game_framework
{

    class InventoryUI : public GameObject
    {
    public:
        void SetInventory(Inventory *inventory);
        void showAmount();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects) override;
        void Render(GameObject *mainObject);
        void SetBag(bool);

    private:
        Inventory *inventory;
        bool bagOpen;
        bool isBag;
    };

    class InventoriesUI : public GameObject
    {
    public:
        void Init(MainCharacter *mainCharacter, vector<GameObject *> &gameObjects);
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects);

    private:
        MainCharacter *mainCharacter;
        InventoryUI *inventoryUI[24];
    };
};