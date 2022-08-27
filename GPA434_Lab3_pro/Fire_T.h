#ifndef FIRE_T_H
#define FIRE_T_H

#include "Territory.h"

// La classe Fire_T
// Description:
// La classe Fire_T représente le territoire circulaire pour le feu. Cette classe herite de la classe Territory puisque le territoire
// feu est un territoire.
// La classe ne possède aucun attribut

class Fire_T : public Territory
{
public:
	// Le constructeur recoit la position du centre du territoire, la grandeur ainsi que la couleur en parametre
	// Le constructeur permet de faire apparaitre le territoire eau a la bonne position avec la bonne taille et
	// la bonne couleur
	Fire_T(QPointF const & initialPosition = QPointF(), qreal scale = 1.0, QBrush const & brush = Qt::black, QGraphicsItem * parent = nullptr);
	~Fire_T()=default;
};

#endif //!FIRE_T_H