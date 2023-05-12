#pragma once
#include "MainCharacter.h"

using namespace game_framework;

namespace game_framework
{

    class HealthUI : public GameObject
    {
    public:
        HealthUI* Init();
        HealthUI* SetMainCharacter(MainCharacter*);
        void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        void HealthUI::Render(GameObject* mainObject);

    private:
        MainCharacter* mainCharacter;
    };
};