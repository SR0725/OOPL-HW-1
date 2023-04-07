#pragma once

namespace game_framework
{
    class Tree : public GameObject
    {
    public:
        Tree();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects) override;
        void OnAttacked(GameObject *gameObject);

    private:
        float onAttackedTick = 0;
        float centerX = -9999;
        float centerY = -9999;
        float hp = 10;
    };
};