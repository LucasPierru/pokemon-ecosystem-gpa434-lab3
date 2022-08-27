#include "Water_T.h"

Water_T::Water_T(QPointF const & initialPosition, qreal scale, QBrush const & brush, QGraphicsItem * parent)
{	
	setPos(initialPosition);
	setScale(scale);
	setBrush(brush);
}