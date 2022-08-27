#ifndef Q_ARROW_ITEM_H
#define Q_ARROW_ITEM_H


#include <QGraphicsItem>
#include <QBrush>


class QArrowItem : public QGraphicsItem
{
public:
	// On choisi un constructeur par défaut offrant optionnellement un accès à tous les paramètres.
	QArrowItem(QPointF const & initialPosition = QPointF(), qreal initialOrientationDegrees = 0.0, qreal initialSpeed = 1.0, qreal scale = 1.0, QBrush const & brush = Qt::white, QGraphicsItem * parent = nullptr);

	// Mutateur de couleur et de vitesse
	void setColor(QBrush const & brush);
	void setSpeed(qreal speed);

	// Fonction abstraite de QGraphicsItem (DOIT être "override") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut être "override") : fait un tick de simulation
	void advance(int phase) override;

protected:
	// La couleur de fond
	QBrush mBrush;
	// La forme 
	QPolygonF mShape;
	// La vitesse
	qreal mSpeed;

	// Fonctions mathématiques utilitaires servant à réaliser la "téléportation" : devraient être ailleurs.
	static qreal warp(qreal value, qreal begin, qreal end);
	void warp(QPointF & point);
};

#endif // Q_ARROW_ITEM_H
