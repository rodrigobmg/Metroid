﻿#include "LeftCannon.h"

LeftCannon::LeftCannon(int x, int y) : BaseObject(LEFT_CANNON)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOSS_STAGE);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_01"));
	_sprite->setPosition(x, y);

	_spriteIndex = 0;
	_isActive = false;
}

void LeftCannon::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_cannonBulletAppearStopWatch = new StopWatch();
}

void LeftCannon::update(float deltatime)
{
	if (_isActive)
	{
		if (_cannonBulletAppearStopWatch->isStopWatch(CANNON_BULLET_APPEAR_TIME))
		{
			_spriteIndex++;
			if (_spriteIndex >= 8)
				_spriteIndex = 0;

			switch (_spriteIndex)
			{
			case 0:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_01"));
				break;
			case 1:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_02"));
				break;
			case 2:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_03"));
				break;
			case 3:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_04"));
				break;
			case 4:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_05"));
				break;
			case 5:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_04"));
				break;
			case 6:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_03"));
				break;
			case 7:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_02"));
				break;
			default:
				break;
			}

			if (_spriteIndex == 3 || _spriteIndex == 5)
			{
				auto cannonBulletPosition = GVector2(this->getPosition().x, this->getPosition().y);

				CannonBullet* cannonBullet = new CannonBullet(cannonBulletPosition.x, cannonBulletPosition.y, eID::LEFT_CANNON);
				cannonBullet->init();
				QuadTreeNode::getInstance()->insert(cannonBullet);
			}

			_cannonBulletAppearStopWatch->restart();
		}
	}
}

void LeftCannon::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_sprite->render(spriteHandle, viewport);
}

void LeftCannon::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void LeftCannon::active()
{
	_isActive = true;
}

void LeftCannon::deactive()
{
	_isActive = false;
}

bool LeftCannon::isActive()
{
	return _isActive;
}

RECT LeftCannon::getBounding()
{
	RECT bound = _sprite->getBounding();

	bound.left -= 3;
	bound.top -= 3;
	bound.right -= 3;
	bound.bottom -= 3;

	return bound;
}

float LeftCannon::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
