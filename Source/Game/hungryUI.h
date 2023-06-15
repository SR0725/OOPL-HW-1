#pragma once
#include "MainCharacter.h"

using namespace game_framework;

namespace game_framework
{

    class HungryUI : public GameObject
    {
    public:
        HungryUI* Init();
        HungryUI* SetMainCharacter(MainCharacter*);
        void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        void HungryUI::Render(GameObject* mainObject);

    private:
        MainCharacter* mainCharacter;
    };
};