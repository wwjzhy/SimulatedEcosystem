#include "AnimalButton.h"
#include "Animal.h"

AnimalButton::AnimalButton(QWidget *parent, shared_ptr<Animal>animal)
	: QPushButton(parent)
	, ui(new Ui::AnimalButtonClass())
{
	ui->setupUi(this);


	int animalSize = 0;
	int x = 0;
	int y = 0;
	
	//setGeometry(animal->GetPosition().GetX(), animal->GetPosition().GetY(), , 500);
	//setStyleSheet("QPushButton{background-image:" + animal->GetPicturePath() + ";}");
	
	if (animal != NULL) {
		if (animal->GetAge() == Age::Child) {
			animalSize = AnimalConstants::CHILD_DISTANCE;
		}
		else if (animal->GetAge() == Age::Adult) {
			animalSize = AnimalConstants::ADULT_DISTANCE;
		}
		setStyleSheet("QWidget{image:url(" + animal->GetPicturePath() + ");border:dashed; }");
		x = animal->GetPosition().GetX();
		y = animal->GetPosition().GetY();
	}
	this->setGeometry(x, y, animalSize, animalSize);
}

AnimalButton::~AnimalButton()
{
	delete ui;
}
