#ifndef METEO_H
#define METEO_H

#include "StaticEntity.h"
#include "QParameters.h"
#include <QGraphicsItem>
#include <QPixmap>
#include <QBrush>
#include <Pokemon.h>

class Meteo : public StaticEntity

{
protected:
	size_t mMeteo{};
	QBrush mBrush{};
	double const mRadius{ 5 };
	bool mEaten{};
	QPolygonF mShape{};
public:
	QRectF boundingRect() const override;
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
	QParameters *mParameter{ new QParameters };
	Meteo(size_t meteo, QPointF const & initialPosition = QPointF(), qreal scale = 1.0,
		QBrush const & brush = Qt::yellow, QGraphicsItem * parent = nullptr);
	void advance(int phase) override;
	~Meteo()=default;
};

#endif // !FLASH_H