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
	schedule(schedule_selector(Game::addDestroyer), 3.0f);

	return true;
}

void Game::addCruiser(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	auto spriteCruiser = Sprite::create("cruiser.png");
	float xPos = rand() % (int)winSize.width;
	float yPos = winSize.height;
	spriteCruiser->setPosition(Vec2(xPos, yPos));
	spriteCruiser->setAnchorPoint(Vec2(0.5, 0));

	addChild(spriteCruiser);

	/*auto moveTo = MoveTo::create(10.f, Vec2(winSize.width * 0.5, winSize.height * 0.25));
	spriteCruiser->runAction(moveTo);*/

	Vec2 position = spriteCruiser->getPosition();
	float xDistance = (winSize.width * 0.5) - position.x;

	ccBezierConfig bezierConfig;
	bezierConfig.controlPoint_1 = Vec2(position.x, winSize.height * 0.6f);
	bezierConfig.controlPoint_2 = Vec2(position.x + (xDistance * 0.33), winSize.height * 0.4f);
	bezierConfig.endPosition = Vec2(winSize.width * 0.5, winSize.height * 0.25);

	auto bezierTo = BezierTo::create(10.f, bezierConfig);
	spriteCruiser->runAction(bezierTo);
}

void Game::addDestroyer(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	auto spriteDestroyer = Sprite::create("destroyer.png");
	float xPos = rand() % (int)winSize.width;
	float yPos = winSize.height;
	spriteDestroyer->setPosition(Vec2(xPos, yPos));
	spriteDestroyer->setAnchorPoint(Vec2(0.5, 0));

	addChild(spriteDestroyer, ZORDER_SHIP);

	auto moveTo = MoveTo::create(7.f, Vec2(winSize.width * 0.5, winSize.height * 0.25));
	spriteDestroyer->runAction(moveTo);
}