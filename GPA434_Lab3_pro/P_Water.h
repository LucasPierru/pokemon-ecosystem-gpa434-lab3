#ifndef P_WATER_H
#define P_WATER_H

#include "Pokemon.h"
#include "P_Grass.h"
#include "P_Fire.h"
#include "Berry.h"

class P_Water : public Pokemon
{
public:
	// Fonction qui retourne 1 si le pokemon est dans le territoire eau sinon 0
	bool isInTerritory() override;
	// Fonction qui retourne 1 si le pokemon est dans le territoire ennemi sinon 0
	virtual bool isInEnemyTerritory() override; 
	P_Water(QPointF const & initialPosition = QPointF(), size_t intelligence = { 0 }, qreal initialSpeed = 1.0, qreal scale = 8.0, QParameters *mParameter = nullptr, QGraphicsItem * parent = nullptr);
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : dessine la forme
	void advance(int phase) override;
	~P_Water() = default;
};

#endif // !P_WATER_H