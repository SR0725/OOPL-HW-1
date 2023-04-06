#pragma once
#include "Item.h"

namespace game_framework
{

    class Inventory
    {
    public:
        Inventory(string id, string name, string description, int amount);
        Inventory(string id, string name, string description);
        string id;
        string name;
        string description;
        int amount;
    };

    class MainCharacter : public GameObject
    {
    public:
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnMove(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnAttack(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnGetItem(Item *item, vector<GameObject *> &gameObjects);
        void Attack(GameObject *gameObject);

    private:
        vector<Inventory> inventories;
        int inventoryIndex = 0;
        void addItemToInventory(Item *item);
    };

};