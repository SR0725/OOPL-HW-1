#pragma once

namespace game_framework
{
    class ItemTable {
    public:
        string id;
        string path;
        float rate;
        int number;
        ItemTable(string, string, float, int);
    };


    class Item : public GameObject
    {
    public:
        Item();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects);
        float tick = 0;

    private:
        float centerX = -9999;
        float centerY = -9999;
    };
};