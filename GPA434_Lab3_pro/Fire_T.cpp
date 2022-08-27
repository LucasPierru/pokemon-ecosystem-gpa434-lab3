#include "Fire_T.h"

Fire_T::Fire_T(QPointF const & initialPosition, qreal scale, QBrush const & brush, QGraphicsItem * parent)
{
	setPos(initialPosition);
	setScale(scale);
	setBrush(brush);
}
