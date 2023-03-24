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
        void Init(vector<string> filename, int _x, int _y, float _speed = 0);
        void SetActive(bool _active = true);
        void SetSpeed(float _speed);
        void GoTop();
        void GoBottom();
        void GoRight();
        void GoLeft();
        void onKeyDown(string isKeyPressed, string isKeyDown, string isKeyReleased);
        bool isCollideWith(GameObject *obj);
        bool GetIsCollider();
        int GetX();
        int GetY();
        int GetWidth();
        int GetHeight();
        void Render();

    private:
        int x;
        int y;
        float speed;
        bool active;
        bool isCollider;
        CMovingBitmap bitmap;
    };

    class MainCharacter : public GameObject
    {
    };
};