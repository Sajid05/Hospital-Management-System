#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include "Person.h"


using namespace std;


class Employee : public Person
{
    private:
        int id = 1;
        int salary;
        int password = 0;



    public:
        Employee();
        Employee(string newFirstName, string newLastName, string newAddress, string newMobileNo, int newYear_of_birth, string newGender, int salary);
        ~Employee();

        void setID(int id)
        {
                this->id = id ;
        }
        int getID()
        {
                return id;
        }

        void setSalary(int salary)
        {
                this->salary = salary;
        }
        int getPassword()
        {
                return password;
        }
        void setPassword(int val)
        {
                password = val;
        }

        void setInformation();
        void showInformation();

};

#endif // EMPLOYEE_H
