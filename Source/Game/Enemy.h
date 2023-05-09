#pragma once

namespace game_framework
{
    class Enemy : public GameObject
    {
    public:
        Enemy* Init(vector<string> filename);
        Enemy* SetHp(float);
        Enemy* SetAttack(float);
        Enemy* SetDefense(float);
        void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects);
        void OnHurt(string pressedKeys, vector<GameObject*>& gameObjects);
        void OnMove(string pressedKeys, vector<GameObject*>& gameObjects);
        void OnAttack(string pressedKeys, vector<GameObject*>& gameObjects);
        void Attack(GameObject* gameObject);
        void OnAttacked(GameObject* gameObject);
        float GetHp();
        float GetAttack();
        float GetDefense();

    private:
        float hp;
        float attack;
        float defense;
        float onAttackedTick = 0;
    };

};