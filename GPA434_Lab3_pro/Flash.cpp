#include "flash.h"



QRectF Flash::boundingRect() const
{
	return mShape.boundingRect();
}

void Flash::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QPixmap lightning;

	lightning.load("lightning.png");

	painter->setPen(Qt::NoPen);
	QRect rect = mShape.boundingRect().toRect();
	painter->drawPixmap(rect, lightning);

}

bool Flash::isDelete()
{
	return mDelete;
}

Flash::Flash(QPointF const & initialPosition, qreal scale, QParameters * parameter, QGraphicsItem * parent)
{
	//changer la forme
	mShape << QPointF(-1, -1)
		<< QPointF(-1, 1)
		<< QPointF(1, 1)
		<< QPointF(1, -1);
	setSize(8);
	resize();
	setPos(initialPosition);
	mParameter = parameter;
	setScale(scale);
}

void Flash::advance(int phase)
{
	if (phase == 0) {

	}
	else if (phase == 1) {
		if (mCurrentTik >= 2)
			mDelete = 1;

		mCurrentTik++;
	}
}
