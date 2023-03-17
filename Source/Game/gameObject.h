namespace game_framework
{
    class InventoryBox : public CGameState
    {
    public:
        int id;
        int amount;
        string name;
        string description;
    }

    class GameObject : public CGameState
    {
    public:
        GameObject(string bitmapSrc, int x, int y, int hungry, int health, int speed, int damage, bool isActive));
        void setActive(bool active);
        void goTop();
        void goDown();
        void goLeft();
        void goRight();
        void attack(GameObject *target);
        void OnAttacken(int damage);
        void addInventory(int id, int amount, string name, string description);
        InventoryBox *getInventories();
        void OnUpdate();

    private:
        CMovingBitmap bitmap;
        InventoryBox inventories[10];
        int x;
        int y;
        int hungry;
        int health;
        int speed;
        int damage;
        bool isActive;
        void die();
    };
}