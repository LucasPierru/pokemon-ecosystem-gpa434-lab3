#include "HealthBar.h"

HealthBar::HealthBar(bool fill, QPointF const & initialPosition, qreal scale,
	QParameters *parameter, QGraphicsItem * parent)
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
	mFill = fill;
}

void HealthBar::setTarget(QPointF target)
{
	mTarget = target;
}

QRectF HealthBar::boundingRect() const
{
	return mShape.boundingRect();
}

void HealthBar::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QPixmap HpBar;
	if (mFill) {
		HpBar.load("emptyHP.png");
	}
	else {
		HpBar.load("fullHP.png");
	}
	painter->setPen(Qt::NoPen);
	QRect rect = mShape.boundingRect().toRect();
	painter->drawPixmap(rect, HpBar);
}