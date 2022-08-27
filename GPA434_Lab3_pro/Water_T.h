#ifndef WATER_T_H
#define WATER_T_H

#include "Territory.h"

// La classe Water_T
// Description:
// La classe Water_T représente le territoire circulaire pour leau. Cette classe herite de la classe Territory puisque le territoire
// eau est un territoire.
// La classe ne possède aucun attribut

class Water_T : public Territory
{
public:
	// Le constructeur recoit la position du centre du territoire, la grandeur ainsi que la couleur en parametre
	// Le constructeur permet de faire apparaitre le territoire eau a la bonne position avec la bonne taille et
	// la bonne couleur
	Water_T(QPointF const & initialPosition = QPointF(), qreal scale = 1.0, 
		QBrush const & brush = Qt::black, QGraphicsItem * parent=nullptr);
	~Water_T() = default;
};

#endif //!WATER_T_H
