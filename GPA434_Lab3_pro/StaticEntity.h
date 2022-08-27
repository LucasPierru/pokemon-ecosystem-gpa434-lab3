#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H

#include "RandomPokemon.h"
#include <QGraphicsItem>

// La classe StaticEntity
// Description:
// La classe StaticEntity représente tous les entites statics soit les territoires (feu, eau et herbe) et les baies.
// La classe ne possède aucun attribut

class StaticEntity : public QGraphicsPixmapItem
{
public:
	StaticEntity(QPointF const & initialPosition = QPointF(), qreal scale = 1.0, QBrush const & brush = Qt::white, QGraphicsItem * parent=nullptr);
	~StaticEntity() = default;
};
#endif //!STATIC_ENTITY_H