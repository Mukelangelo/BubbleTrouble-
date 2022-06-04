#include "ContactListener.h"
#include <iostream>

void ContactListener::BeginContact(b2Contact* contact)
{
	b2Filter fa = contact->GetFixtureA()->GetFilterData();
	b2Filter fb = contact->GetFixtureB()->GetFilterData();

	if (fb.categoryBits == _entity::BALL)
	{
		if (fa.categoryBits == _entity::WEAPON)
		{
			m_splitInfo.m_index = fb.groupIndex;
			m_splitInfo.m_split = true;
		}
		else if (fa.categoryBits == _entity::PLAYER)
		{
			m_playerHit = true;
		}
	}

	if (fb.categoryBits == _entity::PLAYER || fa.categoryBits == _entity::PLAYER)
	{
		if ((fa.categoryBits == _entity::WALL && (fa.groupIndex == -1 || fa.groupIndex == -2)) ||
			(fb.categoryBits == _entity::WALL && (fb.groupIndex == -1 || fb.groupIndex == -2)))
		{
			m_blockPlayer = true;
		}
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	b2Filter fa = contact->GetFixtureA()->GetFilterData();
	b2Filter fb = contact->GetFixtureB()->GetFilterData();

	if (fb.categoryBits == _entity::PLAYER || fa.categoryBits == _entity::PLAYER)
	{
		if ((fa.categoryBits == _entity::WALL && (fa.groupIndex == -1 || fa.groupIndex == -2)) ||
			(fb.categoryBits == _entity::WALL && (fb.groupIndex == -1 || fb.groupIndex == -2)))
		{
			m_blockPlayer = false;
		}
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

void ContactListener::restartFlags()
{
	m_playerHit = false;
	m_blockPlayer = false;
}