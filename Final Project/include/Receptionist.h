#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H
#include "Employee.h"
#include <iostream>



class Receptionist : public Employee
{
    public:
        Receptionist();
        Receptionist(string newFirstName, string newLastName, string newAddress, string newMobileNo, int newYear_of_birth, string newGender, int salary);
        ~Receptionist();

        friend void operator >> (istream &input, Receptionist &receptionist);

        int verifyLogin(int, int);
        void changePassword(int given_id);
        void personalInformation(int given_id);
        void setInformation();
        void showInformation();
        void addPatient();






};

#endif // RECEPTIONIST_H
