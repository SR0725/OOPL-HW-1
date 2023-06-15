#pragma once
#include "Item.h"

namespace game_framework
{
    class Enemy : public GameObject
    {
    public:
        Enemy* Init(vector<string> filename);
        Enemy* SetHp(float);
        Enemy* SetAttack(float);
        Enemy* SetDefense(float);
        Enemy* SetDropItems(vector<ItemTable*>*);
        Enemy* OnDropItem(vector<GameObject*>& gameObjects);
        void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        void OnHurt(string pressedKeys, vector<GameObject*>& gameObjects);
        void OnMove(string pressedKeys, vector<GameObject*>& gameObjects);
        void OnAttack(string pressedKeys, vector<GameObject*>& gameObjects);
        void Attack(GameObject* gameObject);
        void OnAttacked(GameObject* gameObject);
        float GetHp();
        vector<ItemTable*>* dropItems = new vector<ItemTable*>();

    private:
        int moveAnimTick = 0;
        float hp = 10;
        float attack = 2;
        float defense = 2;
        float onAttackedTick = 0;
    };

};