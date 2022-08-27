#include "RandomPokemon.h"


double random(qreal maxValue)
{
	return QRandomGenerator::global()->bounded(maxValue);
}

double random(qreal minValue, qreal maxValue)
{
	return random(maxValue - minValue) + minValue;
}

QColor randomColor()
{
	return QColor::fromRgb(QRandomGenerator::global()->generate());
}

QPointF randomPoint(qreal min, qreal max)
{
	return QPointF(random(min, max), random(min, max));
}

