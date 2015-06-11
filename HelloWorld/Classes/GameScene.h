#pragma once

#include "cocos2d.h"

class Game : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Game);

	void addCruiser(float dt);
	void addDestroyer(float dt);

	void shootFromDokdo(float dt);
};