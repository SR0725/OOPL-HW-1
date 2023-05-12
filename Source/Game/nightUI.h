#pragma once
#include "MainCharacter.h"

using namespace game_framework;

namespace game_framework
{

    class NightUI : public GameObject
    {
    public:
        NightUI* Init();
        NightUI* SetMainCharacter(MainCharacter*);
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        void NightUI::Render(GameObject* mainObject, float time);

    private:
        MainCharacter* mainCharacter;
    };
};