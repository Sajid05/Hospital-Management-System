#include "Patient.h"
#include "Doctor.h"
#include <ctime>
#include "MakeBox.h"

Patient::Patient(int flag) // when patient is called with an argument then this constructor in invoked, which increases the count of patient
{

    ifstream in_patient_count("Total_Patients.txt");

    int current_slip = 0;
    if(in_patient_count.is_open())
    {


        in_patient_count >> current_slip;

        in_patient_count.close();

        setSlip_no(current_slip + 1);
    }

    ofstream patient_count("Total_Patients.txt", ios::trunc);

    patient_count << current_slip + 1 << endl;

    patient_count.close();

    srand(time(0));
    for(int i = 1, j = 1; i <= 5; i++, j *= 10)
    {
       slip_code += ((rand() % (58 - 49) + 1) * j);
    }
   // slip_code = 111;

}

Patient::~Patient()
{
    //dtor
}

void operator >> (istream &input, Patient &pat)
{
    pat.setInformation();
}

void Patient::setInformation()
{
    Table Box;
    Person::setInformation();
    vector <int> hold_doctors; // holds the doctor of a department


    cout << setw(25) << left << "Enter Height (ft)" <<  " : ";
    cin >> height;
    cout << setw(25) << left << "Enter Weight (kg)" <<  " : ";
    cin >> weight;


    cout << setw(25) << left << "Enter Symptoms" <<  " : ";
    getchar();
    gets(symptoms);
    cout << setw(25) << left << "Diseases Suffered Before" <<  " : ";
    gets(diseases);
    cout << setw(25) << left << "Brought Earlier Slips?" <<  endl;
    cout << "   1. Yes" << endl;
    cout << "   2. No" << endl;
    cout << "  -> ";
    int choice, previous_slip;
    string all_old_slips;
    cin >> choice;
    while(choice != 2)
    {
        cout << setw(25) << left << "Enter Slip No" <<  " : ";
        cin >> previous_slip;
        all_old_slips = all_old_slips + "," +  to_string(previous_slip);

        cout << setw(25) << left << "Any more slips?" << endl;
        cout << "   1. Yes" << endl;
        cout << "   2. No" << endl;
        cout << "  -> ";
        cin >> choice;
    }

    all_old_slips += ","; //Comma separates the slip numbers

    setPreviousSlips(all_old_slips);


    string department;
    int is_file_empty; //flag



ll:
    is_file_empty = 0;
    ifstream in_department("Department.txt"); // Shows all departments
    while(getline(in_department, department))
    {
        if(!is_file_empty)
        {
            Box.upperLine(20);
            cout << char(179) << "   Department List  " << char(179) << endl;
            Box.lowerLine(20);
            is_file_empty = 1;
        }
        cout << char(179) << setw(20) << left << department << char(179) << endl;

        Box.lowerLine(20);
    }

    in_department.close();


    if(!is_file_empty) // Department.txt is empty
    {
        cout << endl;
        Box.upperDoubleLayerLine(32);

        cout << char(186)   <<  "STATUS : No Department Added Yet" << char(186) << endl;

        Box.lowerDoubleLayerLine(32);

    } // Shows all the department



    for(int i = 0; i < 16; i++) cout << "_ ";
    cout << endl << endl;

    cout << setw(25) << left << "Find Doctor From" <<  " : ";
    string given_department;
    cin >> given_department;

    ifstream in__department(given_department + ".txt");
    if(!in__department.is_open())
    {
        system("CLS");
        cout << "Department Name Misspelled, Enter Again!" << endl << endl;
        goto ll;
    }

    else
    {
        Doctor doc;


        int is_doctor_available = 0;

        while(in__department.read((char *)&doc, sizeof(doc)))
        {
            if(!is_doctor_available)
            {
                Box.upperLine(40);
                cout << char(179) << "Available Doctors From Given Department " << char (179) << endl;
                Box.lowerLine(40);
                cout << char(179) << setw(12) << left << " Doctor ID " << "|" << setw(27) << left << "      Doctor Name    " << char(179) << endl;
                Box.lowerLine(40);
                is_file_empty = 1;
                is_doctor_available = 1;
            }
            cout << char(179) << setw(12) << left << doc.getID() << "| " << setw(26) << left << doc.getName() << char(179) << endl;
            Box.lowerLine(40);

            hold_doctors.push_back(doc.getID());

        }

        for(int i = 0; i < 16; i++) cout << "_ ";
        cout << endl << endl;
        if(is_doctor_available != 1)
        {
            system("CLS");
            cout << endl << "No Doctor Available in This Department, Choose Another!" << endl;
            goto ll;
        }
        in__department.close ();

    }

    while(1)
    {
        vector <int> :: iterator it;
        cout << setw(25) << left << "Assign a Doctor ID" <<  " : ";
        cin >> assignedDoctor;


        it = find(hold_doctors.begin(), hold_doctors.end(), assignedDoctor); // finds if doctor id is presented in vector
        if(it == hold_doctors.end())
        {
            for(int i = 0; i < 16; i++) cout << "_ ";
            cout << endl << endl;
            cout << "Invalid Doctor ID, Select Again! " << endl << endl;
        }
        else
        {

            break;
        }
    }

    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    admit_day = timePtr->tm_mday;
    admit_month = 1 + timePtr->tm_mon;
    // admiy_year = 1900 + timePtr->tm_year;
    admit_year = (timePtr->tm_year) % 100; // to reduce length



}

void Patient::showInformation()
{
    Table Box;
    string admit_date = getAdmitDate();
    int length_date = admit_date.size();
    Box.upperLine(40);
    cout << char(179) << setw(12) << left << " Slip No" << " | " << setw(25) << left << slip_no << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Admit Date" << " | " << setw(length_date) << left << admit_date << setw(40 - 12 - 3 - length_date + 1) << right << char(179) << endl;
    Box.lowerLine(40);
    Person::showInformation();
    cout << char(179) << setw(12) << left << " Height" << " | " << setw(25) << left << height << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Weight" << " | " << setw(25) << left << weight << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Symptoms" << " | " << setw(25) << left << symptoms << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Old Disease" << " | " << setw(25) << left << diseases << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Doctor ID" << " | " << setw(25) << left << assignedDoctor << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(13) << left << " Prescription" << "| " << setw(25) << left << medicine << char(179) << endl;
    Box.lowerLine(40);
    cout << char(179) << setw(12) << left << " Tests" << " | " << setw(25) << left << suggestedTest << char(179) << endl;
    Box.lowerLine(40); // test and prescription will be added by doctor

}

void Patient::findDoctors()
{
    Table Box;
    ifstream in_doctor("Doctor.txt");
    ifstream in_department("Department.txt");
    string department;
    if(!in_doctor.is_open() || !in_department.is_open())
    {
        cout << endl;
        Box.upperDoubleLayerLine(28);
        cout << char(186)   <<  "STATUS : No Doctor Available" << char(186) << endl;
        Box.lowerDoubleLayerLine(28);
        cout << endl;

    }
    else
    {
        Doctor doc;
        int is_doctor_present = 0; // flag
        while(getline(in_department, department))
        {
            ifstream individual_department(department + ".txt");
            int is_file_empty = 0;
            int length_department = department.size();


            while(individual_department.read((char *)&doc, sizeof(doc)))
            {
                if(is_file_empty == 0)
                {
                    Box.upperLine(40);
                    cout << char(179) << "         Department : " << setw(length_department) << left << department << setw(40 - length_department - 22 + 1) << right << char(179) << endl;
                    Box.lowerLine(40);
                    cout << char(179) << setw(12) << left << " Doctor ID  " << "|" << setw(27) << left << "      Doctor Name    " << char(179) << endl;
                    Box.lowerLine(40);
                    is_file_empty = 1;
                }

                cout << char(179) << setw(12) << left << doc.getID() << "| " << setw(26) << left << doc.getName() << char(179) << endl;
                Box.lowerLine(40);
            }


            individual_department.close();

            cout << endl << endl;

        }

        for(int i = 0; i < 16; i++) cout << "_ ";
        cout << endl << endl;

        cout << "Find Details of Doctor?(Y/N)" << endl << "-> " ;
ll:
        char c;
        cin >> c;
        if(c == 'n' || c == 'N')
            return;
        else if(c == 'y' || c == 'Y')
        {
            system("CLS");
            cout << endl << "Enter a Department : ";
            cin >> department;


            ifstream individual_department(department + ".txt");
            is_doctor_present = 0; // flag
            Doctor doc;
            int length_department = department.size();
            while(individual_department.read((char *)&doc, sizeof(doc)))
            {
                if(is_doctor_present == 0)
                {
                    Box.upperLine(40);
                    cout << char(179) << "         Department : " << setw(length_department) << left << department << setw(40 - length_department - 22 + 1) << right << char(179) << endl;
                    Box.lowerLine(40);
                    is_doctor_present = 1;
                }
                cout << endl << endl;
                int length_first_name = strlen(doc.getFirstName());
                int length_last_name = strlen(doc.getLastName());
                Box.upperLine(40);
                cout << char(179) << setw(12) << left << " Name" << " | " << setw(length_first_name) << left << doc.getFirstName() << " " << setw(length_last_name) << left << doc.getLastName() << setw(40 - 12 - 4 + 1 - length_first_name - length_last_name) << right << char(179) << endl;
                Box.lowerLine(40);
                cout << char(179) << setw(12) << left << " Degree" << " | " << setw(25) << left << doc.getDegree() << char(179) << endl;
                Box.lowerLine(40);
                cout << char(179) << setw(12) << left << " Department" << " | " << setw(25) << left << doc.getDepartment() << char(179) << endl;
                Box.lowerLine(40);
                cout << char(179) << setw(12) << left << " Room No." << " | " << setw(25) << left << doc.getRoomNo() << char(179) << endl;
                Box.lowerLine(40);
            }

            individual_department.close();
            if(!is_doctor_present)
            {
                Box.upperDoubleLayerLine(28);
                cout << char(186)   <<  "STATUS : No Doctor Available" << char(186) << endl;
                Box.lowerDoubleLayerLine(28);
                cout << endl;

            }


        }

        else
        {
            cout << "Invalid Input, Try Again!" << endl << "-> ";
            goto ll;
        }

    }
    cout << endl;
}

void Patient::findPrescription()
{
    Table Box;
    int given_slip_no;
    int given_slip_code;
    cout << endl << "Enter Slip No of Patient       : ";
    cin >> given_slip_no;
    cout <<         "Enter Slip Code of Patient     : ";
    cin >> given_slip_code;
    system("CLS");
    ifstream individual_slip_flie("Slip No " + to_string(given_slip_no) + ".txt", ios::app);
    //ifstream in_patient("Patient.txt");

    if(!individual_slip_flie.is_open())
    {
        Box.upperDoubleLayerLine(26);
        cout << char(186)   <<  "STATUS : Patient Not Found" << char(186) << endl;
        Box.lowerDoubleLayerLine(26);
        cout << endl;
        return;
    }

    Patient pat;
    int is_record_found = 0;
    while(individual_slip_flie.read((char *)&pat, sizeof(pat)))
    {
        if(pat.getSlip_no() == given_slip_no && pat.getSlip_code() == given_slip_code)
        {
            is_record_found = 1;
            Box.upperDoubleLayerLine(36);
            cout << char(186)   <<  "      Most Recent Prescription      " << char(186) << endl;
            Box.lowerDoubleLayerLine(36);
            cout << endl;
            Box.upperLine(40);
            cout << char(179) << "         " << setw(10) << left <<  "Admit Date" << "|" << setw(10) << left << pat.getAdmitDate() << setw(40 - 20 - 9) << right << char(179) << endl;
            Box.lowerLine(40);
            cout << char(179) << "      " << setw(13) << left << "Release Date" << "|" << setw(10) << left << pat.getDischargeDate()  << setw(40 - 13 - 10 - 6) << right << char(179) << endl;
            Box.lowerLine(40);
            pat.showInformation();
            break;
        }
    }
    if(!is_record_found)
    {
        Box.upperDoubleLayerLine(26);
        cout << char(186)   <<  "STATUS : Patient Not Found" << char(186) << endl;
        Box.lowerDoubleLayerLine(26);
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
                        if(!is_previous_record_found)
                        {
                            Box.upperDoubleLayerLine(28);
                            cout << char(186)   <<  "      Old Prescription      " << char(186) << endl;
                            Box.lowerDoubleLayerLine(28);
                            cout << endl;
                        }
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

        }
    }
}


