#include "Person.h"
#include <ctime>
#include <fstream>
#include "MakeBox.h"


Person::Person()
{

}

Person::Person(string newFirstName, string newLastName, string newAddress, string newMobileNo, int newYear_of_birth, string newGender)
{

    strcpy(this->first_name, newFirstName.c_str());
    strcpy(this->last_name, newLastName.c_str());
    strcpy(this->address, newAddress.c_str());
    strcpy(this->mobileNo, newMobileNo.c_str());
    this->year_of_birth = newYear_of_birth;
    strcpy(this->gender, newGender.c_str());

}

Person::~Person()
{

}

void Person::setInformation()
{
    cout << setw(25) << left << "Enter First Name" <<  " : "; cin >> first_name;
    cout << setw(25) << left << "Enter Last Name" <<  " : "; cin >> last_name;
    cout << setw(25) << left << "Enter Address" <<  " : "; cin >> address;
    cout << setw(25) << left << "Enter Mobile No" <<  " : "; cin >> mobileNo;
    cout << setw(25) << left << "Enter Year of Birth" <<  " : "; cin >> year_of_birth;
    cout << setw(25) << left << "Enter Gender" <<  " : "; cin >> gender;

}



void Person::showInformation()
{
    Table Box;
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    int length_first_name = strlen(first_name);
    int length_last_name = strlen(last_name);

    cout << char(179) << setw(12) << left << " Name" << " | " << setw(length_first_name) << left << first_name << " " << setw(length_last_name) << left << last_name << setw(40 - 12 - 4 + 1 - length_first_name - length_last_name) << right << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Address" << " | " << setw(25) << left << address << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Mobile No." << " | " << setw(25) << left << mobileNo << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Age" << " | " << setw(25) << left << (1900 + timePtr->tm_year) - year_of_birth << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Gender" << " | " << setw(25) << left << gender << char(179) << endl;
    Box.lowerLine(40);


}
