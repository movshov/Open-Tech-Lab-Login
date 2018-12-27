Version 2.0 of Lab_Login Program

An electronic sign-in application for the open tech lab
at Portland State University.

Author: Bar Movshovich

Description:

The purpose of this application is to allow students that have been
granted access by Bart Massey, who currently owns the room, to be able
to record what day and times they have been inside the room.

The students need only to scan their PSU access badge or
manually type in their 9-digit ODIN number into the program to sing_in and sign_out.
The date of when they sign_in and sign_out is automatically recorded. The
list of people who have used the program are shown in a scroll down
menu that cannot be altered.

GRANTING ACCESS:
    The students that have access to the room can be found in the file "Access.txt".
    To add new students to use the program you must add them to this text file in the
    format of their 9-digit number followed by a comma (,) and the name of the student.
    This file should only be altered by the Lab Manager (Sharon Strohmeyer) a.k.a "Eve"
    or by the Lab Owner (Bart Massey).


AUTO SAVED RECORDS:
    Once the program is shut-down the program automatically records the list
    of students that signed_in regardless of whether they have signed_out and
    saves that list of records into a text file of the current month and year
    An example would look like so , EX: "December_2018.txt". The file can be
    located in the directory "SavedRecords".
    The format of the file is as follows:

    Name -> Date : Sign_in : Sign_out

    If the program has not been shutdown for over a month it will automatically record
    all entries into a txt file and clean the screen. That month's records can be located
    in a directory called "SavedRecords". If a crash/shutdown has happened before during
    that month a txt file will already exists in this directory. After the month has passed
    this file gets appended with the rest of the month's records.
    The format of the file is as follows:

    Name -> Date : Sign_in : Sign_out


Download/Build Instructions:

you can download the latest stable release at:

https://github.com/movshov/Open-Tech-Lab-Login

BUILD INSTRUCTIONS:
    Some modifications will need to be made for the program to work with your own directories.

    In mainwindow.h on line 19 you will need to specify the file path for your "Access.txt" file.
        Ex: const QString ACCESS_FILE = "D:/QT5/Projects/Lab_Login/Access.txt";

    In mainwindow.h on line 20 you will need to specify the file path for your directory "SavedRecords".
        EX: const QString LOG_DIR = "D:/QT5/Projects/Lab_Login/SavedRecords/";

This application was written in C++ using the Qt5 frameworks. Make sure you have the
required libraries before building. If running on Debian or a Debian derivative,
an easy way to do this would be to use the following command:

    # apt-get install qt5-default qt5-qmake

    or if using sudo

    $ sudo apt-get install qt5-default qt5-qmake

In the top-level directory, issue the command:

    $ qmake -makefile
    $ make

And then to run the program, simple issue:

    $./Lab_Login


