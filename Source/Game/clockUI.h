#pragma once
#include "MainCharacter.h"

using namespace game_framework;

namespace game_framework
{

    class ClockUI : public GameObject
    {
    public:
        ClockUI* Init();
        ClockUI* SetMainCharacter(MainCharacter*);
        void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        void ClockUI::Render(GameObject* mainObject, float time);

    private:
        MainCharacter* mainCharacter;
    };
};