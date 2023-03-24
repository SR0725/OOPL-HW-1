#pragma once
namespace game_framework
{
    class InventoryBox
    {
    public:
        InventoryBox();
        int id;
        int amount;
        string name;
        string description;
    };

    class GameObject
    {
    public:
        GameObject();
        void Init(vector<string> filename, float _x, float _y, float _speed = 0);
        void SetActive(bool _active = true);
        void SetSpeed(float _speed);
        void GoTop();
        void GoBottom();
        void GoRight();
        void GoLeft();
        void onUpdate(string pressedKeys);
        bool isCollideWith(GameObject *obj);
        bool GetIsCollider();
        float GetX();
        float GetY();
        float GetWidth();
        float GetHeight();
        void Render(GameObject *mainObject);

    private:
        float x;
        float y;
        float speed;
        bool active;
        bool isCollider;
        string pressedKeys;
        CMovingBitmap bitmap;
    };

    class MainCharacter : public GameObject
    {
    };
};