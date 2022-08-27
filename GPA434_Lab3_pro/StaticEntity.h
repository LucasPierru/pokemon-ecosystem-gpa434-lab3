#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H

#include "RandomPokemon.h"
#include <QGraphicsItem>

// La classe StaticEntity
// Description:
// La classe StaticEntity repr�sente tous les entites statics soit les territoires (feu, eau et herbe) et les baies.
// La classe ne poss�de aucun attribut

class StaticEntity : public QGraphicsPixmapItem
{
public:
	StaticEntity(QPointF const & initialPosition = QPointF(), qreal scale = 1.0, QBrush const & brush = Qt::white, QGraphicsItem * parent=nullptr);
	~StaticEntity() = default;
};
#endif //!STATIC_ENTITY_H