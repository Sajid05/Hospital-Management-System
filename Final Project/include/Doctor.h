#ifndef DOCTOR_H
#define DOCTOR_H
#include <iostream>
#include "Employee.h"


using namespace std;

class Employee;

class Doctor : public Employee
{
    private:
        char department[20];
        char degree[20];
        char roomNo[10];
    public:
        Doctor();
        ~Doctor();

        friend void operator >> (istream &input, Doctor &doc);

        void setInformation();
        void showInformation();

        void setDegree(string degree)
        {
                strcpy(this->degree, degree.c_str());
        }
        void setDepartment(string department)
        {
                strcpy(this->department, department.c_str());
        }
        void setRoomNo(string roomNo)
        {
                strcpy(this->roomNo, roomNo.c_str());
        }
        char* getDegree()
        {
                return degree;
        }
        char* getDepartment()
        {
                return department;
        }
        char* getRoomNo()
        {
                return roomNo;
        }

        int verifyLogin(int given_id, int password);
        void changePassword(int given_id);
        void personalInformation(int given_id);
        void showPatient(int given_id);
        void prescribePatient(int given_id);
        void showPreviousHistory(int given_id);







};

#endif // DOCTOR_H
