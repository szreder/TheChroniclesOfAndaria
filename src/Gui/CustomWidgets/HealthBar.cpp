#include "Gui/CustomWidgets/HealthBar.h"

HealthBar::HealthBar(int maxHealth, QWidget *parent)
	: BarWidget(0, maxHealth, parent)
{
	addLayer(maxHealth, valueToColor(maxHealth));
	setHealth(maxHealth);
}

int HealthBar::health() const
{
	return operator[](0)->value();
}

void HealthBar::setHealth(int health)
{
	operator[](0)->setColor(valueToColor(health));
	operator[](0)->setValue(health);
	setToolTip(tr("Hit points: %1 / %2").arg(health).arg(maxValue()));
}

QColor HealthBar::valueToColor(int value)
{
	static const QVector <QPair <int, QColor> > colors {
		{30, Qt::darkGreen},
		{15, Qt::yellow},
		{ 5, Qt::red},
	};

	for (const QPair <int, QColor> &p : colors)
		if (value >= p.first)
			return p.second;

	return Qt::darkRed;
}
