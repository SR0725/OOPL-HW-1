namespace game_framework
{
    class GameObject : public CGameState
    {
    public:
        int x;
        int y;
        int hungry;
        void update();
        void goTop();
        void goDown();
        void goLeft();
        void goRight();
        void eat();
        void broken();

    private:
        CMovingBitmap bitmap;
        void die();
    };
}