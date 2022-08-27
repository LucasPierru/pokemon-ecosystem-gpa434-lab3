#include "Meteo.h"

Meteo::Meteo(size_t meteo, QPointF const & initialPosition, qreal scale, 
	QBrush const & brush, QGraphicsItem * parent)
	: mBrush(brush)
{
	//changer la forme
	mShape << QPointF(-1, -1)
		<< QPointF(-1, 1)
		<< QPointF(1, 1)
		<< QPointF(1, -1);
	mMeteo = meteo;
	setScale(scale);
	setPos(initialPosition);
}

QRectF Meteo::boundingRect() const
{
	return mShape.boundingRect();
}

void Meteo::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QPixmap meteo;
	if (mMeteo == 1) {
		meteo.load("normal");
	}
	else if (mMeteo == 2) {
		meteo.load("lune");
	}
	else if (mMeteo == 3) {
		meteo.load("sun");
	}
	else if (mMeteo == 4) {
		meteo.load("rainy");
	}

	painter->setPen(Qt::NoPen);
	QRect rect = mShape.boundingRect().toRect();
	painter->drawPixmap(rect, meteo);

}

void Meteo::advance(int phase)
{
	if (phase == 0) {

	}
	else if (phase == 1) {
	}
}