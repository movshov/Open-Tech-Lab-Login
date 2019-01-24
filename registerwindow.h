#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QtWidgets>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QRegExpValidator>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>

const QString RULES = "D:/QT5/Projects/Lab_Login/Rules.txt";

class RegisterWindow : public QWidget{
    Q_OBJECT

    static const int startXPos = 300;
    static const int startYPos = 100;

public:
    QPushButton * regButton, * cancelButton;
    QLineEdit * nameDialog;
    QLabel * nameLabel, * text;
    QFont font, rulesFont;
    QPlainTextEdit * rulesDisplay;

    RegisterWindow(QWidget * parent = 0);
    void openWindow();
    void closeWindow();
    void showRules();
};

#endif // REGISTERWINDOW_H
