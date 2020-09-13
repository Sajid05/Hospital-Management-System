#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <bits/stdc++.h>

using namespace std;


class Person
{
    private:
        char first_name[20];
        char last_name[20];
        int year_of_birth;
        char address[30];
        char mobileNo[14];
        char gender[10];


    public:
        Person();
        Person(string newFirstName, string newLastName, string newAddress, string newMobileNo, int newYear_of_birth, string newGender);

        ~Person();

        char* getName()
        {
                return strcat(strcat(first_name, " "), last_name);
        }
        char* getFirstName()
        {
                return first_name;
        }
        char* getLastName()
        {
                return last_name;
        }
        void setAddress(string address)
        {
                strcpy(this->address, address.c_str());

        };
        void setMobileNo(string mobileNo)
        {
                strcpy(this->mobileNo, mobileNo.c_str());

        };

        void setInformation();
        void showInformation();





};

#endif // PERSON_H
