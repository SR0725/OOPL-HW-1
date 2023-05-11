#pragma once
#include "Item.h"
#include "Block.h"

namespace game_framework
{

    class Inventory
    {
    public:
        Inventory();
        string id;
        int textureIndex;
        int number;
    };

    class MainCharacter : public GameObject
    {
    public:
        MainCharacter();
        MainCharacter* Init(vector<string> filename);
        int GetMainHandSelectedIndex();
        MainCharacter* SetMainHandSelectedIndex(int);
        MainCharacter* SetTerrian(Terrian*);
        MainCharacter* SetUseTable(bool);
        bool GetUseTable();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        void OnMove(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnHurt(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnAttack(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnBuild(vector<GameObject*>& gameObjects);
        void Attack(GameObject *gameObject);
        void OnAttacked(GameObject *gameObject);
        float GetHp();
        Inventory * GetInventory(int);


    private:
        bool useTable = false;
        Terrian* terrian;
        Inventory inventories[24];
        int mainHandSelectedIndex = 0;
        void addItemToInventory(Item *item);
        float onAttackedTick = 0;
        float centerX = -9999;
        float centerY = -9999;
        float hp = 10;
    };

};