#pragma once
#include "MainCharacter.h"

using namespace game_framework;

namespace game_framework
{

    class ThirstyUI : public GameObject
    {
    public:
        ThirstyUI* Init();
        ThirstyUI* SetMainCharacter(MainCharacter*);
        void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        void ThirstyUI::Render(GameObject* mainObject);

    private:
        MainCharacter* mainCharacter;
    };
};