#ifndef GRASS_T_H
#define GRASS_T_H

#include "Territory.h"

// La classe Grass_T
// Description:
// La classe Grass_T représente le territoire circulaire pour lherbe. Cette classe herite de la classe Territory puisque le territoire
// herbe est un territoire.
// La classe ne possède aucun attribut

class Grass_T : public Territory
{
public:
	// Le constructeur recoit la position du centre du territoire, la grandeur ainsi que la couleur en parametre
	// Le constructeur permet de faire apparaitre le territoire eau a la bonne position avec la bonne taille et
	// la bonne couleur
	Grass_T(QPointF const & initialPosition = QPointF(), qreal scale = 1.0, 
		QBrush const & brush = Qt::black, QGraphicsItem * parent = nullptr);
	~Grass_T()=default;
};

#endif //!GRASS_T_H