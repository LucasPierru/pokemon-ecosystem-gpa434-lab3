#ifndef RANDOMPOKEMON_H
#define RANDOMPOKEMON_H

#include <QRandomGenerator>
#include <QGraphicsView>

	double random(qreal maxValue);
	double random(qreal minValue, qreal maxValue);
	QColor randomColor();
	QPointF randomPoint(qreal min, qreal max);

#endif // !RANDOMPOKEMON_H