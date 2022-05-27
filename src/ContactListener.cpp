#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	b2Filter fa = contact->GetFixtureA()->GetFilterData();
	b2Filter fb = contact->GetFixtureB()->GetFilterData();

	// all ball contacts
	if (fb.categoryBits == _entity::BALL)
	{
		if (fa.categoryBits == _entity::WEAPON)
		{
			m_splitInfo.m_index = fb.groupIndex;
			m_splitInfo.m_split = true;
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