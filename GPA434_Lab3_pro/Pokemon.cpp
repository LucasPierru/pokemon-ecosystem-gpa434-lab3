#include "Pokemon.h"

const qreal radiusGen1min{ 14.0 };
const qreal radiusGen1max{ 18.0 };
const qreal radiusGen2min{ 17.0 };
const qreal radiusGen2max{ 21.0 };
const qreal radiusGen3min{ 21.0 };
const qreal radiusGen3max{ 25.0 };
Pokemon::Pokemon(QPointF const & initialPosition, size_t intelligence, qreal initialSpeed, qreal scale, QGraphicsItem * parent)
{
	setSpeed(initialSpeed);
	setParameter(mParameter);
	mShape << QPointF(-1, 0.33)
		<< QPointF(-0.33, 1)
		<< QPointF(0.33, 1)
		<< QPointF(1, 0.33)
		<< QPointF(1, -0.33)
		<< QPointF(0.33, -1)
		<< QPointF(-0.33, -1)
		<< QPointF(-1, -0.33);
	setPos(initialPosition);
	setScale(scale);
}

QRectF Pokemon::boundingRect() const
{
	return mShape.boundingRect();
}

void Pokemon::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->drawPolygon(mShape);
}

bool Pokemon::isAlive()
{
	return mAlive;
}

bool Pokemon::isInvulnerable()
{
	return mInvulnerable;
}

bool Pokemon::isInTerritory()
{
	return false;
}

bool Pokemon::isInEnemyTerritory()
{
	return false;
}

void Pokemon::territoryAdvantage()
{
	//La vitesse du Pokemon incremente s'il est dans son territoire
	if (isInTerritory()) {
		setSpeed(mParameter->getTikSpeed() + 0.7);
	}
	if (!isInTerritory()) {
		setSpeed(mParameter->getTikSpeed());
	}
}

void Pokemon::setInvulnerablity(bool invulnerable)
{
	mInvulnerable = invulnerable;
}

void Pokemon::timerInvulnerable()
{
	/*Si le compteur d'invulnerabilite termine, il retourne a zero et le Pokemon perd son invulnerabilite. Il
	regarde aussi son opacite initiale*/
	if (invulnerableTik > 1000) {
		invulnerableTik = 0;
		setInvulnerablity(0);
		setOpacity(1);
	}
	invulnerableTik++;
}
void Pokemon::refreshLife()
{
	//Rafraichi la taille du coeur des Pokemon
	mHealthFill->setSize((10 * mLife) / mParameter->getMaxHealth());
	mHealthFill->resize();
	//Le Pokemon meurt s'il n'a plus de vie
	if (mLife <= 0 && isAlive()) {
		die();
	}
}
void Pokemon::die()
{
	mAlive = 0;
}
void Pokemon::checkMaxAge(size_t life)
{
	//Decremente la vie du Pokemon avec le temps
	if (currentAgeTik > (200 / mParameter->getTikSpeed())) {
		reduceLife(life);
		currentAgeTik = 0;
	}
}


void Pokemon::setParameter(QParameters *mparameter)
{
	mParameter = mparameter;
}

void Pokemon::setNature(size_t nature)
{
	mNature = nature;
}

void Pokemon::advance(int phase)
{
}

qreal Pokemon::randomBehaviour()
{
	const qreal max{ 1 };
	return QRandomGenerator::global()->bounded(max);
}
void Pokemon::reduceLife(size_t damage)
{
	if (damage > mLife) {
		mLife = 0;
	}
	else {
		mLife = mLife - damage;
	}
}

size_t Pokemon::getLife()
{
	return mLife;
}

size_t Pokemon::getIntelligence()
{
	return mIntelligence;
}

qreal Pokemon::getRadius(size_t intelligence, bool cap)
{
	if (intelligence == 0 && cap == 0) {
		return radiusGen1min;
	}

	if (intelligence == 0 && cap == 1) {
		return radiusGen1max;
	}
	if (intelligence == 1 && cap == 0) {
		return radiusGen2min;
	}

	if (intelligence == 1 && cap == 1) {
		return radiusGen2max;
	}
	if (intelligence == 2 && cap == 0) {
		return radiusGen3min;
	}

	if (intelligence == 2 && cap == 1) {
		return radiusGen3max;
	}
}


void Pokemon::meteoChange(QParameters *mparameter, size_t time)
{
	size_t day = mparameter->getMeteo();
	size_t verif = mparameter->getAreaTFire();
	//Si la meteo est celle qui avantage le Pokemon, il gagne de la vision
	if (mparameter->getMeteo() == time) {
		setVisionRadius(mVisionAttackRadius + 20.0, mVisionEscapeRadius + 20);
	}
	else {
		setVisionRadius(mVisionAttackRadius, mVisionEscapeRadius);
	}
}
void Pokemon::setVisionRadius(double visionAttack, double visionEscape)
{
	mVisionAttackRadius = visionAttack;
	mVisionEscapeRadius = visionEscape;
}
void Pokemon::setLife(size_t life)
{
	mLife = life;
}
void Pokemon::setHealthBar(QDynamicItem *health, QDynamicItem *emptyHealth)
{
	mHealthFill = health;
	mHealthBar = emptyHealth;
}
QDynamicItem* Pokemon::getHealthBar()
{
	return mHealthFill;
}
QDynamicItem * Pokemon::getEmptyHealthBar()
{
	return mHealthBar;
}
size_t Pokemon::getKillCount()
{
	return mKillCount;
}
void Pokemon::setKillCount(size_t kill)
{
	mKillCount = kill;
}
void Pokemon::eatBreed(size_t intelligence)
{
	//Regagne une vie
	if (mLife < mParameter->getMaxHealth()) {
		mLife++;
	}
	//Ramene a la taille initiale dependamment de l'intelligence
	if (intelligence == 0 && getSize() <= radiusGen1max) {
		setSize(getSize()*scaleGrad);
		resize();
	}
	if (intelligence == 1 && getSize() <= radiusGen2max) {
		setSize(getSize()*scaleGrad);
		resize();
	}
	if (intelligence == 2 && getSize() <= radiusGen3max) {
		setSize(getSize()*scaleGrad);
		resize();
	}
	if (intelligence == 0 && getSize() >= radiusGen1max) {
		mBreed = 1;
	}
	if (intelligence == 1 && getSize() >= radiusGen2max) {
		mBreed = 1;
	}
	if (intelligence == 2 && getSize() >= radiusGen3max) {
		mBreed = 1;
	}
}
void Pokemon::breedResize(size_t intelligence)
{
	//On ramene mBreed a 0
	mBreed = 0;
	//Dependamment de l'intelligence du pokemon, il rapetisse a sa taille initiale
	if (getIntelligence() == 0) {
		setSize(radiusGen1min);
		resize();
		breedIndicator();

	}
	else if (getIntelligence() == 1) {
		setSize(radiusGen2min);
		resize();
		breedIndicator();
	}
	else if (getIntelligence() == 2) {
		setSize(radiusGen3min);
		resize();
		breedIndicator();
	}
}
void Pokemon::breedIndicator()
{
	scene()->addItem(
		new Flash(pos(), 20, mParameter));
}