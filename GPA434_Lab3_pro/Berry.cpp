#include "Berry.h"

Berry::Berry(QPointF const & initialPosition, qreal scale, QBrush const & brush, QGraphicsItem * parent)
	: mBrush(brush)
{
	mShape << QPointF(-1, 1)
		<< QPointF(1, 1)
		<< QPointF(1, -1)
		<< QPointF(-1, -1);
	setEaten(0);
	setPos(initialPosition);
	setScale(scale);
}

void Berry::setEaten(bool eat)
{
	mEaten = eat;
}

bool Berry::getEaten()
{
	return mEaten;
}

double Berry::getRadius()
{
	return mRadius;
}

QRectF Berry::boundingRect() const
{
	return mShape.boundingRect();
}

void Berry::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QPixmap Lum("Lum_Berry.png");
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	QRect rect = mShape.boundingRect().toRect();
	painter->drawPixmap(rect, Lum);
}

void Berry::advance(int phase)
{
	for (QGraphicsItem * item : scene()->items()) {
		Pokemon* pokemon{ dynamic_cast<Pokemon *>(item) };
		if (pokemon != nullptr && pokemon->distance(pos()) < mRadius + pokemon->getSize()) {
			setEaten(1);
		}
	}
}