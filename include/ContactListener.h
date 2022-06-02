#pragma once

#include "macros.h"

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	bool getSplit(int &index);
	bool getPlayerHit() const;
	bool isPlayerAtBorder();
	void restartFlags();

private:	
	struct ballToSplitInfo
	{
		bool m_split = false;
		int m_index = -1;
	};

	ballToSplitInfo m_splitInfo;
	bool m_playerHit = false;
	bool m_blockPlayer = false;
};