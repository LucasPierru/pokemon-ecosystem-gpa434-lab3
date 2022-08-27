#include "QParameters.h"

QParameters::QParameters(size_t maxItems, QWidget * parent)
	:	QWidget(parent),
		mNbrOfPFire{ new QSpinBox },
		mNbrOfPWater{ new QSpinBox },
		mNbrOfPGrass{ new QSpinBox },
		mAreaTFire{ new QSpinBox },
		mAreaTWater{ new QSpinBox },
		mAreaTGrass{ new QSpinBox },
		mBerryPourcentage{new QSlider(Qt::Horizontal, parent)},
		mNature{ new QSlider(Qt::Horizontal, parent) },
		mMaxHealth{ new QSpinBox },
		mTikSpeed{ new QSpinBox },
		mPSpeed{ new QSpinBox },
		mTextMeteo{ new QLabel },
		mMeteo{ new QSpinBox },
		mEvolution{ new QCheckBox ("Evolution")}

{	
	const size_t minMaxNbr{ 10 };
	const size_t defaultPokemonNbr{ 3 };
	const size_t shownedArea{ 100 };
	const size_t tailleMaxT{ 120 };
	const size_t ratio{100};
	const size_t minTik{ 1 };

	mNbrOfPFire->setRange(1, qMax(static_cast<size_t>(minMaxNbr), maxItems));
	mNbrOfPFire->setValue(defaultPokemonNbr);

	mNbrOfPWater->setRange(1, qMax(static_cast<size_t>(minMaxNbr), maxItems));
	mNbrOfPWater->setValue(defaultPokemonNbr);

	mNbrOfPGrass->setRange(1, qMax(static_cast<size_t>(minMaxNbr), maxItems));
	mNbrOfPGrass->setValue(defaultPokemonNbr);

	mAreaTFire->setRange(1, qMax(static_cast<size_t>(minMaxNbr), tailleMaxT));
	mAreaTFire->setValue(shownedArea);

	mAreaTWater->setRange(1, qMax(static_cast<size_t>(minMaxNbr), tailleMaxT));
	mAreaTWater->setValue(shownedArea);

	mAreaTGrass->setRange(1, qMax(static_cast<size_t>(minMaxNbr), tailleMaxT));
	mAreaTGrass->setValue(shownedArea);

	mBerryPourcentage->setRange(0, ratio); // pourcentage de berry de 0-100
	mBerryPourcentage->setValue(50);

	mNature->setRange(0, ratio); // pourcentage de berry de 0-100
	mNature->setValue(50);

	mMaxHealth->setRange(1, qMax(static_cast<size_t>(minMaxNbr), maxItems));
	mMaxHealth->setValue(minMaxNbr);

	mTikSpeed->setRange(1, qMax(static_cast<size_t>(minMaxNbr), maxItems));
	mTikSpeed->setValue(minTik);

	mPSpeed->setRange(1, qMax(static_cast<size_t>(minMaxNbr), maxItems));
	mPSpeed->setValue(minTik);

	mMeteo->setRange(1, 4);
	mMeteo->setValue(1);

	QFormLayout * layout{ new QFormLayout };
	layout->addRow("Number of Fire Type Pokemon", mNbrOfPFire);
	layout->addRow("Number of Water Type Pokemon", mNbrOfPWater);
	layout->addRow("Number of Grass Type Pokemon", mNbrOfPGrass);
	
	layout->addRow("Area of Fire type Pokemon", mAreaTFire);
	layout->addRow("Area of Water type Pokemon", mAreaTWater);
	layout->addRow("Area of Grass type Pokemon", mAreaTGrass);
	layout->addRow("% Berry", mBerryPourcentage); 
	layout->addRow("Nature", mNature);
	
	layout->addRow("Max health", mMaxHealth);
	layout->addRow("Simulation Speed", mTikSpeed);

	layout->addRow("Meteo", mMeteo);

	mTextMeteo->setText("1. Normal \n2. Night\n3. Day\n4. Rain\n");

	layout->addWidget(mTextMeteo);
	layout->addWidget(mEvolution);

	setLayout(layout);
}

size_t QParameters::getNbrOfPFire() const
{
	return static_cast<size_t>(mNbrOfPFire->value());
}

size_t QParameters::getNbrOfPWater() const
{
	return static_cast<size_t>(mNbrOfPWater->value());
}

size_t QParameters::getNbrOfPGrass() const
{
	return static_cast<size_t>(mNbrOfPGrass->value());
}

size_t QParameters::getAreaTFire() const
{
	return static_cast<size_t>(mAreaTFire->value());
}

size_t QParameters::getAreaTWater() const
{
	return static_cast<size_t>(mAreaTWater->value());
}

size_t QParameters::getAreaTGrass() const
{
	return static_cast<size_t>(mAreaTGrass->value());
}

size_t QParameters::getBerryPourcentage() const
{
	return static_cast<size_t>(mBerryPourcentage->value());
}

size_t QParameters::getNature() const
{
	return static_cast<size_t>(mNature->value());
}

size_t QParameters::getMaxHealth() const
{
	return static_cast<size_t>(mMaxHealth->value());
}

size_t QParameters::getTikSpeed() const
{
	return static_cast<size_t>(mTikSpeed->value());
}

qreal QParameters::getPokemonSpeed() const
{
	return static_cast<qreal>(mPSpeed->value());
}

size_t QParameters::getMeteo() const
{
	return static_cast<size_t>(mMeteo->value());
}

bool QParameters::getEvolutionstate() const
{
	return mEvolution->isChecked();
}
