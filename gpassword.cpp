#include "gpassword.h"
#include <QDebug>
#include <QTime>

GPassword::GPassword(QWidget *parent, int minimumLength, int maximumLength) :
    QWidget(parent)
{
    //on initialise la taille du mot de passe à -1 pour signifier qu'elle n'a pas été définie
    this->passwordLength = -1;
    this->minimumLength = minimumLength;
    this->maximumLength = maximumLength;

    //layouts
    this->layoutMain = new QVBoxLayout(this);
    this->layoutTop = new QHBoxLayout(this);
    this->layoutMiddle = new QHBoxLayout(this);
    this->layoutKeyboard = new QGridLayout(this);
    this->layoutBot = new QHBoxLayout(this);

    this->layoutMain->addLayout(this->layoutTop);
    this->layoutMain->addLayout(this->layoutMiddle);
    this->layoutMiddle->addLayout(this->layoutKeyboard);
    this->layoutMain->addLayout(this->layoutBot);

    this->layoutMiddle->setSpacing(0);

    //components
    this->label = new QLabel("Mot de passe: ", this);
    this->lineEdit = new QLineEdit(this);
    this->lineEdit->setEnabled(false);

    this->layoutTop->addWidget(this->label);
    this->layoutTop->addWidget(this->lineEdit);

    this->clearButton = new QPushButton("C",this);
    this->allClearButton = new QPushButton("AC",this);
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(allClearButton, SIGNAL(clicked()), this, SLOT(clearAll()));

    this->errorLabel = new QLabel("Mot de passe inccorect!", this);
    this->errorLabel->hide();

    this->errorLabel->setStyleSheet("color: red");
    this->layoutBot->addWidget(this->errorLabel);


    QStringList digits;
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    int rIndex;
    for(int i = 0; i < 10; i++)
    {
        digits.append(QString::number(i));
    }

    for(int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if(x==3 && y==0)
            {
                this->layoutKeyboard->addWidget(clearButton, x, y);
            }
            else if(x==3 && y==2)
            {
                this->layoutKeyboard->addWidget(allClearButton, x, y);
            }
            else
            {
                rIndex = qrand()%digits.size();
                QPushButton* button = new QPushButton(digits.takeAt(rIndex),this);
                this->pushButtons.push_back(button);
                this->layoutKeyboard->addWidget(button, x, y);
                connect(button, SIGNAL(clicked()), this, SLOT(enterNumber()));
            }
        }
    }

}

GPassword::~GPassword()
{
    qDebug()<<"GPassword::~GPassword()";
    delete this->layoutTop;
    delete this->layoutBot;
    delete this->layoutKeyboard;
    delete this->layoutMiddle;
    delete this->layoutMain;

    delete this->label;
    delete this->errorLabel;
    delete this->lineEdit;
    for(int i = 0; i < this->pushButtons.size(); i++)
    {
        delete pushButtons[i];
    }

    delete this->clearButton;
    delete this->allClearButton;
}

void GPassword::enterNumber()
{
    //on ajoute le caractère au mot de passe s'il ne contient pas déjà la taille maximum
    if((this->passwordLength>-1 && this->password.size()<this->passwordLength)||this->password.size()<this->maximumLength)
    {
        this->password+=((QPushButton*)sender())->text();
        this->lineEdit->setText(this->lineEdit->text()+'*');
        this->changed(this->password);
    }
}

void GPassword::clearAll()
{
    qDebug()<<"void GPassword::clearAll()";
    this->password = "";
    this->lineEdit->clear();
    this->changed(this->password);
}

void GPassword::clear()
{
    qDebug()<<"void GPassword::clear()";
    this->password.chop(1);
    QString content = this->lineEdit->text();
    content.chop(1);
    this->lineEdit->setText(content);
    this->changed(this->password);
}

void GPassword::afficherErreur()
{
    this->errorLabel->show();
}

void GPassword::setMaximumLength(int value)
{
    maximumLength = value;
}

void GPassword::setLength(int length)
{
    this->passwordLength = length;
}

void GPassword::setMinimumLength(int value)
{
    minimumLength = value;
}

QString GPassword::getPassword()
{
    return password;
}


