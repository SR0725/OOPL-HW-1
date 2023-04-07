#pragma once
namespace game_framework
{
    class GameObject
    {
    public:
        GameObject();
        void Init(vector<string> filename, float _x, float _y, float _speed);
        void Destroy(vector<GameObject *> &gameObjects);
        void SetUI(bool);
        void SetCollider(bool);
        void SetTrigger(bool);
        void SetActive(bool _active = true);
        void SetSpeed(float _speed);
        void GoTop();
        void GoBottom();
        void GoRight();
        void GoLeft();
        virtual void OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects) = 0;
        bool isCollideWith(GameObject *obj);
        bool isTriggerWith(GameObject *obj);
        bool GetIsCollider();
        bool GetIsTrigger();
        float GetX();
        float GetY();
        void SetX(float _x);
        void SetY(float _y);
        float GetWidth();
        float GetHeight();
        void Render(GameObject *mainObject);
        void SetId(string _id);
        string GetId();

    protected:
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
        CMovingBitmap bitmap;
    };

};