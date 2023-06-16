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
		->SetHp(24) //24
		->Init({ "resources/tree_block.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("log", "resources/log.bmp", 1, 4),
					new ItemTable("sapling", "resources/sapling.bmp", 1, 1),
					new ItemTable("sapling", "resources/sapling.bmp", 0.5, 1),
					new ItemTable("apple", "resources/apple.bmp", 0.3f, 1),
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

	// water
	Block* water = new Block();
	water
		->SetHp(999999)
		->SetIndestructible(true)
		->Init({ "resources/water_block.bmp" })
		->SetId("water");

	// sand
	Block* sand = new Block();
	sand
		->SetHp(24) //24
		->Init({ "resources/sand.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("sand", "resources/sand.bmp", 1, 4),
				}))
				->SetId("sand_block");

	// water_purifier
	Block* water_purifier = new Block();
	water_purifier
		->SetHp(4)
		->Init({ "resources/water_purifier_block.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("water_purifier", "resources/water_purifier.bmp", 1, 1),
				}))
				->SetId("water_purifier_block");

	// campfire
	Block* campfire = new Block();
	campfire
		->SetAnimation(500, false)
		->SetHp(4)
		->Init({ "resources/campfire_0_block.bmp", "resources/campfire_1_block.bmp" })
		->SetDropItems(
			new vector<ItemTable*>({
					new ItemTable("campfire", "resources/campfire.bmp", 1, 1),
				}))
				->SetId("campfire_block");

	BlocksType = new vector<GameObject*>({
			air, // 0
			tree, // 1
			tree_small, // 2
			stone, // 3
			coal, // 4
			iron, // 5
			slive, // 6
			craft_table, // 7
			water, // 8
			sand, // 9
			water_purifier, // 10
			campfire, // 11
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

Terrian::~Terrian() {

	for (auto item : *this->BlocksType) {
		delete item;
	}
	delete this->BlocksType;
}

bool Terrian::IsBlock(float x, float y)
{
	if (this->terrians[(int)(x / 48.0f)][(int)(y / 48.0f)] != 0)
	{
		return true;
	}
	// water block is 3x3
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			const int rawX = (int)(x / 48.0f) + i;
			const int rawy = (int)(y / 48.0f) + j;
			const int above0X = rawX < 0 ? 0 : rawX;
			const int above0Y = rawy < 0 ? 0 : rawy;
			const int x = above0X > 21 ? 21 : above0X;
			const int y = above0Y > 21 ? 21 : above0Y;
			if (this->terrians[x][y] == 8)
			{
				return true;
			}
		}
	}

	return false;
}


bool Terrian::IsBehindWater(float x, float y)
{
	for (unsigned int i = 0; i < gameObjects->size(); i++)
	{
		if (!dynamic_cast<Block*>(gameObjects->at(i)))
		{
			continue;
		}

		Block* block = dynamic_cast<Block*>(gameObjects->at(i));
		if (block->BlockIndex != 8)
		{
			continue;
		}

		const float blockX = block->GetX();
		const float blockY = block->GetY();

		if (blockX - 2 * 48 > x || blockX + 2 * 48 < x || blockY - 2 * 48 > y || blockY + 2 * 48 < y)
		{
			continue;
		}

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
		->SetAnimation(templateBlock->GetAnimationTime(), templateBlock->GetAnimationNoLoop())
		->SetIndestructible(templateBlock->IsIndestructible())
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
	if (indestructible)
	{
		return;
	}
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
	if (indestructible)
	{
		return;
	}
	if (onAttackedTick > 0)
		return;

	float damage = 1;
	if (dynamic_cast<MainCharacter*>(gameObject))
	{
		MainCharacter* player = dynamic_cast<MainCharacter*>(gameObject);
		string useTool = player->GetInventory(player->GetMainHandSelectedIndex())->id;

		damage = player->attack;
		if ((BlockIndex == 1 || BlockIndex == 2)) { // tree
			if (useTool == "wood_axe") {
				damage = 2 * player->attack;
			}

			if (useTool == "stone_axe") {
				damage = 3 * player->attack;
			}

			if (useTool == "iron_axe") {
				damage = 4 * player->attack;
			}
		}
		if (BlockIndex == 3 || BlockIndex == 4 || BlockIndex == 5 || BlockIndex == 6 || BlockIndex == 9) { // stone
			if (useTool == "wood_pickaxe") {
				damage = 2 * player->attack;
			}

			if (useTool == "stone_pickaxe") {
				damage = 3 * player->attack;
			}

			if (useTool == "iron_pickaxe") {
				damage = 4 * player->attack;
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


	int randNum = rand() % 5;

	switch (randNum) {
	case 0:
		CAudio::Instance()->Play(1011, false);
		break;
	case 1:
		CAudio::Instance()->Play(1012, false);
		break;
	case 2:
		CAudio::Instance()->Play(1013, false);
		break;
	case 3:
		CAudio::Instance()->Play(1014, false);
		break;
	case 4:
		CAudio::Instance()->Play(1015, false);
		break;
	}
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

	// water_purifier
	if (this->BlockIndex == 10) {
		character->SetUseWaterPurifier(true);
	}

	// campfire
	if (this->BlockIndex == 11) {
		character->OnBarbecue(gameObjects);
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

Block* game_framework::Block::SetAnimation(int time, boolean noloop)
{
	this->bitmap.SetAnimation(time, noloop);
	this->animationNoLoop = noloop;
	this->animationTime = time;
	return this;
}

int game_framework::Block::GetAnimationTime()
{
	return this->animationTime;
}

bool game_framework::Block::GetAnimationNoLoop()
{
	return this->animationNoLoop;
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
	int x = (int)(this->GetX() / 48.0f);
	int y = (int)(this->GetY() / 48.0f);

	this->terrian->terrians[x][y] = 0;

	GameObject::Destroy(gameObjects);
}


boolean Block::IsIndestructible() {
	return indestructible;
}

Block* Block::SetIndestructible(boolean _indestructible) {
	this->indestructible = _indestructible;
	return this;
}