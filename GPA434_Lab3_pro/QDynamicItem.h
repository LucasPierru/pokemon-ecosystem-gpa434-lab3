#ifndef Q_DYNAMIC_ITEM_H
#define Q_DYNAMIC_ITEM_H

#include <QGraphicsPixmapItem>
#include <QtMath>
#include "RandomPokemon.h"

// La classe QDynamicItem
// Description:
// La classe QDynamicItem représente la totalite des QGraphicsPixmapItem. Cette classe herite de la classe QGraphicsPixmapItem puisque les pokemons
// sont des entites dynamiques.
// La classe possède les attributs:	QBrush mColor, mColorInitial, qreal mSpeed, qreal mSize, QPolygonF mShape
// - ces accesseurs : 
//	size_t getLife();
//	size_t getIntelligence();
//	QDynamicItem *getHealthBar();
//	QDynamicItem *getEmptyHealthBar();
//	size_t getKillCount();
//	bool getInvulnerable();
//	qreal getRadius(size_t intelligence, bool cap);
//	size_t getLife();
// - ces mutateurs :
// 	void setInvulnerablity(bool invulnerable);
//	void setParameter(QParameters *mParameter);
//	void setNature(size_t nature);
//	void setVisionRadius(double visionAttack, double visionEscape);
//	void setLife(size_t life);
//	void setHealthBar(QDynamicItem *health, QDynamicItem *emptyHealth);
//	void setKillCount(size_t kill);

class QDynamicItem : public QGraphicsPixmapItem
{
public:
	// Le constructeur recoit la position initiale de litem dynamique, lintelligence, la vitesse initiale, 
	// lechelle de la grosseure, les parametres
	// Le constructeur permet de setter les parametres et de faire apparaitre les items dynamiques
	QDynamicItem(QPointF const & initialPosition = QPointF(), size_t intelligence = { 0 }, 
		qreal initialSpeed = 1.0, qreal scale = 1.0, QGraphicsItem * parent = nullptr);
	double normalizeAngle(double radians);
	void setSpeed(qreal speed);
	void setSize(qreal size);
	void resize();
	qreal getSize();
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : retourne la taille de l'item
	QRectF boundingRect() const;
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
	qreal field(QPointF & point, qreal & angleDepart);
	void advance(int phase) override;
	qreal distance(QPointF point_a);
	~QDynamicItem()=default;
protected:
	qreal mSpeed{};
	qreal mSize{};
	QPolygonF mShape{};
};

#endif // Q_DYNAMIC_ITEM_H