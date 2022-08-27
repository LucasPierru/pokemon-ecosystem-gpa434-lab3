#include "QDynamicItem.h"

QDynamicItem::QDynamicItem(QPointF const & initialPosition, size_t intelligence, 
	qreal initialSpeed, qreal scale, QGraphicsItem * parent)
	: QGraphicsPixmapItem(parent),
	mSize(scale),
	mSpeed{ initialSpeed }
{
	setPos(initialPosition);
	setScale(scale);
}

void QDynamicItem::setSpeed(qreal speed)
{
	mSpeed = speed;
}

void QDynamicItem::setSize(qreal size)
{
	mSize = size;
}

void QDynamicItem::resize()
{
	setScale(mSize);
}

qreal QDynamicItem::getSize()
{
	return mSize;
}

QRectF QDynamicItem::boundingRect() const
{
	return mShape.boundingRect();
}

void QDynamicItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->drawPolygon(mShape);
}

double QDynamicItem::normalizeAngle(double radians) // angle is in interval : [0, 2pi[
{
	if (radians >= 2.0 * M_PI) {
		return fmod(radians, 2.0 * M_PI);
	}
	else if (radians < 0.0) {
		return 2.0 * M_PI - fmod(-radians, 2.0 * M_PI);
	}
	else {
		return radians;
	}
}

void QDynamicItem::advance(int phase)
{
	if (phase == 0) {
		// do nothing
	}
	else if (phase == 1) {
		//setTarget(findClosest());
		QGraphicsItem * target{ nullptr };
		double dist2{ 9e9 };
		QList<QGraphicsItem*> items{ scene()->items() };
		for (auto i : items) {
			if (i != this) {
				double d2{ (i->pos().x() - pos().x()) * (i->pos().x() - pos().x()) + (i->pos().y() - pos().y()) * (i->pos().y() - pos().y()) };
				if (d2 < dist2) {
					dist2 = d2;
					target = i;
				}
			}
		}
		if (target) {
			double maxDeltaRotation{ 0.32 };
			qreal rotateRad{ normalizeAngle(qDegreesToRadians(rotation())) };
			qreal targetRad{ normalizeAngle(atan2(target->pos().y() - y(), target->pos().x() - x())) };
			qreal deltaRotationRadians{ targetRad - rotateRad };
			if (deltaRotationRadians > M_PI) deltaRotationRadians = deltaRotationRadians - 2.0 * M_PI;
			if (deltaRotationRadians < -M_PI) deltaRotationRadians = 2.0 * M_PI + deltaRotationRadians;

			if (deltaRotationRadians > maxDeltaRotation) {
				deltaRotationRadians = maxDeltaRotation;
			}
			else if (deltaRotationRadians < -maxDeltaRotation) {
				deltaRotationRadians = -maxDeltaRotation;
			}
			qreal newDir{ rotateRad + deltaRotationRadians };

			// D�termine la nouvelle position selon la nouvelle orientation et la vitesse
			QPointF newPosition(pos() + QPointF(qCos(newDir), qSin(newDir)) * mSpeed);

			// Applique la nouvelle orientation et la nouvelle position
			setRotation(qRadiansToDegrees(newDir));
			setPos(newPosition);
		}
	}

	if (phase == 0) {
		// do nothing
	}
	else if (phase == 1) {
		static constexpr const qreal maxDeltaOrientation{ 12.5 }; // in �
		// D�termine la nouvelle orientation selon une variation al�atoire dans l'intervalle [-maxDeltaOrientation, maxDeltaOrientation] => � 12.5�
		qreal newOrientationDegrees{ rotation() + QRandomGenerator::global()->bounded(2.0 * maxDeltaOrientation) - maxDeltaOrientation };
		qreal newOrientationRadians{ qDegreesToRadians(newOrientationDegrees) };

		// D�termine la nouvelle position selon la nouvelle orientation et la vitesse
		QPointF newPosition(pos() + QPointF(qCos(newOrientationRadians), qSin(newOrientationRadians)) * mSpeed);
		// Si la nouvelle position est � l'ext�rieur de la sc�ne, la nouvelle position est t�l�port�e � la r�gion oppos�e de la sc�ne

		// Applique la nouvelle orientation et la nouvelle position
		setRotation(field(newPosition, newOrientationDegrees));

		setPos(newPosition);
	}
}

qreal QDynamicItem::distance(QPointF point_a)
{
	return sqrt(pow(point_a.x() - pos().x(), 2) + pow(point_a.y() - pos().y(), 2));
}

qreal QDynamicItem::field(QPointF & point, qreal & angleDepart)
{
	qreal angleRefracte;

	if (point.x() <= scene()->sceneRect().left() + getSize() || point.x() >= scene()->sceneRect().right() - getSize()) {
		angleRefracte = 540 - angleDepart;
	}
	else if (point.y() <= scene()->sceneRect().top() + getSize() || point.y() >= scene()->sceneRect().bottom() - getSize()) {
		angleRefracte = 360 - angleDepart;
	}

	else {
		return angleDepart;
	}
	if (angleRefracte > 360) {
		angleRefracte -= 360;
	}
	return angleRefracte;
}