#include "Weapon.h"

Weapon::Weapon() : m_shooting(false), m_type(0) {
	m_isTimeBased = false;
	m_value = 0;
}

void Weapon::shoot() {

}

bool Weapon::checkHit() {
	return false;
}