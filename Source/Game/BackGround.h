#pragma once

namespace game_framework
{
    class BackGround : public GameObject
    {
    public:
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects) override;
    };
};