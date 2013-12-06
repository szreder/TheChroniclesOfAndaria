#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Gui/CustomWidgets/BarWidget.h"

class HealthBar : public BarWidget {

public:
	HealthBar(int maxHealth, QWidget *parent = nullptr);

	int health() const;
	void setHealth(int health);

private:
	QColor valueToColor(int value);
};

#endif
