#pragma once

using namespace game_framework;

namespace game_framework
{

    class InventoryCraftUI : public GameObject
    {
    public:
        InventoryCraftUI(bool isTable, string id, int number, string costId, int cost);
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects) override;
        void Render(GameObject *mainObject);

    private:
        bool bagOpen;
        bool craftOpen;
        bool isTable;
        string id;
        int number;
        string costId;
        int cost;
    };

};