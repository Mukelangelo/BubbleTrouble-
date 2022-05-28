#pragma once

#include "macros.h"

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	bool getSplit(int &index);

private:	
	struct ballToSplitInfo
	{
		bool m_split = false;
		int m_index = -1;
	};

	ballToSplitInfo m_splitInfo;
};