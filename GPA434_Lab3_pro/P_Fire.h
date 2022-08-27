#ifndef P_FIRE_H
#define P_FIRE_H

#include "Pokemon.h"
#include "P_Grass.h"
#include "P_Water.h"
#include "Berry.h"

// La classe P_Fire
// Description:
// La classe P_Fire représente les pokemons feus. Cette classe herite de la classe Pokemon puisque cette classe
// permet de faire apparaitre un pokemon de type feu
// La classe ne possède aucun attribut

class P_Fire : public Pokemon
{
protected:
	//constante de la distance initiale
	const qreal distanceInit{ 9999 };
public:
	// Le constructeur recoit la position initiale du pokemon, lintelligence, la vitesse initiale, 
	// lechelle de la grosseure, les parametres
	// Le constructeur permet de setter les parametres et de faire apparaitre les pokemons de feu
	P_Fire(QPointF const & initialPosition = QPointF(), size_t intelligence = { 0 }, qreal initialSpeed = 1.0, 
		qreal scale = 8.0, QParameters *mParameter = nullptr, QGraphicsItem * parent = nullptr);
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
	// Fonction qui retourne 1 si le pokemon est dans le territoire feu sinon 0
	bool isInTerritory() override;
	// Fonction qui retourne 1 si le pokemon est dans le territoire eau ou herbe sinon 0
	bool isInEnemyTerritory() override;
	void advance(int phase) override;
	~P_Fire()=default;
};
#endif // !P_FIRE_H