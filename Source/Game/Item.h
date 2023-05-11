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


    class ItemsTable {
    public:
        vector<ItemTable*>* items = new vector<ItemTable*>();
        vector<ItemTable*>* inventoryItems = new vector<ItemTable*>();
        ItemsTable();

        ItemTable* GetItemById(string id);
        ItemTable* GetInventoryItemById(string id);
        vector<string> GetInventoryItemsPath();
    };


    class Item : public GameObject
    {
    public:
        Item();
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        float tick = 0;

    private:
        float centerX = -9999;
        float centerY = -9999;
    };
};