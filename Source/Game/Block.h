#pragma once
namespace game_framework
{
	class Block : public GameObject
	{
	public:
		Block();
		Block* Init(vector<string> filename);
		void OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects) override;
		Block* SetDropItems(vector<ItemTable*>&);
		Block* OnDropItem(vector<GameObject*>& gameObjects);
		void OnAttacked(GameObject* gameObject);

	private:
		vector<ItemTable*>& dropItems = vector<ItemTable*>();
		float onAttackedTick = 0;
		float centerX = -9999;
		float centerY = -9999;
		float hp = 10;
	};
};