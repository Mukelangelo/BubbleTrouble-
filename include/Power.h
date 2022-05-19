#pragma once

class Power {
public:
	Power();

	int getPower();
	bool timeBased();

protected:
	bool m_isTimeBased;
	int m_value;
};