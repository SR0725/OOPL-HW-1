#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "Item.h"
#include "Block.h"
#include <string>
#include "tool.h"

using namespace game_framework;

Terrian::Terrian(vector<GameObject *> *gameObjects)
{
	this->gameObjects = gameObjects;

	Block *air = new Block();
	air
			->Init({"resources/empty.bmp"})
			->SetDropItems(new vector<ItemTable *>())
			->SetId("air");

	Block *tree = new Block();
	tree
			->Init({"resources/tree_block.bmp"})
			->SetDropItems(
					new vector<ItemTable *>({
							new ItemTable("log", "resources/log.bmp", 1, 4),
							new ItemTable("sapling", "resources/sapling.bmp", 0.5, 1),
					}))
			->SetId("tree_block");

	Block *tree_small = new Block();
	tree_small
			->Init({"resources/tree_small.bmp"})
			->SetDropItems(
					new vector<ItemTable *>({
							new ItemTable("log", "resources/log.bmp", 1, 2),
					}))
			->SetId("tree_small_block");

	Block *stone = new Block();
	stone
			->Init({"resources/stone_block.bmp"})
			->SetDropItems(
					new vector<ItemTable *>({
							new ItemTable("stone", "resources/stone.bmp", 1, 4),
					}))
			->SetId("stone_block");

	Block *coal = new Block();
	coal
			->Init({"resources/coal_block.bmp"})
			->SetDropItems(
					new vector<ItemTable *>({
							new ItemTable("stone", "resources/stone.bmp", 1, 2),
							new ItemTable("coal", "resources/coal.bmp", 1, 4),
					}))
			->SetId("coal_block");

	Block *iron = new Block();
	iron
			->Init({"resources/iron_block.bmp"})
			->SetDropItems(
					new vector<ItemTable *>({
							new ItemTable("iron", "resources/iron.bmp", 1, 4),
					}))
			->SetId("iron_block");

	// slive
	Block *slive = new Block();
	slive
			->Init({"resources/slive_block.bmp"})
			->SetDropItems(
					new vector<ItemTable *>({
							new ItemTable("slive", "resources/slive.bmp", 1, 4),
					}))
			->SetId("slive_block");

	BlocksType = new vector<GameObject*>({
			air,
			tree,
			tree_small,
			stone,
			coal,
			iron,
			slive,
	});


	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			this->terrians[i][j] = 0;
		}
	}

	for (unsigned int i = 0; i < gameObjects->size(); i++)
	{
		if (dynamic_cast<Block *>(gameObjects->at(i)))
		{
			Block *block = dynamic_cast<Block *>(gameObjects->at(i));
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
		return;
	}

	Block *templateBlock = dynamic_cast<Block*>(BlocksType->at(blockIndex));
	Block *newBlock = new Block();

	newBlock
			->SetTerrian(this)
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
	hp = 10;
	onAttackedTick = 0;
	centerX = -9999;
	centerY = -9999;
	dropItems = new vector<ItemTable *>();
}

Block *Block::Init(vector<string> filename)
{
	GameObject::Init(filename);
	return this;
}

void Block::OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects, int mouseX, int mouseY)
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
}

void Block::OnAttacked(GameObject *gameObject)
{
	if (onAttackedTick <= 0)
	{
		hp -= 5;
		onAttackedTick = 60.0f; // 1 second
		centerX = this->GetX();
		centerY = this->GetY();
	}
}

Block *Block::SetDropItems(vector<ItemTable *> *_dropItems)
{
	dropItems = _dropItems;

	return this;
}

Block *game_framework::Block::SetTerrian(Terrian* terrian)
{
	this->terrian = terrian;

	return this;
}

Block* game_framework::Block::SetBlockIndex(int blockIndex)
{
	this->BlockIndex = blockIndex;


	return this;
}

Block *Block::OnDropItem(vector<GameObject *> &gameObjects)
{
	for (unsigned int i = 0; i < dropItems->size(); i++)
	{
		ItemTable *itemTable = dropItems->at(i);

		if (itemTable->rate * 10000 < random(0.0f, 9999.0f))
		{
			continue;
		}

		for (int j = 0; j < itemTable->number; j++)
		{
			Item *item = new Item();
			item->Init({itemTable->path})
					->SetPosition(this->GetX() + random(-16.0f, 16.0f), this->GetY() + random(-16.0f, 16.0f))
					->SetTrigger(true)
					->SetId(itemTable->id)
					->SetActive(true);
			gameObjects.push_back(item);
		}
	}
	return this;
}

void Block::Destroy(vector<GameObject *> &gameObjects)
{
	GameObject::Destroy(gameObjects);

	int x = (int)(this->GetX() / 48.0f);
	int y = (int)(this->GetY() / 48.0f);

	this->terrian->terrians[x][y] = 0;
}
