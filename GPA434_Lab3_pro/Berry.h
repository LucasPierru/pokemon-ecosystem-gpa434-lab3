#ifndef BERRY_H
#define BERRY_H

#include <QColor>
#include <QBrush>
#include "StaticEntity.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <Pokemon.h>

// La classe Berry
// Description:
// La classe Berry représente les baies que les pokemons peuvent manger pour evoluer. Cette classe herite de la classe StaticEntity puisque les baies
// sont des entites statics.
// La classe possède les attributs mRadius, mBrush, mEaten et mShape.
// - ces accesseurs :
// bool getEaten();
// double getRadius();
// - ces mutateurs :
// 	void setEaten(bool eat);

class Berry : public StaticEntity
{
protected:
	QBrush mBrush{};
	double const mRadius{ 5 };
	bool mEaten{};
	QPolygonF mShape{};

public:
	// Le constructeur recoit la position initiale de la baie, lechelle de grandeur, la couleur
	// Le constructeur permet de setter les parametres et de faire apparaitre les pokemons
	Berry(QPointF const & initialPosition = QPointF(), qreal scale = 1.0, 
		QBrush const & brush = Qt::yellow, QGraphicsItem * parent = nullptr);
	~Berry()=default;
	void setEaten(bool eat);
	bool getEaten();
	double getRadius();
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;
	//Si un pokemon le touche alors le berry disparait
	void advance(int phase) override;
};

#endif //!BERRY_H