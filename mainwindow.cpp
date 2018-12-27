#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signinwindow.h"

/**
 * @brief Student::Student
 *      Constructor for Student Class
 * @param id
 *      The student's ODIN ID number.
 * @param name
 *      The student's name.
 * @param timeIn
 *      The time at which the student first checks in the room.
 * @param timeOut
 *      The time at which the student checks out of the room.
 */

Student::Student(QString id, QString name, QTime timeIn, QTime timeOut, QDate date){
    this->id = id;
    this->name = name;
    this->date = date;
    this->signInTime = timeIn;
    this->signOutTime = timeOut;
    this->next = nullptr;   //set next pointer to null.
    this->previous = nullptr;   //set previous pointer to null.
}

/**
 *  @brief Student::~Student
 *          Destructor for the Student node. If there is a next ptr, delete it.
 */

Student::~Student(){
    if(next != nullptr) delete next;
}

/**
 * @brief Stack::Stack
 *      Constructor for the Stack.
 */
Stack::Stack(){
    this->head = nullptr;
    this->tail = nullptr;
}

/**
* @brief Stack::Stack
*       Copy constructor for Stack.
* @param toCopy
*       toCopy is the new Stack we want to use.
*/
Stack::Stack(const Stack & toCopy){

}
/**
 *  @brief Stack::~Stack
 *      Destructor for the class containing the list of students that have visited the room.
 */
Stack::~Stack(){
    saverecords();  //save the stack to Records.txt
    if(head != nullptr) delete head;
}

/**
 *  @brief Stack::add
 *      Adds a student to the list of students that have checked in/out of the room.
 *  @param toAdd
 *      The student node being added to the list.
 */
//FUNCTION: Inserts new node at the head of the stack always.
void Stack::add(Student * toAdd){
    if(head == nullptr){ //no list exists yet.
        head = toAdd;
        tail = head;
        return;
    }
    tail->next = toAdd; //set next pointer.
    toAdd->previous = tail; //set previous pointer.
    tail = toAdd;   //move tail over.
    //toAdd->next = head; //set new nodes next to head;
    //head = toAdd;   //reassign head as the new node.
    return;
}

/**
*   @brief Stack::containsId
*       Determine if the student is already on the list with a given ID number and check to see whether they are checking in or out.
*   @param id
*       Student's id number
*   @return
*       True if the student is on the list but timeOut variable is null.
*       False if the student is on the list and timeIn and timeOut are both not null.
**/
bool Stack::containsId(QString id){
    if(head == nullptr)
        return false;
    else {
        Student * current = tail;   //start at the end of the list.(last instance of person should appear first).
        while(current != nullptr){
            if(current->id.compare(id) == 0){   //if we found the student we are looking for.
                if((current->signInTime.isValid()) && (current->signOutTime.isValid()))   //if timeIn and timeOut already exist.
                    return false;
                else if((current->signInTime.isValid()) && (current->signOutTime.isNull())) {   //if timeIn exists but timeOut is NULL.
                    return true;
                }
            }
            current = current->previous;    //traverse towards the front of the list.
        }
        return false;   //student was never found.
    }
}


/**
*   @brief Stack::containsName
*       Determine if the student is already on the list with a given name and check to see whether they are checking in or out.
*   @param id
*       Student's name.
*   @return
*       True if the student is on the list but timeOut variable is null.
*       False if the student is on the list and timeIn and timeOut are both not null.
**/
bool Stack::containsName(QString name){
    if(head == nullptr)
        return false;
    else {
        Student * current = head;
        while(current != nullptr){
            if(current->name.toLower().compare(name.toLower()) == 0){   //if we found the student we are looking for.
                if((current->signInTime.isValid()) && (current->signOutTime.isValid()))   //if timeIn and timeOut already exist.
                    return false;
                else if((current->signInTime.isValid()) && (current->signOutTime.isNull())) {   //if timeIn exists but timeOut is NULL.
                    return true;
                }
            }
            current = current->next;
        }
           return false;   //student was never found.
    }
}

/**
* @brief Stack::removeFromList
*       Will remove everyone from the list.
*/
void Stack::removeFromList(){

    Student * current = head;

    while(current){
        Student * temp = current->next;
        current->previous = nullptr;
        current->next = nullptr;
        delete current;
        current = temp; //since head was already moved 1 forward.
    }
    head = nullptr;
    tail = nullptr;

}
/**
* @brief Stack::saverecords
*       Save the stack of sign in/out records to a .txt file.
* @param head
*       Is a doubly linked list of student sing in/out records.
*/
void Stack::saverecords(){
    if(!head) return;
    QString fileName = LOG_DIR; //"D:/QT5/Projects/Lab_Login/SavedRecords/"
    fileName += QDateTime::currentDateTime().toString("MMMM_yyyy"); //gets month and year.
    fileName += ".txt"; //append .csv file extension to name
    QFile data(fileName);
    if(data.open(QFile::WriteOnly | QFile::Append)){
        QTextStream out(&data); //converting everything to Text so QTextream will work.
        //Don't use QDataStream, it gets garbage symbols into .txt file.
        Student * current = head;
        QString empty = QString::fromUtf8(" ____ ");
        QString delimiter1 = QString::fromUtf8(" -> ");
        QString delimiter2 = QString::fromUtf8(" : ");
        /*
        QString Newline = QString::fromUtf8("'\n'");
        out << "Name";
        out << delimiter1;
        out << "Date";
        out << delimiter2;
        out << "Sign In";
        out << delimiter2;
        out << "Sign out";
        out <<'\n';
        out <<"--------------------------------------------------";
        out <<'\n';
        */
        while(current){
            out << current->name;   //record name.
            out << delimiter1;
            out << current->date.toString("MMMM dd, yyyy");
            out << delimiter2;
            if(current->signInTime.isNull()==true){
                out << empty;
            }
            else{
                 out << current->signInTime.toString("hh:mm a"); //record time in.
            }
            out << delimiter2;
            if(current->signOutTime.isNull()==true){
                out << empty;
            }
            else {
                out << current->signOutTime.toString("hh:mm a"); //record time out.
            }
            out << '\n';    //new line.
            current = current->next;
        }
        data.flush();
        data.close(); //close the opened file.
    }
}

/**
* @brief Stack::monthlysave
*       Saves the stack into a .txt file if one month has passed.
* @param head
*       Is a doubly linked list of sign In/Out records.
*/
void Stack::monthlysave(QString SaveMonth){
    QString fileName = LOG_DIR; //"D:/QT5/Projects/Lab_Login/SavedRecords/"
    fileName += SaveMonth;   //given from monthlysave in MainWindow class.
    fileName += QDateTime::currentDateTime().toString("_yyyy"); //gets month and year.
    fileName += ".txt"; //append .csv file extension to name
    QFile data(fileName);

    if(data.open(QFile::WriteOnly | QFile::Append )){
        QTextStream out(&data); //converting everything to Text so QTextream will work.
        //Don't use QDataStream, it gets garbage symbols into .txt file.
        Student * current = head;
        QString empty = QString::fromUtf8(" ____ ");
        QString delimiter1 = QString::fromUtf8(" -> ");
        QString delimiter2 = QString::fromUtf8(" : ");
        /*
        QString Newline = QString::fromUtf8("'\n'");
        out << "Name";
        out << delimiter1;
        out << "Date";
        out << delimiter2;
        out << "Sign In";
        out << delimiter2;
        out << "Sign out";
        out <<'\n';
        out <<"--------------------------------------------------";
        out <<'\n';
*/
        while(current){
            out << current->name;   //record name.
            out << delimiter1;
            out << current->date.toString("MMMM dd, yyyy");
            out << delimiter2;
            if(current->signInTime.isNull()==true){
                out << empty;
            }
            else{
                out << current->signInTime.toString("hh:mm a"); //record time in.
            }
            out << delimiter2;
            if(current->signOutTime.isNull()==true){
                out << empty;
            }
            else {
                out << current->signOutTime.toString("hh:mm a"); //record time out.
            }
            out << '\n';    //new line.
            current = current->next;
        }

        data.flush();
        data.close(); //close the opened file.
        removeFromList();   //Clean the Stack.
    }

}

/**
 * @brief RegInfo::RegInfo
 *      Constructor for an instance of a Registered student/tutor
 * @param id
 *      The id number of the student/tutor
 * @param name
 *      The name of the student/tutor
 */
RegInfo::RegInfo(QString id, QString name) {
  this->id = id;
  this->name = name;
  this->next = nullptr;
}

/**
 * @brief RegInfo::~RegInfo
 *      Destructor for a Registered student/tutor. Deletes the next node in the list.
 */
RegInfo::~RegInfo() {
  if (next) delete next;
}

/**
*   @brief Database::Database
*   Constructor for Register database. Reads in students from RegInfo.dat and adds students
*   to another data structure.
*/
Database::Database(){   //Constructor.
    tableSize = 21;
    table = new RegInfo *[tableSize];
    QString id, name;

    for(int i=0; i< tableSize; ++i){    //set each ptr to null.
        table[i] = nullptr;
    }

    QFile data(ACCESS_FILE);    //open file containing people who have access.
    if(data.open(QFile::ReadOnly)) {    //read in students from RegInfo.dat
       QTextStream inFile(&data);
        while(!inFile.atEnd()){
            QString line = inFile.readLine();
            QStringList fields = line.split(',');
            if(fields.size() == 2){
                id = fields.takeFirst();
                name = fields.takeFirst();
            }
            addStudent(id, name);
        }
    }
}

/**
*  @brief Database::~Database
*       Destructor for Database class. Writes the database to a file
*       and cleans up the hashtable.
*/
Database::~Database(){
    for(int i = 0; i < tableSize; ++i){ //traverse hash table and delete
        if(table[i]) delete table[i];   //remove info.
    }
}

/**
*   @brief Database::addStudent
*       Adds a student to the hashtable database.
*   @param
*       The student's ODIN ID.
*   @param
*       The student's name.
*/
void Database::addStudent(QString id, QString name){
    int key = hash(id);
    if (table[key] == nullptr) {
      table[key] = new RegInfo(id, name);
    }
    else {
      RegInfo * current = table[key];
      while (current->next) {
        current = current->next;
      }
      current->next = new RegInfo(id, name);
    }
   // writeOut();
}

/**
 * @brief Database::getStudent
 *      Gets the registered student info from the hash table
 * @param id
 *      The id to hash
 * @return
 *      The student's registered info
 */
RegInfo * Database::getStudent(QString id) {
  int key = hash(id);   //hash id

  if (table[key] != nullptr) { //ensure list at table entry is not empty
    RegInfo * current = table[key];
    //traverse list until id is or is not found
    while (current && current->id.compare(id) != 0) {
      current = current->next;
    }
    if (current) { //if the node with the id is found
      return current; //return the node
    }
  }
  return nullptr;
}

/**
 * @brief Database::hash
 *      Hash function. Takes the value of each char and multiplies the ascii value by 7
 *      powered to the string length minus the char index minus 1. Adds that value to
 *      a sum integer and returns the value modulus the table size.
 *      i.e. Sigma from 0 to string length ( digit * |7 ^ (string length - charPos - 1)| )
 * @param id
 *      The id string to hash
 * @return
 *      The hashed value
 */
int Database::hash(QString id) {
  int sum = 0;
  int length = id.length();

  if (id.compare("") == 0)  //If the string is NULL
    return -1;              //Nothing to hash

  for (int i = 0; i < length; ++i)
    sum += id.at(i).digitValue() * abs(pow(float(7),    //sum the string char * 7 powered to string length - index - 1
           float((length - i - 1))));                   //absolute value to prevent negative numbers

  return sum % tableSize; //return the sum modulous the hash table size
}


MainWindow::MainWindow(){
    signInWindow = new SignInWindow(this);

    errorText = new QLabel(this);
    errorText->resize(400,40);
    errorText->hide();

    //This is the table of students who have signed in.
    numberOnList = 0;
    theList = new QTableWidget(0, 4, this); //QTableWidget(row,col,parent).
    buildTable(numberOnList);

    signInWindow->openWindow();

    timer = new QTimer(this);
    timer->start(86400000); //This will only run once every 24 hours.
    //timer->start(60000);    //msec in 1 minute used for testing purposes.
    //timer->start(30000);    //msec in 30sec used for testing purposes.

    //setup signal and slot
    connect(timer, SIGNAL(timeout()),this, SLOT(checkmonth()));
    connect(signInWindow->loginButton, SIGNAL(clicked()), this, SLOT(signInLogInButtonPressed()));
    connect(signInWindow->loginDialog, SIGNAL(returnPressed()), this, SLOT(signInLogInButtonPressed()));

    setWindowTitle("PDX Open Tech Lab Sign In");
    resize(XRES,YRES);  //resize to default x and y res.
    showFullScreen();   //sets to full screen mode.

}
//CheckMonth slots
/**
* @brief MainWindow::checkmonth
*       Used to check if one month has passed. If so, then save the stack of the previous month.
*/

void MainWindow::checkmonth(){
    if(!stack.head) return; //if there is no list.
    QString day = QDateTime::currentDateTime().toString("d");   //will return an integer as a String.
    if(day.compare("1")==0){   //it is a new month.
        QString checkmonth = QDate::currentDate().toString("M"); //get the current Month.
        QString SaveMonth = nullptr; //reset before reassigning.

        if(checkmonth.compare("1")==0){ //check if month is January.
            SaveMonth = "December"; //save as month prior.
        }
        else if(checkmonth.compare("2")==0){    //check if month is February.
            SaveMonth = "January"; //save as month prior.
        }else if(checkmonth.compare("3")==0){   //check if month is March.
            SaveMonth = "February"; //save as month prior.
        }else if(checkmonth.compare("4")==0){   //check if month is April.
            SaveMonth = "March"; //save as month prior.
        }else if(checkmonth.compare("5")==0){   //check if month is May.
            SaveMonth = "April"; //save as month prior.
        }else if(checkmonth.compare("6")==0){   //check if month is June.
            SaveMonth = "May"; //save as month prior.
        }else if(checkmonth.compare("7")==0){   //check if month is July.
            SaveMonth = "June"; //save as month prior.
        }else if(checkmonth.compare("8")==0){   //check if month is August.
            SaveMonth = "July"; //save as month prior.
        }else if(checkmonth.compare("9")==0){   //check if month is September.
            SaveMonth = "August"; //save as month prior.
        }else if(checkmonth.compare("10")==0){  //check if month is October.
            SaveMonth = "September"; //save as month prior.
        }else if(checkmonth.compare("11")==0){  //check if month is November.
            SaveMonth = "October"; //save as month prior.
        }else if(checkmonth.compare("12")==0){  //check if month is December.
            SaveMonth = "November";
        }
        stack.monthlysave(SaveMonth);
        numberOnList = 0;   //after saveing reset list #.
        updateTable();
        return;
    }
    else{
        return; //day was not the 1st of the month.
    }
}
/*
 * Sign-in Window SLOTS
 */
void MainWindow::signInLogInButtonPressed() {
  if (signInWindow->loginDialog->cursorPosition() < 9) {
    signInWindow->closeWindow();
    signInWindow->openWindow();
    errorText->move(1080, 525);
    errorText->setText("Please enter a valid\n9-digit ODIN ID");
    errorText->show();
    return;
  }
  errorText->hide();
  id = signInWindow->loginDialog->text();

    RegInfo * student = database.getStudent(id);
    if (!student) { //if id is not in the database
      //theList->hide();
      signInWindow->closeWindow();
      signInWindow->openWindow();
      errorText->move(1080, 525);
      errorText->setText("You do not have access to be in this room");
      errorText->show();
      return;
    }
    else { //if the id is registered, go to class window
      if (stack.containsId(student->id)==true) {  //they are on the list but have not checked out.
            Student * current = stack.tail; //grab the end of the list.
            while(current != nullptr){
            if(current->name.toLower().compare(student->name.toLower()) == 0){ //we found the student.
               current->signOutTime = QTime::currentTime(); //set sign_out_time.
               signInWindow->closeWindow(); //close old window.
               updateTable();
               signInWindow->openWindow();  //open new updated window.
               return;
              }
            current = current->previous;    //travese from end to front of stack.
            }
      }
      name = student->name;
      id = student->id;
      signInTime = QTime::currentTime();    //get the current time.
      date = QDate::currentDate();  //get the current date.
      ++numberOnList;
      stack.add(new Student(id, name, signInTime, signOutTime, date));
   //   theList->hide();
      updateTable();
      signInWindow->closeWindow();
      signInWindow->openWindow();
      return;
    }

}
void MainWindow::buildTable(int rows) {
  theList->removeRow(rows);
  theList->insertRow(rows);
  theList->move(400, 100);
  theList->resize(850, 300);
  theList->setHorizontalHeaderLabels(QStringList() << "Name" << "Date" << "Sign-in Time" << "Sing-Out Time");
  theList->setEditTriggers(QAbstractItemView::NoEditTriggers);
  theList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  theList->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  theList->setColumnWidth(0, 200);
  theList->setColumnWidth(1, 200);
  theList->setColumnWidth(2, 225);
  theList->setColumnWidth(3, 200);
}

void MainWindow::updateTable() {
  theList->clearContents();
  buildTable(numberOnList);
  Student * current = stack.head;
  int row = 0;
  while (current != nullptr) {
    theList->setItem(row, 0, new QTableWidgetItem(current->name));
    theList->setItem(row, 1, new QTableWidgetItem(current->date.toString("MMMM dd, yyyy")));
    theList->setItem(row, 2, new QTableWidgetItem(current->signInTime.toString("hh:mm a")));
    theList->setItem(row, 3, new QTableWidgetItem(current->signOutTime.toString("hh:mm a")));
    current = current->next;
    ++row;
  }
}















