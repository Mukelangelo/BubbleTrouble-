#include "Power.h"

Power::Power() : m_isTimeBased(false), m_value(0), m_isActive(false) 
{

}

int Power::getPower() 
{
	return m_value;
}

bool Power::timeBased() 
{
	return m_isTimeBased;
}

bool Power::getActiveStatus() 
{
	return m_isActive;
}

void Power::setActive()
{
	m_isActive = true;
}