#pragma once
namespace game_framework
{
    class GameObject
    {
    public:
        GameObject();
		GameObject* Init(vector<string> filename);
        void Destroy(vector<GameObject *> &gameObjects);
        GameObject* SetUI(bool);
        GameObject* SetCollider(bool);
        GameObject* SetTrigger(bool);
        GameObject* SetActive(bool _active = true);
        GameObject* SetSpeed(float _speed);
        GameObject* SetPosition(float _x, float _y);
        GameObject* SetX(float _x);
        GameObject* SetY(float _y);
        GameObject* SetId(string _id);
        string GetId();
        bool isCollideWith(GameObject* obj);
        bool isTriggerWith(GameObject* obj);
        bool GetIsCollider();
        bool GetIsTrigger();
        vector<string> GetFilename();
        float GetX();
        float GetY();
        float GetWidth();
        float GetHeight();
        void Render(GameObject *mainObject);
        void GoTop();
        void GoBottom();
        void GoRight();
        void GoLeft();
        virtual void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY);
        virtual void OnClick(vector<GameObject*>& gameObjects);
        CMovingBitmap bitmap;

    protected:
        vector<string> filename;
        float x = 0.0f;
        float y = 0.0f;
        float motionX = 0.0f;
        float motionY = 0.0f;
        float speed = 1.0f;
        bool active = false;
        bool isCollider = false;
        bool isTrigger = false;
        bool isUI = false;
        string id;
        string pressedKeys;
    };

};