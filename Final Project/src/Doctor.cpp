#include "Doctor.h"
#include <fstream>
#include <ctime>
#include "Patient.h"
#include "MakeBox.h"


Doctor::Doctor()
{
    int current_id = 1;
    ifstream in_doctor("Doctor.txt");
    if(in_doctor.is_open())
    {
        Doctor doc;
        while(!in_doctor.eof())
        {
            in_doctor.read((char *)&doc, sizeof(doc));
            current_id = doc.getID();

        }
        in_doctor.close();
        setID(current_id + 1);
    }

}

Doctor::~Doctor()
{

}

void operator >> (istream &input, Doctor &doc)
{
    doc.setInformation();
}

void Doctor::setInformation()
{

    Employee::setInformation();


    cout << setw(25) << left << "Enter Degree" << " : ";
    getchar();
    gets(degree);


    cout << setw(25) << left << "Enter Room No." << " : ";
    cin >> roomNo;
    cout << endl;

}




void Doctor::showInformation()
{
    Employee::showInformation();
    Table box;
    cout << char(179) << setw(12) << left << " Degree" << " | " << setw(25) << left << degree << char(179) << endl;
    box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Department" << " | " << setw(25) << left << department << char(179) << endl;
    box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Room No." << " | " << setw(25) << left << roomNo << char(179) << endl;
    box.lowerLine(40);

}



int Doctor::verifyLogin(int given_id, int password)
{
    Table Box;
    ifstream in_doctor("Doctor.txt");
    if(!in_doctor.is_open())
    {
        cout << endl << endl;
        Box.upperDoubleLayerLine(29);
        cout << char(186) << "STATUS : Doctor Not Added Yet" << char(186) << endl;
        Box.lowerDoubleLayerLine(29);
        return -1;
    }
    else
    {
        Doctor doc;
        while(in_doctor.read((char *)&doc, sizeof(doc)))
        {
            if(doc.getID() == given_id && doc.getPassword() == password)
            {
                return given_id;
            }
        }
        return -1;
    }
}

void Doctor::changePassword(int given_id)
{
    int new_password;
    Table Box;
    cout << endl << "Enter New Password    : " ;
    cin >> new_password;

    ifstream in_doctor("Doctor.txt");
    ofstream out_doctor("temp.txt", ios::app);

    Doctor doc;
    Doctor point_to_doc = doc;
    while(in_doctor.read((char *)&doc, sizeof(doc)))
    {

        if(given_id == doc.getID())
        {
            point_to_doc = doc;
            point_to_doc.setPassword(new_password);
            out_doctor.write((char *)&point_to_doc, sizeof(point_to_doc));
        }
        else
        {
            out_doctor.write((char *)&doc, sizeof(doc));
        }

    }

    out_doctor.close();
    in_doctor.close();



    if(remove("Doctor.txt") == 0 && rename("temp.txt", "Doctor.txt") == 0)
    {

        string department = point_to_doc.getDepartment();
        ofstream out_department("temp2.txt", ios::app);
        ifstream in_department(department + ".txt");
        while(in_department.read((char *)&doc, sizeof(doc)))
        {
            if(given_id != doc.getID())
            {
                out_department.write((char *)&doc, sizeof(doc));
            }
            else
            {
                out_department.write((char *)&point_to_doc, sizeof(point_to_doc)); // updating information inside the department file
            }
        }
        in_department.close();
        out_department.close();

        strcat(point_to_doc.getDepartment(), ".txt");



        if(remove(point_to_doc.getDepartment()) == 0 && rename("temp2.txt", point_to_doc.getDepartment()) == 0 )
        {
            system("CLS");
            cout << endl;
            Box.upperDoubleLayerLine(38);
            cout << char(186) <<"STATUS : Password Updated Successfully" << char(186) << endl;
            Box.lowerDoubleLayerLine(38);
        }
        else
        {
            Box.upperDoubleLayerLine(34);
            cout << char(186) <<"STATUS : Could Not Update Password" << char(186) << endl;
            Box.lowerDoubleLayerLine(34);
            remove("temp2.txt");
        }


    }


    else
    {
        Box.upperDoubleLayerLine(34);
        cout << char(186) <<"STATUS : Could Not Update Password" << char(186) << endl;
        Box.lowerDoubleLayerLine(34);
        remove("temp.txt");
    }


}

void Doctor::personalInformation(int given_id)
{
    Table Box;
    Doctor doc;
    system("CLS");
    ifstream in_doctor("Doctor.txt");
    cout << "         Your Information   " << endl;
    while(in_doctor.read((char *)&doc, sizeof(doc)))
    {
        if(given_id == doc.getID())
        {
            cout << endl;
            doc.showInformation();
            cout << char(179) << setw(12) << left << " Password" << " | " << setw(25) << left << doc.getPassword() << char(179) << endl;
            Box.lowerLine(40);
        }

    }

}


void Doctor::showPatient(int given_id)
{
    Table Box;
    string seperate_doc_file = to_string(given_id) + "_assigned_patients.txt";
    ifstream in_assigned_patient(seperate_doc_file);
    if(!in_assigned_patient.is_open())
    {

        Box.upperDoubleLayerLine(32);
        cout << char(186)   <<  "STATUS : No Patient Assigned Yet" << char(186) << endl;
        Box.lowerDoubleLayerLine(32);
        cout << endl;
    }
    else
    {
        Patient pat;
        cout << endl;
        int is_patient_assigned = 0; // flag
        while(in_assigned_patient.read((char *)&pat, sizeof(pat)))
        {
            if(!is_patient_assigned)
            {

                Box.upperLine(40);
                cout << char(179) << "          Assigned Patient List         " << char(179) << endl;
                Box.lowerLine(40);
                is_patient_assigned = 1;
            }
            pat.showInformation();
            cout << endl;

        }
        in_assigned_patient.close();
        if(!is_patient_assigned)
        {
            cout << endl;
            Box.upperDoubleLayerLine(32);

            cout << char(186)   <<  "STATUS : No Patient Assigned Yet" << char(186) << endl;
            Box.lowerDoubleLayerLine(32);
        }
    }

}

void Doctor::prescribePatient(int given_id)
{
    Table Box;
    int given_slip;
    cout << endl;
    cout << "Search Patient by Slip No. ";
    cin >> given_slip;
    cout << endl << endl;

    string seperate_doc_file = to_string(given_id) + "_assigned_patients.txt";

    ifstream in_assigned_patient(seperate_doc_file);
    ofstream out_assigned_patient("temp.txt", ios::app);
    int is_record_found = 0;
    if(!in_assigned_patient.is_open())
    {
        Box.upperDoubleLayerLine(36);
        cout << char(186)   <<  "STATUS : Could Not Prescribe Patient" << char(186) << endl;
        Box.lowerDoubleLayerLine(36);
        cout << endl;
        out_assigned_patient.close();
        remove("temp.txt");
    }
    else
    {
        Patient pat;
        Patient pointTopat = pat;
        while(in_assigned_patient.read((char *)&pat, sizeof(pat)))
        {

            if(given_slip == pat.getSlip_no())
            {
                for(int i = 0; i < 16; i++) cout << "_ ";
                cout << endl << endl;
                cout << setw(25) << left << "Prescribe Medicine" << " : ";
                string medicine;
                getchar();
                getline(cin, medicine);


                pat.setMedicine(medicine);
                cout << setw(25) << left << "Any Suggested Test?" << " : ";
                string suggestedTest;
                getline(cin, suggestedTest);


                pat.setSuggestedTest(suggestedTest);



                pointTopat = pat;
                is_record_found = 1;

                //out_assigned_patient.write((char *)&pat, sizeof(pat)); Prescribe patient is not written into assigned list anymore

            }
            else
            {
                out_assigned_patient.write((char *)&pat, sizeof(pat));
            }

        }


        out_assigned_patient.close();
        in_assigned_patient.close();

        if(is_record_found)
        {

            if(remove(seperate_doc_file.c_str()) == 0 && rename("temp.txt", seperate_doc_file.c_str()) == 0)
            {

                ofstream out_patient("temp2.txt", ios::app);
                ifstream in_patient("Patient.txt");

                string slip_file = "Slip No " + to_string(pointTopat.getSlip_no()) + ".txt";
                ofstream out_slip_no(slip_file, ios::trunc); // open in truncate mode to overwrite

                while(in_patient.read((char *)&pat, sizeof(pat)))
                {
                    if(pat.getSlip_no() == given_slip)
                    {
                        time_t t = time(NULL);
                        tm* timePtr = localtime(&t);
                        int date = timePtr->tm_mday;
                        int month = timePtr->tm_mon + 1;
                        int year = timePtr->tm_year % 100;
                        pointTopat.setDischargeDate(date, month, year);
                        //out_patient.write((char *)&pointTopat, sizeof(pointTopat)); //prescribe patient is discarded from current patient list
                        out_slip_no.write((char *)&pointTopat, sizeof(pointTopat));

                    }
                    else
                    {
                        out_patient.write((char *)&pat, sizeof(pat));
                    }
                }
                out_patient.close();
                in_patient.close();

                out_slip_no.close();

                if(remove("Patient.txt") == 0 && rename("temp2.txt", "Patient.txt") == 0)
                {
                    system("CLS");
                    cout << endl;
                    cout << "       Prescribed Patient Information    " << endl << endl;
                    pointTopat.showInformation();
                    cout << endl;
                    Box.upperDoubleLayerLine(40);
                    cout << char(186)   <<  "STATUS : Successfully Prescribed Patient" << char(186) << endl;
                    Box.lowerDoubleLayerLine(40);
                    cout << endl;



                }
                else
                {
                    Box.upperDoubleLayerLine(36);
                    cout << char(186)   <<  "STATUS : Could Not Prescribe Patient" << char(186) << endl;
                    Box.lowerDoubleLayerLine(36);
                    out_patient.close();
                    remove("temp2.txt");

                }

            }

            else
            {
                Box.upperDoubleLayerLine(36);
                cout << char(186)   <<  "STATUS : Could Not Prescribe Patient" << char(186) << endl;
                Box.lowerDoubleLayerLine(36);
            }
        }
        else
        {
            cout << endl << "Invalid ID" << endl;
            remove("temp.txt");
        }

    }
}



void Doctor::showPreviousHistory(int given_id)
{
    Table Box;
    cout << endl << "Enter Slip No of Patient : ";
    int slip_no;
    cin >> slip_no;
    string seperate_doc_file = to_string(given_id) + "_assigned_patients.txt";
    ifstream in_assigned_patient(seperate_doc_file);

    if(!in_assigned_patient.is_open())
    {
        Box.upperDoubleLayerLine(45);
        cout << char(186)   <<  "STATUS : Patient Has Not Been Assigned to You" << char(186) << endl;
        Box.lowerDoubleLayerLine(45);
        cout << endl;
        return;
    }

    Patient pat;
    int is_record_found = 0;
    while(in_assigned_patient.read((char *)&pat, sizeof(pat)))
    {
        if(pat.getSlip_no() == slip_no)
        {
            is_record_found = 1;
            break;
        }
    }
    if(!is_record_found)
    {
        Box.upperDoubleLayerLine(45);
        cout << char(186)   <<  "STATUS : Patient Has Not Been Assigned to You" << char(186) << endl;
        Box.lowerDoubleLayerLine(45);
        cout << endl;
        return;
    }
    else
    {
        string old_history = pat.getPreviousSlips();
        if(old_history == "None")
        {
            Box.upperDoubleLayerLine(50);
            cout << char(186)   <<  "STATUS : Patient Does Not Have Any Previous Record" << char(186) << endl;
            Box.lowerDoubleLayerLine(50);
            cout << endl;

        }
        else
        {
            string s = "Slip No ";
            int size_of_history = old_history.size();
            int is_previous_record_found = 0;
            int record_no = 1;
            cout << endl;
            for(int i = 1; i < size_of_history; i++) // index 0 contains a comma
            {

                if(old_history[i] != ',')
                {

                    s = s + old_history[i];

                }
                else
                {
                    s = s + ".txt";
                    ifstream slip_file(s);
                    if(slip_file.is_open())
                    {
                        if(!is_previous_record_found) system("CLS");
                        is_previous_record_found = 1;
                        Patient old_patient_record;

                        slip_file.read((char *)&old_patient_record, sizeof(old_patient_record));



                        cout << endl << endl;
                        cout << "         Record No. " << record_no++ << endl;
                        Box.upperLine(40);
                        cout << char(179) << "         " << setw(10) << left <<  "Admit Date" << "|" << setw(10) << left << old_patient_record.getAdmitDate() << setw(40 - 20 - 9) << right << char(179) << endl;
                        Box.lowerLine(40);
                        cout << char(179) << "      " << setw(13) << left << "Release Date" << "|" << setw(10) << left << old_patient_record.getDischargeDate()  << setw(40 - 13 - 10 - 6) << right << char(179) << endl;
                        Box.lowerLine(40);
                        Box.upperLine(40);
                        cout << char(179) << setw(12) << left << " Symptoms" << " | " << setw(25) << left << old_patient_record.getSymptoms() << char(179) << endl;
                        Box.lowerLine(40);
                        cout << char(179) << setw(12) << left << "Prescription" << " | " << setw(25) << left << old_patient_record.getMedicine() << char(179) << endl;
                        Box.lowerLine(40);
                        cout << char(179) << setw(12) << left << " Tests" << " | " << setw(25) << left << old_patient_record.getSuggestedTest() << char(179) << endl;
                        Box.lowerLine(40);
                        cout << endl;
                    }
                    s = "Slip No ";
                }



            }

            if(!is_previous_record_found)
            {
                cout << endl;
                Box.upperDoubleLayerLine(24);
                cout << char(186)   <<  "STATUS : No Record Found" << char(186) << endl;
                Box.lowerDoubleLayerLine(24);
                cout << endl;

            }
        }
    }

}


