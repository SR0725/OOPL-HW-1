#pragma once
#include "MainCharacter.h"

using namespace game_framework;

namespace game_framework
{

    class GameOverUI : public GameObject
    {
    public:
        GameOverUI* Init(float, int);
        void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        void GameOverUI::Render(GameObject* mainObject);

    private:
        float time = 0;
        int day = 0;
        MainCharacter* mainCharacter;
    };
};