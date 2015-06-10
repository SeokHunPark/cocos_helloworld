#include "GameScene.h"
#include "Defines.h"

USING_NS_CC;

Scene* Game::createScene()
{
	auto scene = Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();

	// Sea(background)
	auto spriteSEA = Sprite::create("SEA.png");
	spriteSEA->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.5));
	spriteSEA->setScaleX(winSize.width / spriteSEA->getContentSize().width);
	addChild(spriteSEA, ZORDER_SEA);

	// Dokdo
	auto spriteDOKDO = Sprite::create("DOKDO.png");
	spriteDOKDO->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.25));
	addChild(spriteDOKDO, ZORDER_DOKDO);

	// Cruiser
	schedule(schedule_selector(Game::addCruiser), 5.0f);

	return true;
}

void Game::addCruiser(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	auto spriteCruiser = Sprite::create("cruiser.png");
	float xPos = rand() % (int)winSize.width;
	float yPos = winSize.height * 0.8;
	spriteCruiser->setPosition(Vec2(xPos, yPos));

	addChild(spriteCruiser);
}