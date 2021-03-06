﻿#include "Zoomer.h"
#include "SoundManager.h"

Zoomer::Zoomer(int x, int y) : BaseObject(ZOOMER)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "orange_zoomer_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.2f);
	_animation->addFrameRect(eID::ENEMY, "orange_zoomer_01", "orange_zoomer_02", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	// Ban đầu cho Zoomer đi sang phải
	_velocity = GVector2(ZOOMER_MOVE_SPEED, -30);

	_hitPoint = 2;
	_isActive = false;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;

	movement->setVelocity(_velocity);
}

void Zoomer::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHitStopWatch = false;

	_preDirection = eDirection::NONE;
	_preWall = nullptr;
}

void Zoomer::update(float deltatime)
{
	if (_hitPoint > 0)
	{
		_animation->update(deltatime);

		if (_startHitStopWatch)
		{
			// Nếu đang trong thời gian protect thì deactive
			this->deactive();

			// Check để sau khi hết khoảng thời gian protect thì tắt hitStopWatch
			// Active lại
			if (_hitStopWatch->isStopWatch(400))
			{
				_startHitStopWatch = false;
				_hitStopWatch->restart();
				// Do đã có điều kiện active bên Player nên không cần active lại
				this->active();
			}
		}

		for (auto it = _componentList.begin(); it != _componentList.end(); it++)
		{
			it->second->update(deltatime);
		}
	}
	else
	{
		_effect->setPosition(this->getPosition());
		_effectAnimation->update(deltatime);

		if (_effectStopWatch->isStopWatch(200))
		{
			SoundManager::getInstance()->play(eSoundID::EXPLOSION_SOUND);

			this->setStatus(DESTROY);

			BaseObject* item = nullptr;
			srand(time(0));
			auto random = rand() % 10;

			if (random < 5)
				item = new EnergyBall(this->getPositionX(), this->getPositionY());

			if (item != nullptr)
			{
				item->init();
				QuadTreeNode::getInstance()->insert(item);
			}
		}
	}
}

void Zoomer::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void Zoomer::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Zoomer::wasHit(int hitPoint)
{
	// Nếu không trong khoảng thời gian protect thì trừ HP và bật hitStopWatch
	// Nếu đang trong khoảng thời gian protect thì không trừ HP
	if (!_startHitStopWatch)
	{
		_hitPoint -= hitPoint;
		_hitStopWatch->restart();
		_startHitStopWatch = true;
	}

	if (_hitPoint <= 0)
	{
		auto move = (Movement*)this->_componentList["Movement"];
		move->setVelocity(GVector2(0, 0));
	}
}

bool Zoomer::isDead()
{
	return (_hitPoint <= 0);
}

void Zoomer::active()
{
	_isActive = true;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(_velocity);
}

void Zoomer::deactive()
{
	_isActive = false;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(GVector2(0, 0));
}

bool Zoomer::isActive()
{
	return _isActive;
}

float Zoomer::checkCollision(BaseObject* object, float dt)
{
	auto objectId = object->getId();
	if (objectId == WALL || objectId == BREAKABLE_BLUE_WALL || objectId == BREAKABLE_RED_WALL || objectId == BLUE_DOOR || objectId == RED_DOOR)
	{
		auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
		eDirection direction;
		if (collisionBody->checkCollision(object, direction, dt, true))
		{
			if (direction == TOP) // Va chạm Wall TOP thì tiếp tục đi sang phải
			{
				_velocity = GVector2(ZOOMER_MOVE_SPEED, -30);
				_sprite->setRotate(0);
				_preDirection = eDirection::TOP;
			}
			else if (direction == RIGHT) // Va chạm Wall RIGHT thì tiếp tục đi xuống
			{
				_velocity = GVector2(-30, -ZOOMER_MOVE_SPEED);
				_sprite->setRotate(90);
				_preDirection = eDirection::RIGHT;
			}
			else if (direction == BOTTOM) // Va chạm Wall BOTTOM thì tiếp tục đi sang trái
			{
				_velocity = GVector2(-ZOOMER_MOVE_SPEED, 30);
				_sprite->setRotate(180);
				_preDirection = eDirection::BOTTOM;
			}
			else if (direction == LEFT) // Va chạm Wall LEFT thì tiếp tục đi lên
			{
				_velocity = GVector2(30, ZOOMER_MOVE_SPEED);
				_sprite->setRotate(270);
				_preDirection = eDirection::LEFT;
			}

			auto movement = (Movement*)this->_componentList["Movement"];
			movement->setVelocity(_velocity);

			_preWall = object;
			return 1.0f;
		}
		else if (object == _preWall)
		{
			if (_preDirection == TOP) // Va chạm Wall trước đó TOP thì đi xuống
			{
				auto movement = (Movement*)this->_componentList["Movement"];
				movement->setVelocity(GVector2(-30, -ZOOMER_MOVE_SPEED));
			}
			else if (_preDirection == RIGHT) // Va chạm Wall trước đó LEFT thì đi sang trái
			{
				auto movement = (Movement*)this->_componentList["Movement"];
				movement->setVelocity(GVector2(-ZOOMER_MOVE_SPEED, 30));
			}
			else if (_preDirection == BOTTOM) // Va chạm Wall trước đó BOTTOM thì đi lên
			{
				auto movement = (Movement*)this->_componentList["Movement"];
				movement->setVelocity(GVector2(30, ZOOMER_MOVE_SPEED));
			}
			else if (_preDirection == LEFT) // Va chạm Wall trước đó RIGHT thì sang phải
			{
				auto movement = (Movement*)this->_componentList["Movement"];
				movement->setVelocity(GVector2(ZOOMER_MOVE_SPEED, -30));
			}
		}
	}
	return 0;
}
