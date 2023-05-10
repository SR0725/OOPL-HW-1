#pragma once

using namespace std;
namespace game_framework
{

	class Terrian {
	public:
		Terrian(vector<GameObject*>* gameObjects);
		void SetBlock(float x, float y, int blockIndex);
		bool IsBlock(float x, float y);
		vector<GameObject*>* gameObjects = nullptr;
		vector<GameObject*>* BlocksType = nullptr;
		int terrians[21][21] = {};
	};

	class Block : public GameObject
	{
	public:
		Block();
		Block* Init(vector<string> filename);
		void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, int mouseX, int mouseY) override;
		Block* SetDropItems(vector<ItemTable*>*);
		Block* SetTerrian(Terrian*);
		Block* SetBlockIndex(int);
		Block* OnDropItem(vector<GameObject*>& gameObjects);
		void Destroy(vector<GameObject*>& gameObjects);
		void OnAttacked(GameObject* gameObject);
		vector<ItemTable*>* dropItems = new vector<ItemTable*>();
		int BlockIndex = 0;

	private:
		Terrian* terrian = nullptr;
		float onAttackedTick = 0;
		float centerX = -9999;
		float centerY = -9999;
		float hp = 10;
	};
};