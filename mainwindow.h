#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QLabel>
#include <QTime>
#include <QTableWidget>
#include <QHeaderView>
#include <cmath>
#include <QTimer>
#include <QDebug>
#include <QFileInfo>


using namespace std;

const QString ACCESS_FILE = "D:/QT5/Projects/Lab_Login/Access.txt";
const QString LOG_DIR = "D:/QT5/Projects/Lab_Login/SavedRecords/";

class SignInWindow; //window below table of current students in the room.
class RegisterWindow;   //window to have users accept Lab Rules and Regulations.

struct Student {    //struct for Student Info.
    Student(QString, QString, QTime, QTime, QDate); //constructor.
    ~Student(); //destructor.

    QString id, name;
    QTime signInTime, signOutTime;
    QDate date;
    Student * next;
    Student * previous;
};

struct Stack {
    Stack();    //constructor.
    Stack(const Stack&);    //copy constructor.
    ~Stack();   //destructor.
    void add(Student*); //add a student to the stack. 
    bool containsId(QString);
    bool containsName(QString); //checks LLL to see if they are already on the list.
    void removeFromList();
    void saverecords();  //record the stack into a .txt file if the program is forcefully shut off.   
    void monthlysave(QString, QString);  //if one month has passed save the stack into a .txt file named "that month + year.txt"
    //EX: "December_2019.txt", "November_2019.txt"
    Student * head; //head pointer.
    Student * tail; //tail pointer.

};


struct RegInfo {
    RegInfo(QString, QString);  //constructor.
    ~RegInfo(); //destructor.
    QString id;
    QString name;
    RegInfo * next;
};

struct Database {
    Database(); //constructor.
    ~Database();    //destructor.
    void addStudent(QString, QString);
    RegInfo * getStudent(QString);

private:
    int tableSize;
    RegInfo ** table;
    int hash(QString);
};
//Resolution.
const int XRES = 1366, YRES = 768;

class MainWindow : public QMainWindow{
    Q_OBJECT

    int numberOnList;
    QString id, name;
    QTime signInTime, signOutTime;
    QDate date;
    QLabel * errorText;
    QTableWidget * theList;
    Stack stack;
    Database database;
    SignInWindow * signInWindow;
    RegisterWindow * registerWindow;
    QTimer *timer;


    void buildTable(int);   //build the table.
    void updateTable();     //update the already built table.
    //void checkmonth(Stack stack);   //check if one month has passed.


private slots:
    void signInLogInButtonPressed();

    void registerRegisterButtonPressed();
    void registerCancelButtonPressed();
    void registerIDDialogEntered();

    void checkmonth();      //slots wrapper for checkmonth(stack).

public:
    MainWindow();
};

#endif // MAINWINDOW_H
