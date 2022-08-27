#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QDynamicItem.h>
#include <QParameters.h>

// La classe HealthBar
// Description:
// La classe HealthBar représente la barre de vie. Cette classe herite de la classe QDynamicItem 
// puisque les barres de vie.
// La classe possède les attributs mTarget, mFill, mParameter
// - ces accesseurs : 
//	
// - ces mutateurs :
//	void setTarget(QPointF target);

class HealthBar : public QDynamicItem

{
private:
	QPointF mTarget{};			//le point du target
	bool mFill{};				// si cest linterieur ou le contour de la vie
	QParameters *mParameter{ new QParameters };		//les parametres
public:
	// Le constructeur recoit si cest linterieur ou le contour de la vie, la position initiales, 
	// lechelle de grandeur, les parametres
	// Le constructeur permet de setter les parametres et de faire apparaitre les barres de vie
	HealthBar(bool fill, QPointF const & initialPosition = QPointF(), qreal scale = 1.0, 
		QParameters *mParameter = nullptr, QGraphicsItem * parent = nullptr);
	void setTarget(QPointF target);
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
	//le destructeur
	~HealthBar()=default;
};

#endif // !HEALTHBAR_H