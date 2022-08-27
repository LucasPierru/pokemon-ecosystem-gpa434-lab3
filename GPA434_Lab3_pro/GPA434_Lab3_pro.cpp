#include "GPA434_Lab3_pro.h"

#include <QRandomGenerator>

const size_t GPA434_Lab3_pro::sMaxNbrOfItems{ 500 };
const QSize GPA434_Lab3_pro::sSceneSize(400, 373);
//const QSize GPA434_Lab3_pro::sSceneSize(500, 500);
const QColor GPA434_Lab3_pro::sSceneBackgroundColor(QColor::fromHsl(215, 80, 222));
const QString GPA434_Lab3_pro::sControlStartText("Start new simulation");
const QString GPA434_Lab3_pro::sControlStopText("End simulation");
const QString GPA434_Lab3_pro::sControlPauseText("Pause simulation");
const QString GPA434_Lab3_pro::sControlResumeText("Resume simulation");
const QString GPA434_Lab3_pro::sControlStepText("One step simulation");
const QColor GPA434_Lab3_pro::sControlActiveColor(0, 255, 0);
const QColor GPA434_Lab3_pro::sControlPauseColor(255, 255, 0);
const QColor GPA434_Lab3_pro::sControlIdleColor(255, 0, 0);
const QColor GPA434_Lab3_pro::sControlNotReadyColor(230, 230, 230);
const QColor GPA434_Lab3_pro::sControlNotBorderColor(128, 128, 128);
const qreal GPA434_Lab3_pro::sCenterRadius{ 25 };
const qreal GPA434_Lab3_pro::sMinOrientationDegrees{ 0.0 };
const qreal GPA434_Lab3_pro::sMaxOrientationDegrees{ 360.0 };
const qreal GPA434_Lab3_pro::sMinSpeed{ 1.0 };
const qreal GPA434_Lab3_pro::sMaxSpeed{ 5.0 };
const qreal GPA434_Lab3_pro::sMinSize{ 5.0 };
const qreal GPA434_Lab3_pro::sMaxSize{ 15.0 };

const int scaleText{ 3 };
const int posText{ 100 };

const QString GPA434_Lab3_pro::sAboutButtonText("À propos...");
const QString GPA434_Lab3_pro::sAboutText(
	R"..(GPA434 
Ingénierie des systèmes orientés objets

Laboratoire  3
Simulation d'un écosystème 

Ce projet consiste à réaliser un écosystème représenté par des pokemon de différents types

Réalisé par :
   - Fedi Bessrour
   - Érika Bolduc
   - Lucas Pierru
   - Mike Zamis
)..");



GPA434_Lab3_pro::GPA434_Lab3_pro(QWidget *parent)
	: QMainWindow(parent),
	mSimulationView{ new QGraphicsView(&mGraphicsScene) },
	mParameters{ new QParameters(sMaxNbrOfItems) },
	mControlBar{ new QControlBar(Qt::Vertical) },
	mAboutButton{ new QPushButton(sAboutButtonText) }
{
	setWindowTitle("Startup project demo");
	setWindowIcon(QIcon(":/GPA434_Lab3_pro/icon"));

	ui.setupUi(this);

	mControlBar->setReady();
	mControlBar->setText(sControlStartText, sControlStopText, sControlPauseText, sControlResumeText, sControlStepText);
	mControlBar->setColor(sControlActiveColor, sControlPauseColor, sControlIdleColor, sControlNotReadyColor, sControlNotBorderColor);
	mGraphicsScene.setSceneRect(-sSceneSize.width() / 2, -sSceneSize.height() / 2, sSceneSize.width(), sSceneSize.height());

	QWidget * controlWidget{ new QWidget };
	QVBoxLayout * controlLayout{ new QVBoxLayout };
	controlWidget->setLayout(controlLayout);
	controlLayout->addWidget(mParameters);
	controlLayout->addStretch();
	controlLayout->addWidget(mControlBar);
	controlLayout->addWidget(mAboutButton);

	QWidget * centralWidget{ new QWidget };
	QHBoxLayout * centralLayout{ new QHBoxLayout };
	centralWidget->setLayout(centralLayout);

	centralLayout->addWidget(mSimulationView);
	centralLayout->addWidget(controlWidget);

	setCentralWidget(centralWidget);

	connect(mControlBar, &QControlBar::started, this, &GPA434_Lab3_pro::startSimulation);
	connect(mControlBar, &QControlBar::stopped, this, &GPA434_Lab3_pro::stopSimulation);
	connect(mControlBar, &QControlBar::paused, this, &GPA434_Lab3_pro::pauseSimulation);
	connect(mControlBar, &QControlBar::resumed, this, &GPA434_Lab3_pro::resumeSimulation);
	connect(mControlBar, &QControlBar::stepped, this, &GPA434_Lab3_pro::stepSimulation);

	connect(&mTimer, &QTimer::timeout, this, &GPA434_Lab3_pro::advance);

	connect(mAboutButton, &QPushButton::clicked, this, &GPA434_Lab3_pro::about);
}

void GPA434_Lab3_pro::startSimulation()
{
	// Vide la scène pour démarrer une nouvelle démo
	mGraphicsScene.clear();

	// Met un item rectangulaire pour bien voir les limites de la scène
	QGraphicsRectItem * background{ new QGraphicsRectItem(mGraphicsScene.sceneRect()) };

	background->setPen(Qt::NoPen);
	background->setBrush(sSceneBackgroundColor);
	mGraphicsScene.addItem(background);


	left = mGraphicsScene.sceneRect().left();
	right = mGraphicsScene.sceneRect().right();
	top = mGraphicsScene.sceneRect().top();
	bottom = mGraphicsScene.sceneRect().bottom();

	Meteo * meteo{ new Meteo(mParameters->getMeteo(),QPointF(right - 20,bottom - 20),20) };
	mGraphicsScene.addItem(meteo);

	Water_T t;
	QPointF p;
	qreal rad = t.getRadius();
	qreal middle = (right + left) / 2;

	createTerritory();



	// Defini le nombres de baies voulues dans une intervalle voulue

	size_t nbBerryF = floor(t.getBerry(mParameters->getBerryPourcentage(), mParameters->getAreaTFire()));
	size_t nbBerryW = floor(t.getBerry(mParameters->getBerryPourcentage(), mParameters->getAreaTWater()));
	size_t nbBerryG = floor(t.getBerry(mParameters->getBerryPourcentage(), mParameters->getAreaTGrass()));
	// Cree tout les Pokemon feu, herbe, et eau dans leurs territoires respectifs
	for (int i{ 0 }; i < mParameters->getNbrOfPFire(); ++i) {
		P_Fire *fire{ new P_Fire(QPointF(left + mParameters->getAreaTFire(), top + mParameters->getAreaTFire()),
			0,
			mParameters->getTikSpeed(),
			fire->getRadius(0,0),
			mParameters) };
		mGraphicsScene.addItem(fire);

		HealthBar *mEmptyHealth{ new HealthBar(1,QPointF(left + mParameters->getAreaTFire(), top + mParameters->getAreaTFire()), 10, mParameters) };
		HealthBar *mHealth{ new HealthBar(0,QPointF(left + mParameters->getAreaTFire(), top + mParameters->getAreaTFire()), 10, mParameters) };
		fire->setHealthBar(mHealth, mEmptyHealth);
		mGraphicsScene.addItem(mHealth);
		mGraphicsScene.addItem(mEmptyHealth);
	}

	for (int i{ 0 }; i < mParameters->getNbrOfPWater(); ++i) {

		P_Water *water{ new P_Water(QPointF(right - mParameters->getAreaTWater(), top + (mParameters->getAreaTWater())),
				0,
				mParameters->getTikSpeed(),
				water->getRadius(0,0) ,
				mParameters) };
		mGraphicsScene.addItem(water);
		HealthBar *mEmptyHealth{ new HealthBar(1,QPointF(right - mParameters->getAreaTWater(), top + (mParameters->getAreaTWater())), 10, mParameters) };
		HealthBar *mHealth{ new HealthBar(0,QPointF(right - mParameters->getAreaTWater(), top + (mParameters->getAreaTWater())), 10, mParameters) };
		water->setHealthBar(mHealth, mEmptyHealth);
		mGraphicsScene.addItem(mHealth);
		mGraphicsScene.addItem(mEmptyHealth);

	}

	for (int i{ 0 }; i < mParameters->getNbrOfPGrass(); ++i) {

		P_Grass *grass{ new P_Grass(QPointF(middle, bottom - mParameters->getAreaTGrass()),
				0,
				mParameters->getTikSpeed(),
				grass->getRadius(0,0),
				mParameters)
		};
		mGraphicsScene.addItem(grass);
		HealthBar *mEmptyHealth{ new HealthBar(1,QPointF(middle,bottom - mParameters->getAreaTGrass()), 10, mParameters) };
		HealthBar *mHealth{ new HealthBar(0,QPointF(middle,bottom - mParameters->getAreaTGrass()), 10, mParameters) };
		grass->setHealthBar(mHealth, mEmptyHealth);

		mGraphicsScene.addItem(mHealth);
		mGraphicsScene.addItem(mEmptyHealth);

	}

	for (int i{ 0 }; i < 1; ++i) {
		spawn(nbBerryG, QPointF(middle, bottom - mParameters->getAreaTGrass()), mParameters->getAreaTGrass());
		spawn(nbBerryF, QPointF(left + mParameters->getAreaTFire(), top + mParameters->getAreaTFire()), mParameters->getAreaTFire());
		spawn(nbBerryW, QPointF(right - mParameters->getAreaTWater(), top + (mParameters->getAreaTWater())), mParameters->getAreaTWater());
	}

	// Démarre la simulation
	mTimer.start(30);
}
void GPA434_Lab3_pro::advance()
{
	mGraphicsScene.advance();
	qreal left = mGraphicsScene.sceneRect().left();
	qreal right = mGraphicsScene.sceneRect().right();
	qreal top = mGraphicsScene.sceneRect().top();
	qreal bottom = mGraphicsScene.sceneRect().bottom();
	bool pFire = 0;
	bool pWater = 0;
	bool pGrass = 0;

	for (QGraphicsItem * item : mGraphicsScene.items()) {
		Berry* berry{ dynamic_cast<Berry*>(item) };
		Pokemon* pokemon{ dynamic_cast<Pokemon*>(item) };
		P_Fire* fire{ dynamic_cast<P_Fire*>(item) };
		P_Water* water{ dynamic_cast<P_Water*>(item) };
		P_Grass* grass{ dynamic_cast<P_Grass*>(item) };
		HealthBar* health{ dynamic_cast<HealthBar*>(item) };
		Flash* flash{ dynamic_cast<Flash*>(item) };
		qreal dist_min = 9999;

		//Si le berry a ete mange on le delete de la scene
		if (berry != nullptr && berry->getEaten()) {
			mGraphicsScene.removeItem(berry);
			delete berry;
			spawn(1, randomPoint(left, right), (right - left) / 2);
		}

		if (fire != nullptr) {
			//Garde le coeur toujours en haut du Pokemon en question
			fire->getHealthBar()->setPos(fire->pos());
			fire->getHealthBar()->moveBy(0, -fire->getSize() - 10);

			fire->getEmptyHealthBar()->setPos(fire->pos());
			fire->getEmptyHealthBar()->moveBy(0, -fire->getSize() - 10);

			//Si on est en mode Evolution, et que le Pokemon en tue un autre, il evolue
			if (fire->getKillCount() >= 1 && fire->getIntelligence() == 0 && mParameters->getEvolutionstate() == 1) {

				//L'evolution se fais en creeant un deuxieme pokemon au dessus du pokemon initial et en effacant l'ancien directement apres
				P_Fire *charmeleon(new P_Fire(fire->pos(), 1, mParameters->getPokemonSpeed(), fire->getRadius(1, 0), mParameters));
				mGraphicsScene.addItem(charmeleon);

				HealthBar *mEmptyHealth{ new HealthBar(1,QPointF(left + mParameters->getAreaTFire(), top + mParameters->getAreaTFire()),10, mParameters) };
				HealthBar *mHealth{ new HealthBar(0,QPointF(left + mParameters->getAreaTFire(), top + mParameters->getAreaTFire()), mParameters->getMaxHealth(), mParameters) };
				charmeleon->setHealthBar(mHealth, mEmptyHealth);
				mGraphicsScene.addItem(mHealth);
				mGraphicsScene.addItem(mEmptyHealth);

				mGraphicsScene.removeItem(fire->getEmptyHealthBar());
				mGraphicsScene.removeItem(fire->getHealthBar());
				mGraphicsScene.removeItem(fire);
				delete fire->getHealthBar();
				delete fire;
			}
			// S'il a deja evolue et qu'il en tue un autre, il evolue encore
			else if (fire->getKillCount() >= 1 && fire->getIntelligence() == 1 && mParameters->getEvolutionstate() == 1) {

				//L'evolution se fais en creeant un deuxieme pokemon au dessus du pokemon initial et en effacant l'ancien directement apres

				P_Fire *charizard(new P_Fire(fire->pos(), 2, mParameters->getPokemonSpeed(), fire->getRadius(2, 0), mParameters));
				mGraphicsScene.addItem(charizard);
				HealthBar *mEmptyHealth{ new HealthBar(1,QPointF(left + mParameters->getAreaTFire(), top + mParameters->getAreaTFire()), 10, mParameters) };
				HealthBar *mHealth{ new HealthBar(0,QPointF(left + mParameters->getAreaTFire(), top + mParameters->getAreaTFire()),  mParameters->getMaxHealth(), mParameters) };
				charizard->setHealthBar(mHealth, mEmptyHealth);
				mGraphicsScene.addItem(mHealth);
				mGraphicsScene.addItem(mEmptyHealth);

				mGraphicsScene.removeItem(fire->getEmptyHealthBar());
				mGraphicsScene.removeItem(fire->getHealthBar());
				mGraphicsScene.removeItem(fire);
				delete fire->getHealthBar();
				delete fire;
			}
			pFire = 1;
		}
		if (water != nullptr) {
			//Garde le coeur toujours en haut du Pokemon en question
			water->getHealthBar()->setPos(water->pos());
			water->getHealthBar()->moveBy(0, -water->getSize() - 10);

			water->getEmptyHealthBar()->setPos(water->pos());
			water->getEmptyHealthBar()->moveBy(0, -water->getSize() - 10);

			//Si on est en mode Evolution, et que le Pokemon en tue un autre, il evolue
			if (water->getKillCount() >= 1 && water->getIntelligence() == 0 && mParameters->getEvolutionstate() == 1) {

				//L'evolution se fais en creeant un deuxieme pokemon au dessus du pokemon initial et en effacant l'ancien directement apres

				P_Water *wartortle(new P_Water(water->pos(), 1, mParameters->getPokemonSpeed(), water->getRadius(1, 0), mParameters));
				mGraphicsScene.addItem(wartortle);

				HealthBar *mEmptyHealth{ new HealthBar(1,QPointF(right - mParameters->getAreaTWater(), top + (mParameters->getAreaTWater())),  10 , mParameters) };
				HealthBar *mHealth{ new HealthBar(0,QPointF(right - mParameters->getAreaTWater(), top + (mParameters->getAreaTWater())),  mParameters->getMaxHealth(), mParameters) };
				wartortle->setHealthBar(mHealth, mEmptyHealth);
				mGraphicsScene.addItem(mHealth);
				mGraphicsScene.addItem(mEmptyHealth);

				mGraphicsScene.removeItem(water->getEmptyHealthBar());
				mGraphicsScene.removeItem(water->getHealthBar());
				mGraphicsScene.removeItem(water);
				delete water->getHealthBar();
				delete water;
			}
			// S'il a deja evolue et qu'il en tue un autre, il evolue encore
			else if (water->getKillCount() >= 1 && water->getIntelligence() == 1 && mParameters->getEvolutionstate() == 1) {

				//L'evolution se fais en creeant un deuxieme pokemon au dessus du pokemon initial et en effacant l'ancien directement apres

				P_Water *blastoise(new P_Water(water->pos(), 2, mParameters->getPokemonSpeed(), water->getRadius(2, 0), mParameters));
				mGraphicsScene.addItem(blastoise);

				HealthBar *mEmptyHealth{ new HealthBar(1,QPointF(right - mParameters->getAreaTWater(), top + (mParameters->getAreaTWater())), 10, mParameters) };
				HealthBar *mHealth{ new HealthBar(0,QPointF(right - mParameters->getAreaTWater(), top + (mParameters->getAreaTWater())),  mParameters->getMaxHealth(), mParameters) };
				blastoise->setHealthBar(mHealth, mEmptyHealth);
				mGraphicsScene.addItem(mHealth);
				mGraphicsScene.addItem(mEmptyHealth);

				mGraphicsScene.removeItem(water->getEmptyHealthBar());
				mGraphicsScene.removeItem(water->getHealthBar());
				mGraphicsScene.removeItem(water);
				delete water->getHealthBar();
				delete water;
			}
			pWater = 1;
		}
		if (grass != nullptr) {
			//Garde le coeur toujours en haut du Pokemon en question
			grass->getHealthBar()->setPos(grass->pos());
			grass->getHealthBar()->moveBy(0, -grass->getSize() - 10);

			grass->getEmptyHealthBar()->setPos(grass->pos());
			grass->getEmptyHealthBar()->moveBy(0, -grass->getSize() - 10);

			//Si on est en mode Evolution, et que le Pokemon en tue un autre, il evolue
			if (grass->getKillCount() >= 1 && grass->getIntelligence() == 0 && mParameters->getEvolutionstate() == 1) {

				//L'evolution se fais en creeant un deuxieme pokemon au dessus du pokemon initial et en effacant l'ancien directement apres

				P_Grass *ivysaur(new P_Grass(grass->pos(), 1, mParameters->getPokemonSpeed(), grass->getRadius(1, 0), mParameters));
				mGraphicsScene.addItem(ivysaur);

				HealthBar *mEmptyHealth{ new HealthBar(1,QPointF((right + left) / 2,bottom - mParameters->getAreaTGrass()), 10, mParameters) };
				HealthBar *mHealth{ new HealthBar(0,QPointF((right + left) / 2,bottom - mParameters->getAreaTGrass()),  mParameters->getMaxHealth(), mParameters) };
				ivysaur->setHealthBar(mHealth, mEmptyHealth);
				mGraphicsScene.addItem(mHealth);
				mGraphicsScene.addItem(mEmptyHealth);

				mGraphicsScene.removeItem(grass->getEmptyHealthBar());
				mGraphicsScene.removeItem(grass->getHealthBar());
				mGraphicsScene.removeItem(grass);
				delete grass->getHealthBar();
				delete grass;
			}
			// S'il a deja evolue et qu'il en tue un autre, il evolue encore
			else if (grass->getKillCount() >= 1 && grass->getIntelligence() == 1 && mParameters->getEvolutionstate() == 1) {

				//L'evolution se fais en creeant un deuxieme pokemon au dessus du pokemon initial et en effacant l'ancien directement apres

				P_Grass *venusaur(new P_Grass(grass->pos(), 2, mParameters->getPokemonSpeed(), grass->getRadius(2, 0), mParameters));
				mGraphicsScene.addItem(venusaur);

				HealthBar *mEmptyHealth{ new HealthBar(1,QPointF((right + left) / 2,bottom - mParameters->getAreaTGrass()), 10, mParameters) };
				HealthBar *mHealth{ new HealthBar(0,QPointF((right + left) / 2,bottom - mParameters->getAreaTGrass()),  mParameters->getMaxHealth(), mParameters) };
				venusaur->setHealthBar(mHealth, mEmptyHealth);
				mGraphicsScene.addItem(mHealth);
				mGraphicsScene.addItem(mEmptyHealth);

				mGraphicsScene.removeItem(grass->getEmptyHealthBar());
				mGraphicsScene.removeItem(grass->getHealthBar());
				mGraphicsScene.removeItem(grass);
				delete grass->getHealthBar();
				delete grass;
			}
			pGrass = 1;
		}
		//Delete le flash qui apparait lorsqu'il y a reproduction
		if (flash != nullptr && flash->isDelete()) {
			mGraphicsScene.removeItem(flash);
			delete flash;
		}
		//Delete les Pokemon morts en effacant d'abord leur coeur d'HP. Spawn aussi des berry.
		if (pokemon != nullptr && !pokemon->isAlive())
		{
			spawn(1, pokemon->pos(), 1000);
			mGraphicsScene.removeItem(pokemon);
			mGraphicsScene.removeItem(pokemon->getHealthBar());

			delete pokemon->getEmptyHealthBar();
			delete pokemon->getHealthBar();
			delete pokemon;
		}


	}
	//Affichages des gagnants
	if (pFire + pWater + pGrass < 2) {
		QGraphicsTextItem *gameOver = mGraphicsScene.addText("Les gagnants sont");
		if (pFire) {
			QGraphicsTextItem *winner = mGraphicsScene.addText("Les Pokemon Feu!!");
			winner->setScale(scaleText);
			winner->adjustSize();
			winner->setPos(-posText, 0);

		}
		if (pWater) {
			QGraphicsTextItem *winner = mGraphicsScene.addText("Les Pokemon Eau!!");
			winner->setScale(scaleText);
			winner->adjustSize();
			winner->setPos(-posText, 0);
		}
		if (pGrass) {
			QGraphicsTextItem *winner = mGraphicsScene.addText("Les Pokemon Herbe!!");
			winner->setScale(scaleText);
			winner->adjustSize();
			winner->setPos(-posText, 0);
		}

		gameOver->setScale(scaleText);
		gameOver->adjustSize();
		gameOver->setPos(-posText, -50);

		stopSimulation();
	}
}

void GPA434_Lab3_pro::createTerritory()
{

	mGraphicsScene.addItem(
		new Grass_T(QPointF((right + left) / 2, bottom - mParameters->getAreaTGrass()),
			mParameters->getAreaTGrass(),
			Qt::green));

	mGraphicsScene.addItem(
		new Fire_T(QPointF(left + mParameters->getAreaTFire(), top + mParameters->getAreaTFire()),
		(mParameters->getAreaTFire()),
			Qt::red));

	mGraphicsScene.addItem(
		new Water_T(QPointF(right - mParameters->getAreaTWater(), top + (mParameters->getAreaTWater())),
			mParameters->getAreaTWater(),
			Qt::blue));
}

double GPA434_Lab3_pro::numberPokemon(size_t a, size_t b, size_t c)
{
	double nbPokemon{ 0 };

	nbPokemon = a + b + c;


	return nbPokemon;
}

void GPA434_Lab3_pro::spawn(size_t nb, QPointF pos, qreal rayon)
{
	for (double i{ 0 }; i < nb; ++i) {
		qreal top = mGraphicsScene.sceneRect().top();
		QPointF posBerry;
		do {
			posBerry.setX(random(pos.x() - rayon, pos.x() + rayon));

		} while (posBerry.x() >= mGraphicsScene.sceneRect().right() || posBerry.x() <= mGraphicsScene.sceneRect().left());
		do {
			posBerry.setY(random(pos.y() - rayon, pos.y() + rayon));
		} while (posBerry.y() <= mGraphicsScene.sceneRect().top() || posBerry.y() >= mGraphicsScene.sceneRect().bottom());

		mGraphicsScene.addItem(
			new Berry(posBerry,
				6,
				Qt::darkMagenta));
	}

}


double GPA434_Lab3_pro::random(qreal maxValue)
{
	return QRandomGenerator::global()->bounded(maxValue);
}

double GPA434_Lab3_pro::random(qreal minValue, qreal maxValue)
{
	return random(maxValue - minValue) + minValue;
}

QColor GPA434_Lab3_pro::randomColor()
{
	return QColor::fromRgb(QRandomGenerator::global()->generate());
}

QPointF GPA434_Lab3_pro::randomPoint(qreal min, qreal max)
{
	return QPointF(random(min, max), random(min, max));
}

void GPA434_Lab3_pro::stepSimulation()
{
	mGraphicsScene.advance();
}

void GPA434_Lab3_pro::pauseSimulation()
{
	mTimer.stop();
}

void GPA434_Lab3_pro::resumeSimulation()
{
	mTimer.start(30);
}

void GPA434_Lab3_pro::stopSimulation()
{
	mTimer.stop();
}

void GPA434_Lab3_pro::about()
{
	QAboutDialog about(sAboutText, this);
	about.exec();
}