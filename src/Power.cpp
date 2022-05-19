#include "Power.h"

Power::Power() : m_isTimeBased(false), m_value(0) {

}

int Power::getPower() {
	return m_value;
}

bool Power::timeBased() {
	return m_isTimeBased;
}