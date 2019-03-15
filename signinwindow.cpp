#include "signinwindow.h"

SignInWindow::SignInWindow(QWidget * parent) : QWidget(parent){
    font.setPointSize(30);  //set font to size 32.
    font.setBold(true); //set font to be bolded.

    buttonFont.setPointSize(20);    //set font of button to be 20.
    buttonFont.setBold(true);   //set button font to be bolded.

    loginText = new QLabel("Welcome! Please scan your PSU ID barcode or type in your ODIN ID below", parent);
    loginText->move(200, 425);
    loginText->resize(1300, 50);
    loginText->setFont(buttonFont);
    loginText->hide();

    loginButton = new QPushButton("Sign-in", parent);
    loginButton->move(670, 500);
    loginButton->resize(200, 80);
    loginButton->hide();
    loginButton->setFont(buttonFont);

    loginDialog = new QLineEdit(parent);
    loginDialog->move(470, 500);
    loginDialog->resize(200, 80);
    loginDialog->setPlaceholderText("ODIN ID");
    loginDialog->setMaxLength(9);
    loginDialog->setValidator(new QRegExpValidator(QRegExp("[0-9]{9}")));
    loginDialog->hide();

    logo = new QLabel("<img src='/var/tutor-data/psulogo.gif' />", parent);
    logo->resize(300,100);

    title = new QLabel("Open Tech Lab Sign-IN/OUT", parent);
    title->setFont(font);
    title->move(420, 0);
    title->resize(600, 150);
  }

  void SignInWindow::openWindow() {
    loginText->show();
    loginButton->show();
    loginDialog->show();
    loginDialog->setFocus();
  }

  void SignInWindow::closeWindow() {
    loginText->hide();
    loginButton->hide();
    loginDialog->hide();
    loginDialog->clear();
  }






