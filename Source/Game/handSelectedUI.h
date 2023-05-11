#pragma once
#include "MainCharacter.h"

using namespace game_framework;

namespace game_framework
{

    class HandSelectedUI : public GameObject
    {
    public:
        HandSelectedUI* Init(vector<string> filename);
        HandSelectedUI* SetMainCharacter(MainCharacter*);
        void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);

    private:
        MainCharacter* mainCharacter;
    };
};