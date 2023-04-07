#pragma once

namespace game_framework
{

    class InventoryUI : public GameObject
    {
    public:
        void SetInventory(Inventory *inventory);
        void showAmount();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects) override;

    private:
        Inventory *inventory;
    };

    class InventoriesUI : public GameObject
    {
    public:
        void Init(MainCharacter *mainCharacter, vector<GameObject *> &gameObjects);
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects);

    private:
        MainCharacter *mainCharacter;
        GameObject *inventoryUI[6];
    };
};