#ifndef GPASSWORD_H
#define GPASSWORD_H

#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <vector>

using namespace std;

class GPassword : public QWidget
{
    Q_OBJECT
public:
    explicit GPassword(QWidget *parent = 0, int minimumLength = 0, int maximumLength = 8);

    ~GPassword();
signals:

public:

    QString getPassword();

    void setMinimumLength(int value);

    void setMaximumLength(int value);

    void setLength(int length);

public slots:
    void enterNumber();
    void clearAll();
    void clear();
    void afficherErreur();

signals:
    void changed(QString value);

private:
    QVBoxLayout* layoutMain;
    QHBoxLayout* layoutTop;
    QHBoxLayout* layoutMiddle;
    QHBoxLayout* layoutBot;
    QGridLayout* layoutKeyboard;

    QLabel* label;
    QLabel* errorLabel;
    QLineEdit* lineEdit;
    vector <QPushButton*> pushButtons;

    QPushButton* clearButton;
    QPushButton* allClearButton;

    QString password;
    int minimumLength;
    int maximumLength;
    int passwordLength;
};

#endif // GPASSWORD_H
