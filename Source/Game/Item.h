#pragma once

namespace game_framework
{
    class Item : public GameObject
    {
    public:
        Item();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects) override;
        float tick = 0;

    private:
        float centerX = -9999;
        float centerY = -9999;
    };
};