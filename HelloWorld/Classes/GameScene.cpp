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

	// Surface SpriteBatchNode
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Surface.plist");
	auto spriteBatchNodeSurface = SpriteBatchNode::create("Surface.png");
	addChild(spriteBatchNodeSurface, ZORDER_SPRITE_BATCH_NODE_SURFACE, TAG_SPRITE_BATCH_NODE_SURFACE);

	// Dokdo
	auto spriteDOKDO = Sprite::createWithSpriteFrameName("DOKDO.png");
	spriteDOKDO->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.25));
	spriteBatchNodeSurface->addChild(spriteDOKDO, ZORDER_DOKDO);

	// Rotate Radar
	auto spriteRotateRadar = Sprite::createWithSpriteFrameName("radar_01.png");
	spriteRotateRadar->setAnchorPoint(Vec2(1, 0));
	spriteRotateRadar->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.25));

	float scale = winSize.height / spriteRotateRadar->getContentSize().height;
	spriteRotateRadar->setScale(scale);
	spriteBatchNodeSurface->addChild(spriteRotateRadar, ZORDER_RADAR);

	auto rotateBy = RotateBy::create(10, 360);
	auto repeatForever = RepeatForever::create(rotateBy);
	spriteRotateRadar->runAction(repeatForever);

	// Scale Radar
	auto spriteScaleRadar = Sprite::createWithSpriteFrameName("radar_00.png");
	spriteScaleRadar->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.25));
	spriteScaleRadar->setScale(0);
	spriteBatchNodeSurface->addChild(spriteScaleRadar, ZORDER_RADAR);

	scale = winSize.height / spriteScaleRadar->getContentSize().height;
	auto scaleTo = ScaleTo::create(4, scale);	
	auto scaleToZero = ScaleTo::create(0, 0);
	auto sequenceScale = Sequence::create(scaleTo, scaleToZero, NULL);
	auto scaleForever = RepeatForever::create(sequenceScale);
	spriteScaleRadar->runAction(scaleForever);

	// Fade Radar
	auto spriteFadeRadar = Sprite::createWithSpriteFrameName("radar_00.png");
	spriteFadeRadar->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.25));
	spriteFadeRadar->setScale(scale);
	spriteBatchNodeSurface->addChild(spriteFadeRadar);

	auto fadeOut = FadeOut::create(4);
	auto fadeIn = FadeIn::create(0);
	auto sequenceFade = Sequence::create(fadeOut, fadeIn, NULL);
	auto fadeForever = RepeatForever::create(sequenceFade);
	spriteFadeRadar->runAction(fadeForever);

	// Explosion
	/*auto spriteExplosion = Sprite::create("explosion_effect_18.png");
	spriteExplosion->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.5));
	spriteExplosion->setScale(winSize.width / spriteExplosion->getContentSize().width);
	addChild(spriteExplosion, ZORDER_EXPLOSION_S);
	
	BlendFunc bfLinearDodge = { GL_ONE, GL_ONE };
	spriteExplosion->setBlendFunc(bfLinearDodge);*/

	// Schedule
	schedule(schedule_selector(Game::addCruiser), 5.0f);
	schedule(schedule_selector(Game::addDestroyer), 3.0f);
	schedule(schedule_selector(Game::shootFromDokdo), 0.6f);
	schedule(schedule_selector(Game::dropNuclearBomb), 4.0f);
	schedule(schedule_selector(Game::addCloud), 8.0);

	return true;
}

void Game::addCruiser(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	auto spriteBatchNodeSurface = (SpriteBatchNode*)getChildByTag(TAG_SPRITE_BATCH_NODE_SURFACE);

	auto spriteCruiser = Sprite::createWithSpriteFrameName("cruiser.png");
	float xPos = rand() % (int)winSize.width;
	float yPos = winSize.height;
	spriteCruiser->setPosition(Vec2(xPos, yPos));
	spriteCruiser->setAnchorPoint(Vec2(0.5, 0));

	spriteBatchNodeSurface->addChild(spriteCruiser);

	/*auto moveTo = MoveTo::create(10.f, Vec2(winSize.width * 0.5, winSize.height * 0.25));
	spriteCruiser->runAction(moveTo);*/

	Vec2 position = spriteCruiser->getPosition();
	float xDistance = (winSize.width * 0.5) - position.x;

	ccBezierConfig bezierConfig;
	bezierConfig.controlPoint_1 = Vec2(position.x, winSize.height * 0.6f);
	bezierConfig.controlPoint_2 = Vec2(position.x + (xDistance / 3.0f), winSize.height * 0.4f);
	bezierConfig.endPosition = Vec2(winSize.width * 0.5, winSize.height * 0.25);

	auto bezierTo = BezierTo::create(10.f, bezierConfig);
	
	auto callfunc = CallFuncN::create(CC_CALLBACK_1(Game::selfRemover, this));
	auto sequence = Sequence::create(bezierTo, callfunc, NULL);
	spriteCruiser->runAction(sequence);
}

void Game::addDestroyer(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	auto spriteBatchNodeSurface = (SpriteBatchNode*)getChildByTag(TAG_SPRITE_BATCH_NODE_SURFACE);

	auto spriteDestroyer = Sprite::createWithSpriteFrameName("destroyer.png");
	float xPos = rand() % (int)winSize.width;
	float yPos = winSize.height;
	spriteDestroyer->setPosition(Vec2(xPos, yPos));
	spriteDestroyer->setAnchorPoint(Vec2(0.5, 0));

	spriteBatchNodeSurface->addChild(spriteDestroyer, ZORDER_SHIP);

	auto moveTo = MoveTo::create(7.f, Vec2(winSize.width * 0.5, winSize.height * 0.25));
	
	auto callfunc = CallFuncN::create(CC_CALLBACK_1(Game::selfRemover, this));
	auto sequence = Sequence::create(moveTo, callfunc, NULL);
	spriteDestroyer->runAction(sequence);
}
void Game::addCloud(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	int cloudNum = rand() % 3;
	char szFileName[16] = { 0, };
	sprintf(szFileName, "cloud_%02d.png", cloudNum);
	auto spriteCloud = Sprite::create(szFileName);

	float frand = ((rand() % 4) + 6) / 10.f;
	float scale = (winSize.width * frand) / spriteCloud->getContentSize().width;
	spriteCloud->setScale(scale);
	spriteCloud->setAnchorPoint(Vec2(1, 0.5));

	float xPos = 0;
	float yPos = (rand() % (int)winSize.height);
	spriteCloud->setPosition(Vec2(xPos, yPos));

	BlendFunc bf = { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA };
	spriteCloud->setBlendFunc(bf);

	float moveTime = 8 + (rand() % 3);
	auto moveBy = MoveBy::create(moveTime, Vec2(winSize.width + spriteCloud->getBoundingBox().size.width, 0));

	auto callfunc = CallFuncN::create(CC_CALLBACK_1(Game::selfRemover, this));

	auto sequence = Sequence::create(moveBy, callfunc, NULL);

	spriteCloud->runAction(sequence);

	addChild(spriteCloud, ZORDER_CLOUD);
}

void Game::shootFromDokdo(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	auto spriteBullet = Sprite::create("bullet.png");
	float scale = (winSize.height / 30) / spriteBullet->getContentSize().height;
	spriteBullet->setScale(scale);
	spriteBullet->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.25));
	spriteBullet->setRotation(180);

	addChild(spriteBullet, ZORDER_BULLET);

	auto moveBy = MoveBy::create(1.5f, Vec2(0, winSize.height * 0.5));
	auto actionInterval = EaseOut::create(moveBy, 1.8f);
	
	auto callfunc = CallFuncN::create(CC_CALLBACK_1(Game::selfRemover, this));
	auto sequence = Sequence::create(actionInterval, callfunc, NULL);
	spriteBullet->runAction(sequence);
}

void Game::dropNuclearBomb(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	auto spriteBomb = Sprite::create("MISSILE.png");
	float bombHeight = spriteBomb->getContentSize().height;
	float beginScale = (winSize.height / 6) / bombHeight;
	float finishScale = (winSize.height / 40) / bombHeight;

	spriteBomb->setScale(beginScale);
	float visibleHeight = spriteBomb->getBoundingBox().size.height;
	spriteBomb->setPosition(Vec2(winSize.width * 0.5, 0 - (visibleHeight * 0.5)));
	addChild(spriteBomb, ZORDER_NUCLEAR);

	auto moveBy = MoveBy::create(1.5f, Vec2(0, winSize.height * 0.66));
	auto actionInterval = EaseOut::create(moveBy, 1.8f);
	auto scaleTo = ScaleTo::create(1.5f, finishScale);
	auto spawn = Spawn::create(actionInterval, scaleTo, NULL);

	auto callfunc = CallFuncN::create(CC_CALLBACK_1(Game::selfRemover, this));
	auto sequence = Sequence::create(spawn, callfunc, NULL);
	spriteBomb->runAction(sequence);
}

void Game::selfRemover(Node* sender)
{
	sender->removeFromParentAndCleanup(true);
}