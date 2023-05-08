#pragma once
#include "Item.h"

namespace game_framework
{

    class Inventory
    {
    public:
        Inventory();
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
        MainCharacter();
        void Init(vector<string> filename, float _x, float _y, float _speed);
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnMove(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnHurt(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnAttack(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnGetItem(Item *item, vector<GameObject *> &gameObjects);
        void Attack(GameObject *gameObject);
        void OnAttacked(GameObject *gameObject);
        float GetHp();
        Inventory *
        GetInventory(int);

    private:
        Inventory inventories[24];
        int inventoryIndex = 0;
        void addItemToInventory(Item *item);
        float onAttackedTick = 0;
        float centerX = -9999;
        float centerY = -9999;
        float hp = 10;
    };

};