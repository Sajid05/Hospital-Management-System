#include "Employee.h"
#include <fstream>
#include <ctime>
#include "Person.h"
#include "MakeBox.h"

Employee::Employee()
{
    srand(time(0));
    for(int i = 1, j = 1; i <= 5; i++, j *= 10)
    {
        password += ((rand() % (58 - 49) + 1) * j);
    }
    //password = 111;
}

Employee::Employee(string newFirstName, string newLastName, string newAddress, string newMobileNo, int newYear_of_birth, string newGender, int salary):Person(newFirstName, newLastName, newAddress, newMobileNo, newYear_of_birth, newGender)
{
    this->salary = salary;
    srand(time(0));
    for(int i = 1, j = 1; i <= 5; i++, j *= 10)
    {
        password += ((rand() % (58 - 49) + 1) * j);
    }
    //password = 111;
}

Employee::~Employee()
{

}


void Employee::setInformation()
{
    Person::setInformation();
    cout << setw(25) << left << "Enter Salary" <<  " : ";
    cin >> salary;


}

void Employee::showInformation()
{
    Table Box;
    Box.upperLine(40);
    cout << char(179) << setw(12) << left << " ID" << " | " << setw(25) << left << id << char(179) << endl;
    Box.lowerLine(40);
    Person::showInformation();
    cout << char(179) << setw(12) << left << " Salary" << " | " << setw(25) << left << salary << char(179) << endl;
    Box.lowerLine(40);
}
