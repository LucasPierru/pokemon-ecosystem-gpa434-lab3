#include "P_Fire.h"

P_Fire::P_Fire(QPointF const & initialPosition, size_t intelligence, 
	qreal initialSpeed, qreal scale, QParameters *parameter, QGraphicsItem * parent)
{
	setParameter(parameter);
	setLife(mParameter->getMaxHealth());
	setNature(mParameter->getNature());
	mIntelligence = intelligence;
	setSize(scale);
	setSpeed(mParameter->getPokemonSpeed());
	meteoChange(mParameter, 2);
	mBreed = 0;
	setPos(initialPosition);
	setScale(scale);
}

QRectF P_Fire::boundingRect() const
{
	return mShape.boundingRect();
}

void P_Fire::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QPixmap red;
	//L'intelligence du Pokemon definit son apparence
	if (mIntelligence == 2) {
		red.load("6.png");
	}
	else if (mIntelligence == 1) {
		red.load("5.png");
	}
	else {
		red.load("4.png");
	}
	painter->setPen(Qt::NoPen);
	painter->drawPixmap(mShape.boundingRect().toRect(), red);
}

bool P_Fire::isInTerritory()
{
	left = scene()->sceneRect().left();
	right = scene()->sceneRect().right();
	top = scene()->sceneRect().top();
	bottom = scene()->sceneRect().bottom();
	qreal center = static_cast<qreal>(mParameter->getAreaTFire());
	if (pos().x() > left + center - center && pos().x() < left + center + center) {
		if (pos().y() < top + center + center && pos().y() > top + center - center) {
			return true;
		}
	}
	return false;
}

bool P_Fire::isInEnemyTerritory()
{
	left = scene()->sceneRect().left();
	right = scene()->sceneRect().right();
	top = scene()->sceneRect().top();
	bottom = scene()->sceneRect().bottom();
	qreal center = static_cast<qreal>(mParameter->getAreaTWater());
	if (pos().x() > right - center - center && pos().x() < right) {
		if (pos().y() < top + (center)+center && pos().y() > top + (center)-center) {
			return true;
		}
	}
	return false;
}

void P_Fire::advance(int phase)
{
	if (phase == 0) {
		QPointF target;
		qreal decision;
		qreal mDistancePredator{ distanceInit };
		qreal mDistancePrey{ distanceInit };
		qreal mDistanceFood{ distanceInit };
		qreal mDistanceAlly{ distanceInit };
		qreal sizeAlly{};
		QPointF mPositionPredator;
		QPointF mPositionPrey;
		QPointF mPositionFood;
		QPointF mPositionAlly;
		for (QGraphicsItem * item : scene()->items()) {
			P_Fire* ally{ dynamic_cast<P_Fire*>(item) };
			P_Water* predator{ dynamic_cast<P_Water*>(item) };
			P_Grass* prey{ dynamic_cast<P_Grass*>(item) };
			Berry* food{ dynamic_cast<Berry*>(item) };
			//Trouve les predateurs, proies, la nourriture et l'allie les plus proches
			if (predator != nullptr && distance(predator->pos()) < mDistancePredator) {
				mDistancePredator = distance(predator->pos());
				mPositionPredator = predator->pos();
			}
			if (prey != nullptr && distance(prey->pos()) < mDistancePrey && prey->isInvulnerable() == 0) {
				mDistancePrey = distance(prey->pos());
				mPositionPrey = prey->pos();
			}
			if (food != nullptr && distance(food->pos()) < mDistanceFood) {
				mDistanceFood = distance(food->pos());
				mPositionFood = food->pos();
			}
			if (ally != nullptr && ally != this && distance(ally->pos()) < mDistanceAlly) {
				mDistanceAlly = distance(ally->pos());
				mPositionAlly = ally->pos();
				sizeAlly = ally->getSize();
			}
		}
		//decision est un nombre aleatoire qui definiera son prochain mouvement
		decision = randomBehaviour();
		qreal NatureElement = 0;
		//Convertis la nature du Pokemon en decimal
		if (mNature > 50) {
			NatureElement = 0.7 + ((mNature / 100.0) / 2);
		}
		else {
			NatureElement = 0.7 - (0.5 - (mNature / 100.0) / 2);
		}
		//Fonctions de validation empechant d'avoir une nature invalide
		if (NatureElement > 1) {
			NatureElement = 1;
		}
		else if (NatureElement < 0) {
			NatureElement = 0;
		}
		//Si la nature du Pokémon lui dit d'etre agressif OU s'il n'y a aucun berry dans son champ de vision, il va vers la proie la plus proche
		if ((decision < NatureElement || mDistanceFood> mVisionAttackRadius) && mDistancePrey < mVisionAttackRadius && mIntelligence == 0 || (mIntelligence > 0 && getLife() > mHitByPrey)) {
			target = mPositionPrey;
		}
		//Si la nature du Pokémon lui dit d'etre passif OU s'il n'y a aucune proie dans son champ de vision, il va vers la baie la plus proche
		else if ((decision > NatureElement || mDistancePrey > mVisionAttackRadius) && mDistanceFood < mVisionAttackRadius) {
			target = mPositionFood;
		}
		//S'il n'y a rien d'intelligent a faire, la target sera un point aléatoire dans la map
		else {
			left = scene()->sceneRect().left();
			right = scene()->sceneRect().right();
			target = QPointF(randomPoint(left, right));
		}
		//S'il a mangé assez de baie pour se reproduire, il lache sa nourriture ou sa proie et retourne aussitot à son territoire pour pouvoir se procrée
		if (mBreed == 1) {
			target = QPointF(left + mParameter->getAreaTFire(), top + mParameter->getAreaTFire());
		}
		//S'il est un Pokemon evolue 2 fois, il ne pourchasse JAMAIS sa proie dans un territoire ennemi
		if (mIntelligence == 2 && isInEnemyTerritory()) {
			target.setX(this->x() + (this->x() - right - mParameter->getAreaTWater()));
			target.setY(this->y() + (this->y() - top + (mParameter->getAreaTWater())));
		}
		//S'il voit un predateur, il lache toute ses autres prioritées pour s'enfuir
		if (mDistancePredator < mVisionEscapeRadius && mDistancePredator < mDistanceFood && mDistancePredator < mDistancePrey) {
			target.setX(this->x() + (this->x() - mPositionPredator.x()));
			target.setY(this->y() + (this->y() - mPositionPredator.y()));
		}
		//Condition qui empeche des Pokémon alliés de se piétiner
		if (mDistanceAlly < getSize() + sizeAlly) {
			target.setX(this->x() + (this->x() - mPositionAlly.x()));
			target.setY(this->y() + (this->y() - mPositionAlly.y()));
		}
		//Conditions qui s'assurent que la cible ne peut jamais etre a l'exterieur de la map
		if (target.x() <= scene()->sceneRect().left() + getSize()) {
			target.setX(scene()->sceneRect().left() + getSize());
		}
		if (target.y() <= scene()->sceneRect().top() + getSize()) {
			target.setY(scene()->sceneRect().top() + getSize());
		}
		if (target.x() >= scene()->sceneRect().right() - getSize()) {
			target.setX(scene()->sceneRect().right() - getSize());
		}
		if (target.y() >= scene()->sceneRect().bottom() - getSize()) {
			target.setY(scene()->sceneRect().bottom() - getSize());
		}
		double maxDeltaRotation{ 0.32 };
		//Se deplace vers la cible
		qreal rotateRad{ QDynamicItem::normalizeAngle(qDegreesToRadians(rotation())) };
		qreal targetRad{ QDynamicItem::normalizeAngle(atan2(target.y() - y(), target.x() - x())) };
		qreal deltaRotationRadians{ targetRad - rotateRad };
		if (deltaRotationRadians > M_PI) deltaRotationRadians = deltaRotationRadians - 2.0 * M_PI;
		if (deltaRotationRadians < -M_PI) deltaRotationRadians = 2.0 * M_PI + deltaRotationRadians;

		if (deltaRotationRadians > maxDeltaRotation) {
			deltaRotationRadians = maxDeltaRotation;
		}
		else if (deltaRotationRadians < -maxDeltaRotation) {
			deltaRotationRadians = -maxDeltaRotation;
		}
		qreal newDir{ rotateRad + deltaRotationRadians };

		// Détermine la nouvelle position selon la nouvelle orientation et la vitesse
		QPointF newPosition(pos() + QPointF(qCos(newDir), qSin(newDir)) * mSpeed);

		// Applique la nouvelle orientation et la nouvelle position
		setRotation(qRadiansToDegrees(newDir));
		setPos(newPosition);
	}
	else if (phase == 1) {
		//Soustrait la vie du pokemon selon son age
		checkMaxAge(1);
		//Rafraichis la vie du pokemon en mettant a jour son coeur et en le tuant s'il le faut.
		refreshLife();
		//Verifie si le Pokemon a des avantages de territoire
		territoryAdvantage();
		static constexpr const qreal maxDeltaOrientation{ 12.5 }; // in °
		// Détermine la nouvelle orientation selon une variation aléatoire dans l'intervalle [-maxDeltaOrientation, maxDeltaOrientation] => ± 12.5°
		qreal newOrientationDegrees{ rotation() + QRandomGenerator::global()->bounded(2.0 * maxDeltaOrientation) - maxDeltaOrientation };
		qreal newOrientationRadians{ qDegreesToRadians(newOrientationDegrees) };

		// Détermine la nouvelle position selon la nouvelle orientation et la vitesse
		QPointF newPosition(pos() + QPointF(qCos(newOrientationRadians), qSin(newOrientationRadians)) * mSpeed);
		// Si la nouvelle position est à l'extérieur de la scène, la nouvelle position est téléportée à la région opposée de la scène

		// Applique la nouvelle orientation et la nouvelle position
		setRotation(field(newPosition, newOrientationDegrees));
		setPos(newPosition);
		//On verifie tout les item de la scene pour voir leurs interactions avec le P_Fire
		for (QGraphicsItem * item : scene()->items()) {
			Berry* berry{ dynamic_cast<Berry*>(item) };
			P_Fire* fire{ dynamic_cast<P_Fire*>(item) };
			P_Water* water{ dynamic_cast<P_Water*>(item) };
			P_Grass* grass{ dynamic_cast<P_Grass*>(item) };

			//Si le Pokemon feu rencontre un pokemon herbe, et qu'aucun des deux est invulnerable
			if (grass != nullptr && distance(grass->pos()) < (getSize() + grass->getSize()) && grass->isInvulnerable() == 0 && isInvulnerable() == 0) {
				//Le Pokemon herbe perd des vies
				grass->reduceLife(mHitByPredator);
				//Le Pokemon feu perd un peu moins de vies
				reduceLife(mHitByPrey);
				//Le Pokemon herbe deviens invulnerable
				grass->setInvulnerablity(1);
				//Si le Pokemon herbe meurt, le Pokemon feu gagne un "kill"
				if (grass->getLife() <= 0) {
					mKillCount++;
				}
			}

			//Si le Pokemon feu est invulnerable, il devient transparent et on lance son timer
			if (isInvulnerable()) {
				setOpacity(0.3);
				timerInvulnerable();
			}

			//Si le Pokemon feu rencontre un berry, il le mange, regagne une vie et gagne une taille selon son intelligence
			if (berry != nullptr && distance(berry->pos()) < getSize() + berry->getRadius()) {
				eatBreed(mIntelligence);
			}

			//Si le Pokemon feu est dans son territoire et qu'il doit breed, il cree un enfant et reprend sa taille originale
			if (isInTerritory() && mBreed == 1) {
				P_Fire *babyFire(new P_Fire(pos(), 0, mParameter->getTikSpeed(), 12.0, mParameter));
				scene()->addItem(babyFire);


				HealthBar *mEmptyHealth{ new HealthBar(1,QPointF(right - mParameter->getAreaTWater(), top + (mParameter->getAreaTWater())), 10, mParameter) };
				HealthBar *mHealth{ new HealthBar(0,QPointF(right - mParameter->getAreaTWater(), top + (mParameter->getAreaTWater())), 10, mParameter) };
				babyFire->setHealthBar(mHealth, mEmptyHealth);
				scene()->addItem(mHealth);
				scene()->addItem(mEmptyHealth);

				//Reprend sa taille initiale
				breedResize(mIntelligence);
			}

		}
	}
	currentAgeTik++;
	currentTik++;
}