#include "Territory.h"


Territory::Territory(QPointF const & initialPosition, qreal scale, QBrush const & brush, QGraphicsItem * parent)
	: mBrush(brush)
{
	mShape << QPointF(-1, 1)
		<< QPointF(1, 1)
		<< QPointF(1, -1)
		<< QPointF(-1, -1);
	setPos(initialPosition);
	setScale(scale);
}

qreal Territory::getBerry(qreal percentage, qreal size)
{
	return (percentage / 100) * size*sizeAdjust;
}

void Territory::setBrush(QBrush const & brush)
{
	mBrush = brush;
}

double Territory::getRadius()
{
	return mRadius;
}

QRectF Territory::boundingRect() const
{
	return mShape.boundingRect();
}

void Territory::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setOpacity(0.2);
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawEllipse(mShape.boundingRect());
}