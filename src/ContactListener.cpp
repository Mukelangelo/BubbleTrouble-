#include "ContactListener.h"
#include <iostream>

void ContactListener::BeginContact(b2Contact* contact)
{
	b2Filter fa = contact->GetFixtureA()->GetFilterData();
	b2Filter fb = contact->GetFixtureB()->GetFilterData();

	if (fb.categoryBits == entity::BALL)
	{
		if (fa.categoryBits == entity::WEAPON)
		{
			m_splitInfo.m_index = fb.groupIndex;
			m_splitInfo.m_split = true;
		}
		else if (fa.categoryBits == entity::PLAYER)
		{
			m_playerHit = true;
		}
	}

	if (fb.categoryBits == entity::PLAYER)
	{
		if (fa.categoryBits == entity::WALL && (fa.groupIndex == -1 || fa.groupIndex == -2))
		{
			m_blockPlayer = true;
		}
	}
	if (fa.categoryBits == entity::PLAYER)
	{
		if (fb.categoryBits == entity::GIFT)
		{
			m_giftPlayer = true;
		}
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	b2Filter fa = contact->GetFixtureA()->GetFilterData();
	b2Filter fb = contact->GetFixtureB()->GetFilterData();

	if (fb.categoryBits == entity::PLAYER)
	{
		if (fa.categoryBits == entity::WALL && (fa.groupIndex == -1 || fa.groupIndex == -2))
		{
			m_blockPlayer = false;
		}
		if (fb.categoryBits == entity::GIFT)
			m_giftPlayer = false;
	}
}

bool ContactListener::getSplit(int& index)
{
	index = m_splitInfo.m_index;
	if (m_splitInfo.m_split)
	{
		m_splitInfo.m_split = false;
		return true;
	}
	return false;
}

bool ContactListener::getPlayerHit() const
{
	return m_playerHit;
}

bool ContactListener::isPlayerAtBorder()
{
	return m_blockPlayer;
}

bool ContactListener::getCollisionGift() const
{
	return m_giftPlayer;
}