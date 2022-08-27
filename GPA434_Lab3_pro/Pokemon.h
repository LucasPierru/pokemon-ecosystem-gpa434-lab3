#ifndef POKEMON_H
#define POKEMON_H

#include "QDynamicItem.h"
#include "QParameters.h"
#include "Territory.h"
#include "HealthBar.h"
#include "Flash.h"

// La classe Pokemon
// Description:
// La classe pokemon représente la totalite des pokemons. Cette classe herite de la
// classe QDynamicItem puisque les pokemons
// sont des entites dynamiques.
// La classe possède les attributs mWidth, mHealthMax, mAge, mVisionEscapeRadius, 
// mVisionAttackRadius, mKillCount, mIntelligence, currentTik, currentAgeTik, mAlive, 
// mBreed,mInvulnerable, left, right, top, bottom, mPrey, mPredator, *mParameter, *mHealthBar, *mHealthFill
// mNature = 0, mLife, mHitByPrey, mHitByPredator, invulnerableTik, scaleGrad, radiusGen1min, radiusGen1max, 
// radiusGen2min, radiusGen2max,radiusGen3min, radiusGen3max.
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

class Pokemon : public QDynamicItem
{
public:
	// Le constructeur recoit la position initiale du pokemon, lintelligence, la vitesse initiale, 
	// lechelle de la grosseure, les parametres
	// Le constructeur permet de setter les parametres et de faire apparaitre les pokemons
	Pokemon(QPointF const & initialPosition = QPointF(), size_t intelligence = { 0 }, 
		qreal initialSpeed = 1.0, qreal scale = 1.0, QGraphicsItem * parent = nullptr);
	bool isAlive();
	// Fonction qui retourne 1 si le pokemon est dans son territoire sinon 0
	virtual bool isInTerritory();
	// Fonction qui retourne 1 si le pokemon est dans le territoire ennemi sinon 0
	virtual bool isInEnemyTerritory();
	//Les avantages si un pokemon est dans son propre territoire
	void territoryAdvantage();
	// Le timer pour le temps dinvulnerabilite
	void timerInvulnerable();
	//Pour mettre a jour la vie
	void refreshLife();
	//Setter a 0 pour la varialbe mAlive
	void die();
	//verifier si la vie est depasse
	void checkMaxAge(size_t life);
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "override") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
	void advance(int phase) override;
	qreal randomBehaviour();
	//diminuer la vie dependamment du dommage
	void reduceLife(size_t damage);
	//les changements dependamment de la meteo (normal, jour, nuit, pluie)
	void meteoChange(QParameters *mparameter, size_t time);
	void eatBreed(size_t intelligence);
	void breedResize(size_t intelligence);
	void breedIndicator();

	//Les setter
	void setInvulnerablity(bool invulnerable);
	void setParameter(QParameters *mParameter);
	void setNature(size_t nature);
	void setVisionRadius(double visionAttack, double visionEscape);
	void setLife(size_t life);
	void setHealthBar(QDynamicItem *health, QDynamicItem *emptyHealth);
	void setKillCount(size_t kill);

	//Les getter
	size_t getLife();
	size_t getIntelligence();
	QDynamicItem *getHealthBar();
	QDynamicItem *getEmptyHealthBar();
	size_t getKillCount();
	bool isInvulnerable();
	qreal getRadius(size_t intelligence, bool cap);

	~Pokemon()=default;
protected:
	qreal mWidth{};						// la largeur
	qreal mHealthMax{};					// la vie max
	qreal mAge{};						// lage
	qreal mVisionEscapeRadius{ 50 };	//le rayon avec le predateur
	qreal mVisionAttackRadius{ 200 };	//le rayon avec la proie
	size_t mKillCount{ };				//
	size_t mIntelligence{ };			// le niveau dintelligence (evolution)
	size_t currentTik{ };				// le tik
	size_t currentAgeTik{ };			// le tik par rapport a lage
	bool mAlive{ 1 };					// 1 si vivant, 0 sinon
	bool mBreed{ };						// reproduction
	bool mInvulnerable{ };				// si vulnerable
	qreal left{ };						// coordonnee gauche cadre
	qreal right{  };					// coordonnee droite cadre
	qreal top{ };						// coordonnee top cadre
	qreal bottom{ };					// coordonnee en bas cadre
	qreal mPrey{};						// la proie
	qreal mPredator{};					// le predateur
	QParameters *mParameter{ new QParameters };		// les parametres
	QDynamicItem *mHealthBar{ new QDynamicItem };	// la barre de vie
	QDynamicItem *mHealthFill{ new QDynamicItem };	// remplir la vie
	size_t mNature{};					// la nature
	size_t mLife{};						// la vie
	size_t const mHitByPrey{ 2 };		//constante de perte de vie quand touche proie
	size_t const mHitByPredator{ 4 };	// constante de perte de vie quand touche predateur
	size_t invulnerableTik{ 0 };		// le tik invulnerable
	const qreal scaleGrad{ 1.02 };
};
#endif // POKEMON_H