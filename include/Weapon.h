#pragma once

#include "Power.h"

class Weapon : public Power {
public:
	Weapon();

	void shoot();
	bool checkHit(); // do we need this?

private:
	int m_type;
	bool m_shooting;
};