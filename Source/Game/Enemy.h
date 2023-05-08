#pragma once

namespace game_framework
{
    class Enemy : public GameObject
    {
    public:
        void Init(vector<string> filename, float _x, float _y, float _speed);
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnHurt(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnMove(string pressedKeys, vector<GameObject *> &gameObjects);
        void OnAttack(string pressedKeys, vector<GameObject *> &gameObjects);
        void Attack(GameObject *gameObject);
        void OnAttacked(GameObject *gameObject);
        void SetHp(float);
        void SetAttack(float);
        void SetDefense(float);
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