#ifndef FLASH_H
#define FLASH_H

#include "QDynamicItem.h"
#include "QParameters.h"
#include <QGraphicsItem>
#include <QPixmap>
#include <QBrush>
#include <QDynamicItem.h>
#include <Pokemon.h>

// La classe Flash
// Description:
// La classe Flash représente leclair lorsquil y a une reproduction. Cette classe herite de la classe QDynamicItem 
// puisque les eclairs bougent.
// La classe possède les attributs mDelete, mCurrentTik, mParameter
// - ces accesseurs : 
//	bool isDelete();
// - ces mutateurs :

class Flash : public QDynamicItem
{
protected:
	bool mDelete{ };			//si le flash doit disparaitre
	size_t mCurrentTik{ };		// le tik
	QParameters *mParameter{ new QParameters };		//Les parametres
public:
	// Le constructeur recoit la position initiale de leclair, les parametres
	// Le constructeur permet de setter les parametres et de faire apparaitre les pokemons
	Flash(QPointF const & initialPosition = QPointF(), qreal scale = 1.0, QParameters *parameter = nullptr, 
		QGraphicsItem * parent = nullptr);
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
	bool isDelete();
	void advance(int phase) override;
	//le destructeur
	~Flash()=default;
};
#endif // !FLASH_H