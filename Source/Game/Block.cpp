#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "MainCharacter.h"
#include "Item.h"
#include "Block.h"
#include <string>
#include "tool.h"

using namespace game_framework;

Terrian::Terrian(vector<GameObject*>* gameObjects)
{
	this->gameObjects = gameObjects;

	Block* air = new Block();
	air
		->Init({ "resources/empty.bmp" })
		->SetDropItems(new vector<ItemTable*>())
		->SetId("air");

	Block* tree = new Block();
	tree
		->SetHp(24)
		->Init({ "resources/tree_block.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("log", "resources/log.bmp", 1, 4),
					new ItemTable("sapling", "resources/sapling.bmp", 1, 1),
					new ItemTable("sapling", "resources/sapling.bmp", 0.5, 1),
		}))
		->SetId("tree_block");

	Block* tree_small = new Block();
	tree_small
		->SetHp(16)
		->Init({ "resources/tree_small.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("log", "resources/log.bmp", 1, 2),
					new ItemTable("sapling", "resources/sapling.bmp", 1, 1),
				}))
				->SetId("tree_small_block");

	Block* stone = new Block();
	stone
		->SetHp(36)
		->Init({ "resources/stone_block.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("stone", "resources/stone.bmp", 1, 4),
				}))
				->SetId("stone_block");

	Block* coal = new Block();
	coal
		->SetHp(32)
		->Init({ "resources/coal_block.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("stone", "resources/stone.bmp", 1, 2),
					new ItemTable("coal", "resources/coal.bmp", 1, 4),
				}))
				->SetId("coal_block");

	Block* iron = new Block();
	iron
		->SetHp(56)
		->Init({ "resources/iron_block.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("iron", "resources/iron.bmp", 1, 4),
				}))
				->SetId("iron_block");

	// slive
	Block* slive = new Block();
	slive
		->SetHp(80)
		->Init({ "resources/slive_block.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("slive", "resources/slive.bmp", 1, 4),
				}))
				->SetId("slive_block");

	// craft_table
	Block* craft_table = new Block();
	craft_table
		->SetHp(4)
		->Init({ "resources/craft_table.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("craft_table", "resources/craft_table.bmp", 1, 1),
				}))
				->SetId("craft_table");

	BlocksType = new vector<GameObject*>({
			air, // 0
			tree, // 1
			tree_small, // 2
			stone, // 3
			coal, // 4
			iron, // 5
			slive, // 6
			craft_table, // 7
		});


	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			this->terrians[i][j] = 0;
		}
	}

	for (unsigned int i = 0; i < gameObjects->size(); i++)
	{
		if (dynamic_cast<Block*>(gameObjects->at(i)))
		{
			Block* block = dynamic_cast<Block*>(gameObjects->at(i));
			int x = (int)(block->GetX() / 32);
			int y = (int)(block->GetY() / 32);
			terrians[x][y] = block->BlockIndex;
		}
	}
}

bool Terrian::IsBlock(float x, float y)
{
	if (this->terrians[(int)(x / 48.0f)][(int)(y / 48.0f)] != 0)
	{
		return true;
	}
	return false;
}

void Terrian::SetBlock(float x, float y, int blockIndex)
{
	if (IsBlock(x, y))
	{
		for (unsigned int i = 0; i < gameObjects->size(); i++)
		{
			if (dynamic_cast<Block*>(gameObjects->at(i)))
			{
				Block* block = dynamic_cast<Block*>(gameObjects->at(i));
				if (block->GetX() == ((int)(x / 48.0f)) * 48.0f && block->GetY() == ((int)(y / 48.0f)) * 48.0f)
				{
					block->Destroy(*gameObjects);
					break;
				}
			}
		}
	}

	Block* templateBlock = dynamic_cast<Block*>(BlocksType->at(blockIndex));
	Block* newBlock = new Block();

	newBlock
		->SetTerrian(this)
		->SetHp(templateBlock->GetHp())
		->Init(templateBlock->GetFilename())
		->SetDropItems(templateBlock->dropItems)
		->SetBlockIndex(blockIndex)
		->SetPosition(((int)(x / 48.0f)) * 48.0f, ((int)(y / 48.0f)) * 48.0f)
		->SetCollider(true)
		->SetId(templateBlock->GetId())
		->SetActive(true);

	this->gameObjects->push_back(newBlock);
	this->terrians[(int)(x / 48.0f)][(int)(y / 48.0f)] = blockIndex;
}

Block::Block()
{
	hp = 1;
	onAttackedTick = 0;
	centerX = -9999;
	centerY = -9999;
	dropItems = new vector<ItemTable*>();
}

Block* Block::Init(vector<string> filename)
{
	GameObject::Init(filename);
	return this;
}

void Block::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	if (hp <= 0)
	{
		OnDropItem(gameObjects);
		Destroy(gameObjects);
		return;
	}

	if (onAttackedTick > 0)
	{
		onAttackedTick -= 1.0f;
		this->SetX(centerX + sin(onAttackedTick) * 4.0f);
		this->SetY(centerY + sin(onAttackedTick) * 4.0f);

		if (onAttackedTick <= 0)
		{
			this->SetX(centerX);
			this->SetY(centerY);
		}
	}

	// tree_small
	if (this->BlockIndex == 2) {
		this->tick++;
		if (tick > 60 * 60) {
			this->terrian->SetBlock(this->GetX(), this->GetY(), 1);
		}
	}
}

void Block::OnAttacked(GameObject* gameObject)
{

	if (onAttackedTick > 0)
		return;

	float damage = 1.0;
	if (dynamic_cast<MainCharacter*>(gameObject))
	{
		MainCharacter* player = dynamic_cast<MainCharacter*>(gameObject);
		string useTool = player->GetInventory(player->GetMainHandSelectedIndex())->id;
		if ((BlockIndex == 1 || BlockIndex == 2)) { // tree
			if (useTool == "wood_axe") {
				damage = 2;
			}

			if (useTool == "stone_axe") {
				damage = 3;
			}

			if (useTool == "iron_axe") {
				damage = 4;
			}
		}
		if ((BlockIndex == 3 || BlockIndex == 4 || BlockIndex == 5 || BlockIndex == 6)) { // stone
			if (useTool == "wood_pickaxe") {
				damage = 2;
			}

			if (useTool == "stone_pickaxe") {
				damage = 3;
			}

			if (useTool == "iron_pickaxe") {
				damage = 4;
			}
		}
		if (useTool == "wood_sword" || useTool == "stone_sword" || useTool == "iron_sword") {
			return;
		}
	}
	hp -= damage;
	onAttackedTick = 15.0f;
	centerX = this->GetX();
	centerY = this->GetY();
}

void Block::OnClick(vector<GameObject*>& gameObjects) {
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);
	if (character->GetX() + 128 < GetX() || character->GetX() - 128 > GetX())
	{
		return;
	}

	if (character->GetY() + 128 < GetY() || character->GetY() - 128 > GetY())
	{
		return;
	}

	// craft_table
	if (this->BlockIndex == 7) {
		character->SetUseTable(true);
	}
}


Block* Block::SetHp(float _hp) {
	this->hp = _hp;

	return this;
}
float Block::GetHp() {
	return hp;
}

Block* Block::SetDropItems(vector<ItemTable*>* _dropItems)
{
	dropItems = _dropItems;

	return this;
}

Block* game_framework::Block::SetTerrian(Terrian* terrian)
{
	this->terrian = terrian;

	return this;
}

Block* game_framework::Block::SetBlockIndex(int blockIndex)
{
	this->BlockIndex = blockIndex;


	return this;
}

Block* Block::OnDropItem(vector<GameObject*>& gameObjects)
{
	for (unsigned int i = 0; i < dropItems->size(); i++)
	{
		ItemTable* itemTable = dropItems->at(i);

		if (itemTable->rate * 10000 < random(0.0f, 9999.0f))
		{
			continue;
		}

		for (int j = 0; j < itemTable->number; j++)
		{
			Item* item = new Item();
			item->Init({ itemTable->path })
				->SetPosition(this->GetX() + random(-16.0f, 16.0f), this->GetY() + random(-16.0f, 16.0f))
				->SetTrigger(true)
				->SetId(itemTable->id)
				->SetActive(true);
			gameObjects.push_back(item);
		}
	}
	return this;
}

void Block::Destroy(vector<GameObject*>& gameObjects)
{
	GameObject::Destroy(gameObjects);

	int x = (int)(this->GetX() / 48.0f);
	int y = (int)(this->GetY() / 48.0f);

	this->terrian->terrians[x][y] = 0;
}
