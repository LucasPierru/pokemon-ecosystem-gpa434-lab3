#ifndef TERRITORY_H
#define TERRITORY_H

#include "StaticEntity.h"

// La classe Territory
// Description:
// La classe territoire représente les territoires circulaires. Cette classe herite de la classe StaticEntity puisque les territoires
// sont des entites statics.
// La classe possède les attributs mRadius, mBrush et mShape.
// - ces accesseurs :
// double getRadius();
// - ces mutateurs :
// 	void setBrush(QBrush const & brush);

class Territory : public StaticEntity
{
protected:
	double mRadius;					// Le rayon du territoire
	QBrush mBrush;					// Le couleur du territoire
	QPolygonF mShape;				// La forme du territoire
	qreal const sizeAdjust = 0.1;	//Ajustement de la taille des territoires pour le nb de berry
	
public:
	// Le constructeur qui recoit la position du territoire, lechelle et la couleur voulu
	// Le constructeur permet de creer la forme circulaire puis de faire apparaitre le 
	// territoire a la bonne position et de la bonne grandeur
	Territory(QPointF const & initialPosition = QPointF(), qreal scale = 1.0, 
		QBrush const & brush = Qt::black, QGraphicsItem * parent=nullptr);
	// Le destructeur
	~Territory()=default;

	// Fonction qui recoit le pourcentage de berri voulu et retourne
	qreal getBerry(qreal percentage, qreal size);
	void setBrush(QBrush const & brush);
	double getRadius();

	// Fonction abstraite de QGraphicsItem (DOIT être "override") : retourne la taille de l'item
	QRectF boundingRect() const ;
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;
};

#endif //!TERRITORY_H