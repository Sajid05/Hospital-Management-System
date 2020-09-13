#include <iostream>
#include <conio.h>
#include "Admin.h"
#include "Doctor.h"
#include "Receptionist.h"
#include "Patient.h"
#include <windows.h>
#include "MakeBox.h"


using namespace std;


void menu();
void logIn();
void admin_access();
void doctor_access();
void receptionist_access();
void visitor_access();

int main()
{

    menu();


    return 0;
}


void menu()
{
    Table Box; int choice;
    string s = "         SAGITTARIUS HOSPITAL LIMITED ";
    int index = 0;
    while(s[index] != '\0')
    {
        cout << s[index++];
        Sleep(50);
    }
    cout << "                      " << endl;
    cout << "                      " << endl;
    cout << "                      " << endl;
    cout << "Press any key to continue . . . " << endl;


    getchar();
    system("CLS");
    do
    {
        string menu[5] = {"        Menu        ", " 1. Log In          ", " 2. About Us        ", " 3. Contact Us      ", " 4. Exit            "};
        Box.upperLine(20); // make box of width 30

        for(int k = 0; k < 5; k++)
        {
            cout << char(179) << menu[k] << char(179) << endl; // printing menu options

            Box.lowerLine(20);
        }


        for(int i = 0; i < 16; i++) cout << "_ ";

        cout << endl << endl;


        cout << " Enter Your Choice :  ";


        cin >> choice;

        system("CLS");
        switch(choice)
        {
        case 1:
            logIn();
            system("pause");
            system("CLS");
            break;
        case 2:
            for(int i = 0; i < 10; i++) cout << endl;
            cout << "                                " ;
            for(int i = 0; i < 48; i++) cout << "_ ";
            cout << endl << endl;
            cout << "Sagittarius Hospital Limited has over two decades of experience in the healthcare sector, and is known for providing quality healthcare and valuable experience to all domestic and international patients. Our healthcare offerings are supported by a team of compassionate and dedicated medical professionals who have rich knowledge and experience in their respective domains." << endl << endl;
            cout << "                                " ;
            for(int i = 0; i < 48; i++) cout << "_ ";
            cout << endl << endl;
            system("pause");
            system("CLS");

            break;
        case 3:
            cout << endl << endl << endl;
            cout << "                                " ;
            for(int i = 0; i < 48; i++) cout << "_ ";
            cout << endl << endl;
            cout << "                                " ; cout << "For Any Medical Emergency Contact Us: " << endl;
            cout << "                                " ; cout << "Email Address : info@sagittariusltd.com" << endl;
            cout << "                                " ; cout << "Mobile No     : +880132536845" << endl;
            cout << "                                " ;
            for(int i = 0; i < 48; i++) cout << "_ ";
            cout << endl << endl;
            system("pause");
            system("CLS");
            break;
        case 4:
            break;
        default:
            cout << "Invalid Input!" << endl;
            break;
        }
    }
    while(choice != 4);
}



void logIn()
{


    int choice;
    Table Box;

    do
    {
        string menu[6] = {"            Option            ", " 1. Log in as Admin           ", " 2. Log in as Doctor          ", " 3. Log in as Receptionist    ", " 4. Log in as Visitor         ", " 5. Back                      "};

        Box.upperLine(30); // make box of width 30

        for(int k = 0; k < 6; k++)
        {
            cout << char(179) << menu[k] << char(179) << endl; // printing menu options

            Box.lowerLine(30);
        }


        for(int i = 0; i < 16; i++) cout << "_ ";

        cout << endl << endl;


        cout << " Enter Your Choice :  ";


        cin >> choice;

        system("CLS");


        switch(choice)
        {
        case 1:
            admin_access();
            system("pause");
            system("CLS");
            break;
        case 2:
            doctor_access();
            system("pause");
            system("CLS");

            break;
        case 3:
            receptionist_access();
            system("pause");
            system("CLS");

            break;
        case 4:
            visitor_access();
            system("pause");
            system("CLS");
        case 5:
            break;
        default:
            system("CLS");
            cout << "Invalid Input! Choose Again " << endl;

            break;
        }
    }
    while(choice != 5);
}


void admin_access()
{
    int choice;
    Admin admin;
    Table Box;
    string password;
    getchar();
    cout << endl << " Enter Password  : ";
    char c = ' ';
    while(c != 13)
    {
        c = getch();
        if(c != 13)
        {
            password += c;
            cout << "*";
        }
    }

    if(admin.verifyPassword(password))
    {
        system("CLS");
        Box.upperDoubleLayerLine(14);
        cout << char(186) << "Access Granted" << char(186) << endl;
        Box.lowerDoubleLayerLine(14);

        do
        {
            cout << endl;
            Box.upperLine(35);
            cout << char(179) << "              Options              " << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 1. Create New Department" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 2. Show All Departments" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 3. Add New Doctor" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 4. Update Details of Doctor" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 5. Delete Doctor" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 6. Search Doctors by Department" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 7. Show All Doctors" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 8. Add New Receptionist" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 9. Update Details of Receptionist" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 10. Delete Receptionist" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 11. Show All Receptionists" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 12. Show All Patients" << char(179) << endl;
            Box.lowerLine(35);
            cout << char(179) << setw(35) << left << " 13. Back" << char(179) << endl;
            Box.lowerLine(35);



            for(int i = 0; i < 16; i++) cout << "_ ";
            cout << endl << endl;
            cout << "Enter choice      : " ;
            cin >> choice;

            system("CLS");

            switch(choice)
            {
            case 1:
                admin.createDepartment();

                system("pause");
                system("CLS");

                break;

            case 2:
                admin.showDepartment();

                system("pause");
                system("CLS");

                break;

            case 3:
                admin.addDoctor();

                system("pause");
                system("CLS");

                break;

            case 4:
                admin.updateDoctor();

                system("pause");
                system("CLS");

                break;

            case 5:
                admin.deleteDoctor();

                system("pause");
                system("CLS");

                break;

            case 6:
                admin.searchInDepartment();

                system("pause");
                system("CLS");

                break;

            case 7:
                admin.showDoctor();

                system("pause");
                system("CLS");

                break;

            case 8:
                admin.addReceptionist();

                system("pause");
                system("CLS");

                break;

            case 9:
                admin.updateReceptionist();

                system("pause");
                system("CLS");

                break;

            case 10:
                admin.deleteReceptionist();

                system("pause");
                system("CLS");

                break;

            case 11:
                admin.showReceptionist();

                system("pause");
                system("CLS");

                break;

            case 12:
                admin.showPatient();

                system("pause");
                system("CLS");

                break;

            case 13:

                break;

            default:

                system("CLS");
                cout << "Invalid Input! Choose Again " << endl;

                break;

            }


        }
        while(choice != 13);
    }
    else
    {
        cout << endl << endl << " Invalid Password" << endl << endl;
    }
}
void doctor_access()
{
    Table Box;

    int given_id;
    int given_password;
    int choice;
    cout << "Enter Doctor ID : ";
    cin >> given_id;
    cout << "Enter Password  : ";
    //cin >> given_password;
    char c = ' ';
    string password;
    while(c != 13)
    {
        c = getch();
        if(c != 13)
        {
            password += c;
            cout << "*";
        }
    }
    given_password = stoi(password);

    Doctor doc;
    int check_id = doc.verifyLogin(given_id, given_password);

    if(check_id == -1)
    {
        cout << endl << endl << "Invalid ID/Password" << endl;
        cout << endl;
        return;
    }

    else
    {
        system("CLS");
        Box.upperDoubleLayerLine(14);
        cout << char(186) << "Access Granted" << char(186) << endl;
        Box.lowerDoubleLayerLine(14);
    }


    do
    {

        cout << endl;
        Box.upperLine(35);
        cout << char(179) << "              Options              " << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 1. Personal Profile" << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 2. Change Password" << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 3. Show Assigned Patients" << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 4. Show Full History of Patient" << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 5. Prescribe Patient" << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 6. Back" << char(179) << endl;
        Box.lowerLine(35);

        for(int i = 0; i < 16; i++) cout << "_ ";
        cout << endl << endl;
        cout << "Enter choice      : " ;
        cin >> choice;

        system("CLS");

        switch(choice)
        {
        case 1:
            doc.personalInformation(given_id);
            system("pause");
            system("CLS");
            break;
        case 2:
            doc.changePassword(given_id);
            system("pause");
            system("CLS");
            break;
        case 3:
            doc.showPatient(given_id);
            system("pause");
            system("CLS");
            break;
        case 4:
            doc.showPreviousHistory(given_id);
            system("pause");
            system("CLS");
            break;
        case 5:
            doc.prescribePatient(given_id);
            system("pause");
            system("CLS");
            break;
        case 6:
            break;
        default:
            system("CLS");
            cout << "Invalid Input! Choose Again " << endl;
            break;
        }
    }
    while(choice != 6);

}


void receptionist_access()
{
    Table Box;
    int given_id;
    int given_password;
    int choice;
    cout << "Enter Receptionist ID : ";
    cin >> given_id;
    cout << "Enter Password        : ";
    //cin >> given_password;
    char c = ' ';
    string password;
    while(c != 13)
    {
        c = getch();
        if(c != 13)
        {
            password += c;
            cout << "*";
        }
    }
    given_password = stoi(password);

    Receptionist rec;
    int check_id = rec.verifyLogin(given_id, given_password);

    if(check_id == -1)
    {
        cout << endl << endl << "Invalid ID/Password" << endl;
        cout << endl;
        return;
    }
    else
    {
        system("CLS");
        Box.upperDoubleLayerLine(14);
        cout << char(186) << "Access Granted" << char(186) << endl;
        Box.lowerDoubleLayerLine(14);
    }

    do
    {
        cout << endl;
        Box.upperLine(35);
        cout << char(179) << "              Options              " << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 1. Personal Profile" << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 2. Change Password" << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 3. Add Patient" << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 4. Back" << char(179) << endl;
        Box.lowerLine(35);

        for(int i = 0; i < 16; i++) cout << "_ ";
        cout << endl << endl;
        cout << "Enter choice      : " ;
        cin >> choice;

        system("CLS");

        switch(choice)
        {
        case 1:
            rec.personalInformation(given_id);
            system("pause");
            system("CLS");
            break;
        case 2:
            rec.changePassword(given_id);
            system("pause");
            system("CLS");
            break;
        case 3:
            rec.addPatient();
            system("pause");
            system("CLS");
            break;
        case 4:
            break;
        default:
            system("CLS");
            cout << "Invalid Input! Choose Again " << endl;
            break;
        }
    }
    while(choice != 4);

}


void visitor_access()
{
    Table Box;
    int choice;
    Patient pat;
    do
    {
        cout << endl;
        Box.upperLine(35);
        cout << char(179) << "              Options              " << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 1. Find Doctors " << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 2. Find Your Prescription" << char(179) << endl;
        Box.lowerLine(35);
        cout << char(179) << setw(35) << left << " 3. Back" << char(179) << endl;
        Box.lowerLine(35);

        for(int i = 0; i < 16; i++) cout << "_ ";
        cout << endl << endl;
        cout << "Enter choice      : " ;
        cin >> choice;

        system("CLS");

        switch(choice)
        {
        case 1:
            pat.findDoctors();
            system("pause");
            system("CLS");
            break;
        case 2:
            pat.findPrescription();
            system("pause");
            system("CLS");
            break;
        case 3:
            break;
        default:
            system("CLS");
            cout << "Invalid Input! Choose Again " << endl;
            break;
        }
    }
    while(choice != 3);
}

