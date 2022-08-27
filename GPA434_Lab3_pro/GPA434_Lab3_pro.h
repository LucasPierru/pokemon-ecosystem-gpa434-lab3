#include <QtWidgets/QMainWindow>
#include "ui_GPA434_Lab3_pro.h"
#include <QGraphicsScene>
#include <QTimer>


#include <QtWidgets/QMainWindow>
#include "ui_GPA434_Lab3_pro.h"
#include <QGraphicsView>
#include "QControlBar.h"
#include "QParameters.h"
#include <QPushButton>
#include "QAboutDialog.h"
#include <QHBoxLayout>
#include "QDynamicItem.h"
#include "Territory.h"
#include "Berry.h"
#include "P_Fire.h"
#include "P_Grass.h"
#include "P_Water.h"
#include "Fire_T.h"
#include "Water_T.h"
#include "Grass_T.h"
#include "HealthBar.h"
#include "Meteo.h"

class QGraphicsView;
class QControlBar;
class QParameters;
class QPushButton;

// La classe GPA434_Lab3_pro
// Description:
// La classe GPA434_Lab3_pro repr�sente la gestion du projet. 
// Cette classe herite de la classe QMainWindow.
// La classe poss�de les attributs mRadius, mBrush, mEaten et mShape.
// - ces accesseurs :
// bool getEaten();
// double getRadius();
// - ces mutateurs :
// 	void setEaten(bool eat);

class GPA434_Lab3_pro : public QMainWindow
{
	Q_OBJECT
public:
	GPA434_Lab3_pro(QWidget *parent = Q_NULLPTR);
	void advance();
	void spawn(size_t nb, QPointF pos, qreal rayon);
	void createTerritory();
	double numberPokemon(size_t a, size_t b, size_t c);

private:
	Ui::GPA434_Lab3_proClass ui;
	QGraphicsScene mGraphicsScene{};
	QGraphicsView * mSimulationView{};
	QParameters * mParameters{};
	QControlBar * mControlBar{};
	QPushButton * mAboutButton{};
	QTimer mTimer{};

	// Fonctions utilitaires de g�n�ration de valeurs al�atoires : devraient �tre ailleurs.
	double random(qreal maxValue);
	double random(qreal minValue, qreal maxValue);
	qreal left{ mGraphicsScene.sceneRect().left() };
	qreal right {mGraphicsScene.sceneRect().right()};
	qreal top = mGraphicsScene.sceneRect().top();
	qreal bottom = mGraphicsScene.sceneRect().bottom();
	QColor randomColor();
	QPointF randomPoint(qreal min, qreal max);

private slots:
	void startSimulation();
	void stepSimulation();
	void pauseSimulation();
	void resumeSimulation();
	void stopSimulation();

	void about();

protected:
	// Lit�raux et variables symboliques utilis�s
	static const QSize sSceneSize;					// Taille de la sc�ne
	static const size_t sMaxNbrOfItems;				// Nombre maximum de fl�che
	static const QString sAboutButtonText;			// Text du bouton "� propos"
	static const QString sAboutText;				// Text pour la bo�te � propos
	static const QString sControlStartText;			// Textes pour les contr�les
	static const QString sControlStopText;			//    "
	static const QString sControlPauseText;			//    "
	static const QString sControlResumeText;		//    "
	static const QString sControlStepText;			//    "
	static const QColor sSceneBackgroundColor;		// Couleurs utilis�es
	static const QColor sControlActiveColor;		//    "
	static const QColor sControlPauseColor;			//    "
	static const QColor sControlIdleColor;			//    "
	static const QColor sControlNotReadyColor;		//    "
	static const QColor sControlNotBorderColor;		//    "
	static const qreal sCenterRadius;				// Constantes li�es � la cr�ation al�atoire des fl�ches
	static const qreal sMinOrientationDegrees;		//    "
	static const qreal sMaxOrientationDegrees;		//    "
	static const qreal sMinSpeed;					//    "
	static const qreal sMaxSpeed;					//    "
	static const qreal sMinSize;					//    "
	static const qreal sMaxSize;
	//    "
};													//    "