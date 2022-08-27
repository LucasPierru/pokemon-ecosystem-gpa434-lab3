#ifndef P_GRASS_H
#define P_GRASS_H

#include "Pokemon.h"
#include "P_Fire.h"
#include "P_Water.h"
#include "Berry.h"

// La classe P_Grass
// Description:
// La classe P_Grass représente les pokemons herbes. Cette classe herite de la classe Pokemon puisque cette classe
// permet de faire apparaitre un pokemon de type herbe
// La classe ne possède aucun attribut

class P_Grass :public Pokemon
{
public:
	// Le constructeur recoit la position initiale du pokemon, lintelligence, la vitesse initiale, 
	// lechelle de la grosseure, les parametres
	// Le constructeur permet de setter les parametres et de faire apparaitre les pokemons de grass
	P_Grass(QPointF const & initialPosition = QPointF(), size_t intelligence = { 0 }, 
		qreal initialSpeed = 1.0, qreal scale = 1.0, QParameters *mParameter = nullptr, 
		QGraphicsItem * parent = nullptr);
	
	void advance(int phase) override;
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
	// Fonction qui retourne 1 si le pokemon est dans le territoire feu sinon 0
	bool isInTerritory() override;
	// Fonction qui retourne 1 si le pokemon est dans le territoire ennemi sinon 0
	virtual bool isInEnemyTerritory() override;
	~P_Grass()=default;
};

#endif // !P_GRASS_H