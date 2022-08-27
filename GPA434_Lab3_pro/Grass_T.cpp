#include "Grass_T.h"

Grass_T::Grass_T(QPointF const & initialPosition, qreal scale, QBrush const & brush, QGraphicsItem * parent)
{
	setPos(initialPosition);
	setScale(scale);
	setBrush(brush);
}
