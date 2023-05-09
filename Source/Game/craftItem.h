#pragma once
#include "Item.h"


using namespace game_framework;

namespace game_framework
{

    class CraftItem : public GameObject
    {
    public:
        CraftItem();
        CraftItem* Init(vector<string> filename);
        CraftItem* SetRawMaterials(vector<ItemTable*>&);
        CraftItem* SetProducts(vector<ItemTable*>&);
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects);
        void Render(GameObject *mainObject);
        void OnClick(vector<GameObject *> &gameObjects);

    private:
        bool isOpen;
        bool isOpenInTable;
        bool onlyTable;
        vector<ItemTable*> rawMaterials = vector<ItemTable*>();
        vector<ItemTable*> products = vector<ItemTable*>();
    };

};