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
        MainCharacter *Init(vector<string> filename);
        int GetMainHandSelectedIndex();
        MainCharacter *SetMainHandSelectedIndex(int);
        MainCharacter *SetTerrian(Terrian *);
        MainCharacter* SetUseTable(bool);
        MainCharacter* SetUseWaterPurifier(bool);
        MainCharacter* SetInventory(int, Inventory*);
        MainCharacter* SetHp(float);
        MainCharacter* SetHungry(float);
        MainCharacter* SetThirsty(float);
        bool GetUseTable();
        bool GetUseWaterPurifier();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects, vector<GameObject *> &uiObjects, int mouseX, int mouseY);
        void OnMove(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnMoveSound();
        void OnHurt(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnAttack(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnBuild(vector<GameObject*>& gameObjects);
        void OnFillWater(vector<GameObject*>& gameObjects);
        void OnBarbecue(vector<GameObject*>& gameObjects);
        void OnDrink(vector<GameObject*>& gameObjects);
        void OnEat(vector<GameObject*>& gameObjects);
        void Attack(GameObject *gameObject);
        void OnAttacked(GameObject *gameObject);
        float GetHp();
        float GetHungry();
        float GetThirsty();
        float attack = 1.0f;
        Inventory *GetInventory(int);

    private:
        bool useTable = false;
        bool useWaterPurifier = false;
        Terrian *terrian;
        Inventory *inventories[28];
        int mainHandSelectedIndex = 0;
        void addItemToInventory(Item *item);
        float onAttackedTick = 0;
        float centerX = -9999;
        float centerY = -9999;
        float hp = 100;
        float hungry = 100;
        float thirsty = 100;
        int moveSoundTick = 0;
        int moveAnimTick = 0;

    };

};