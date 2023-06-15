#pragma once

using namespace std;
namespace game_framework
{

	class Terrian {
	public:
		Terrian(vector<GameObject*>* gameObjects);
		void SetBlock(float x, float y, int blockIndex);
		bool IsBlock(float x, float y);
		bool IsBehindWater(float x, float y);
		vector<GameObject*>* gameObjects = nullptr;
		vector<GameObject*>* BlocksType = nullptr;
		int terrians[22][22] = {};
	};

	class Block : public GameObject
	{
	public:
		Block();
		Block* Init(vector<string> filename);
		Block* SetDropItems(vector<ItemTable*>*);
		Block* SetTerrian(Terrian*);
		Block* SetBlockIndex(int);
		Block* OnDropItem(vector<GameObject*>& gameObjects);
		Block* SetHp(float);
		Block* SetIndestructible(boolean);
		Block* SetAnimation(int, boolean);
		int GetAnimationTime();
		bool GetAnimationNoLoop();
		void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY) override;
		void OnClick(vector<GameObject*>& gameObjects);

		float GetHp();
		void Destroy(vector<GameObject*>& gameObjects);
		void OnAttacked(GameObject* gameObject);
		vector<ItemTable*>* dropItems = new vector<ItemTable*>();
		int BlockIndex = 0;
		boolean IsIndestructible();

	protected:
		Terrian* terrian = nullptr;
		float onAttackedTick = 0;
		float centerX = -9999;
		float centerY = -9999;
		float hp = 10;
		int tick = 0;
		int animationTime = 0;
		boolean animationNoLoop = false;
		boolean indestructible = false;
	};
};