#ifndef Q_PARAMETERS_H
#define Q_PARAMETERS_H

#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>

class QSpinBox;
class QSlider;
class QCheckbox;

// La classe QParameters
// Description:
// La classe QParameters représente les 8 parametres modifiables. Cette classe herite de la classe QWidget.
// La classe possède les attributs mNbrOfPFire, mNbrOfPWater,mNbrOfPGrass,mAreaTFire,mAreaTWater, mAreaTGrass, 
// mBerryPourcentage, mNature, mMaxHealth, mTikSpeed, mPSpeed, mMeteo, mTextMeteo, mEvolution.
// - ces accesseurs :
// 	size_t getNbrOfPFire() const;
//	size_t getNbrOfPWater() const;
//	size_t getNbrOfPGrass() const;
//	size_t getAreaTFire() const;
//	size_t getAreaTWater() const;
//	size_t getAreaTGrass() const;
//	size_t getBerryPourcentage() const;
//	size_t getNature() const;
//	size_t getMaxHealth() const;
//	size_t getTikSpeed() const;
//	qreal getPokemonSpeed() const;
//	size_t getMeteo() const;
//	bool getEvolutionstate()const;

class QParameters : public QWidget
{
	Q_OBJECT

public:
	QParameters(size_t maxItems = 250, QWidget * parent = nullptr);
	size_t getNbrOfPFire() const;
	size_t getNbrOfPWater() const;
	size_t getNbrOfPGrass() const;
	size_t getAreaTFire() const;
	size_t getAreaTWater() const;
	size_t getAreaTGrass() const;
	size_t getBerryPourcentage() const;
	size_t getNature() const;
	size_t getMaxHealth() const;
	size_t getTikSpeed() const;
	qreal getPokemonSpeed() const;
	size_t getMeteo() const;
	bool getEvolutionstate()const;

protected:
	QSpinBox * mNbrOfPFire;
	QSpinBox * mNbrOfPWater;
	QSpinBox * mNbrOfPGrass;
	QSpinBox * mAreaTFire;
	QSpinBox * mAreaTWater;
	QSpinBox * mAreaTGrass;
	QSlider * mBerryPourcentage;
	QSlider * mNature;
	QSpinBox * mMaxHealth;
	QSpinBox * mTikSpeed;
	QSpinBox * mPSpeed;
	QSpinBox * mMeteo;
	QLabel * mTextMeteo;
	QCheckBox * mEvolution;
};
#endif // Q_PARAMETERS_H