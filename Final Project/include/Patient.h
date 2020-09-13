#ifndef PATIENT_H
#define PATIENT_H
#include <iostream>
#include "Person.h"

using namespace std;

class Patient : public Person
{
    private:

        int slip_no = 1;
        int slip_code;
        int admit_day;
        int admit_month;
        int admit_year;
        int discharge_date = -1;
        int discharge_month = -1;
        int discharge_year = -1;
        char prev_slip_no[50] = "None";
        int assignedDoctor = -1;
        char symptoms[50];
        char diseases[100];
        char suggestedTest[30] = "None";
        char medicine[60] = "None";
        float height;
        float weight;
    public:
        Patient(int);
        Patient(){};
        ~Patient();

        int getSlip_no()
        {
                return slip_no;
        }
        void setSlip_no(int slip_no)
        {
                this->slip_no = slip_no;
        }
        int getSlip_code()
        {
                return slip_code;
        }
        char* getAdmitDate()
        {
                string result;
                result = to_string(admit_day) + "/" + to_string(admit_month) + "/" +  to_string(admit_year);
                char* res = new char[10]; // memory must be created in heap as it's a local variable
                strcpy(res, result.c_str());
                return res;
        }
        char* getDischargeDate()
        {
                string result;
                result = to_string(discharge_date) + "/" + to_string(discharge_month) + "/" + to_string(discharge_year);
                char* res = new char[10]; // if memory is created in code section then return type should be const char*
                strcpy(res, result.c_str());
                return res;
        }
        void setDischargeDate(int discharge_date, int discharge_month, int discharge_year)
        {
                this->discharge_date = discharge_date;
                this->discharge_month = discharge_month;
                this->discharge_year = discharge_year;
        }
        int getAssignedDoctor()
        {
                return assignedDoctor;
        }
        void setAssignedDoctor(int val)
        {
                assignedDoctor = val;
        }
        void setSuggestedTest(string suggestedTest)
        {
                strcpy(this->suggestedTest, suggestedTest.c_str());
        }
        void setMedicine(string medicine)
        {
                strcpy(this->medicine, medicine.c_str());
        }
        void setPreviousSlips(string prev_slip_no)
        {
                strcpy(this->prev_slip_no, prev_slip_no.c_str());
        }
        char* getPreviousSlips()
        {
                return prev_slip_no;
        }
        char* getSymptoms()
        {
                return symptoms;
        }
        char* getMedicine()
        {
                return medicine;
        }
        char* getSuggestedTest()
        {
                return suggestedTest;
        }


        void setInformation();
        void showInformation();
        void findDoctors();
        void findPrescription();
        friend void operator >> (istream &input, Patient &pat);


};

#endif // PATIENT_H
