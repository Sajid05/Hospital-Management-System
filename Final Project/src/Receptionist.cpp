#include "Receptionist.h"
#include "Employee.h"
#include "Patient.h"
#include "MakeBox.h"



Receptionist::Receptionist()
{

}

Receptionist::Receptionist(string newFirstName, string newLastName, string newAddress, string newMobileNo, int newYear_of_birth, string newGender, int newSalary) : Employee(newFirstName, newLastName, newAddress, newMobileNo, newYear_of_birth, newGender, newSalary)
{
    int current_id;
    ifstream in_receptionist("Receptionist.txt");
    if(in_receptionist.is_open())
    {
        Receptionist receptionist;
        while(in_receptionist.read((char *)&receptionist, sizeof(receptionist)))
        {

            current_id = receptionist.getID();

        }
        in_receptionist.close();
        setID(current_id + 1);
    }
}

Receptionist::~Receptionist()
{

}

void operator >> (istream &input, Receptionist &receptionist)
{
    receptionist.setInformation();
}

int Receptionist::verifyLogin(int given_id, int password)
{
    Table Box;
    ifstream in_receptionist("Receptionist.txt");
    if(!in_receptionist.is_open())
    {
        cout << endl << endl;
        Box.upperDoubleLayerLine(35);
        cout << char(186) << "STATUS : Receptionist Not Added Yet" << char(186) << endl;
        Box.lowerDoubleLayerLine(35);
        return -1;
    }
    else
    {
        Receptionist rec;
        while(in_receptionist.read((char *)&rec, sizeof(rec)))
        {
            if(rec.getID() == given_id && rec.getPassword() == password)
            {
                return given_id;
            }
        }
        return -1;
    }
}


void Receptionist::changePassword(int given_id)
{
    int new_password; Table Box;
    cout << endl << "Enter New Password    : " ;
    cin >> new_password;

    ifstream in_receptionist("Receptionist.txt");
    ofstream out_receptionist("temp.txt", ios::app);

    Receptionist receptionist;
    Receptionist point_to_receptionist = receptionist;
    while(in_receptionist.read((char *)&receptionist, sizeof(receptionist)))
    {

        if(given_id == receptionist.getID())
        {
            point_to_receptionist = receptionist;
            point_to_receptionist.setPassword(new_password);
            out_receptionist.write((char *)&point_to_receptionist, sizeof(point_to_receptionist));
        }
        else
        {
            out_receptionist.write((char *)&receptionist, sizeof(receptionist));
        }

    }

    out_receptionist.close();
    in_receptionist.close();



    if(remove("Receptionist.txt") == 0 && rename("temp.txt", "Receptionist.txt") == 0)
    {
        system("CLS"); cout << endl;
        Box.upperDoubleLayerLine(38);
        cout << char(186) <<"STATUS : Password Updated Successfully" << char(186) << endl;
        Box.lowerDoubleLayerLine(38);
    }
    else
    {
        Box.upperDoubleLayerLine(34);
        cout << char(186) <<"STATUS : Could Not Update Password" << char(186) << endl;
        Box.lowerDoubleLayerLine(34);
        remove("temp.txt");
    }


}


void Receptionist::setInformation()
{

    Employee::setInformation();


    cout << endl;

}

void Receptionist::showInformation()
{
    Employee::showInformation();
}



void Receptionist::personalInformation(int given_id)
{
    Table Box;
    Receptionist receptionist;
    system("CLS");
    ifstream in_receptionist("Receptionist.txt");
    cout << "         Your Information   " << endl;
    while(in_receptionist.read((char *)&receptionist, sizeof(receptionist)))
    {
        if(given_id == receptionist.getID())
        {
            cout << endl;
            receptionist.showInformation();
            cout << char(179) << setw(12) << left << " Password" << " | " << setw(25) << left << receptionist.getPassword() << char(179) << endl;
            Box.lowerLine(40);
        }

    }

}

void Receptionist::addPatient()
{
    Table Box;
    Patient pat(1);
    cin >> pat;

    ofstream outpatient("Patient.txt", ios::app);
    outpatient.write((char *)&pat, sizeof(pat));
    outpatient.close();

    string seperate_doc_file;
    seperate_doc_file = to_string(pat.getAssignedDoctor());
    ofstream out_assigned_patient(seperate_doc_file + "_assigned_patients.txt", ios::app);
    out_assigned_patient.write((char *)&pat, sizeof(pat));
    out_assigned_patient.close();

    ofstream individual_slip_flie("Slip No " + to_string(pat.getSlip_no()) + ".txt", ios::app);
    individual_slip_flie.write((char *)&pat, sizeof(pat));
    individual_slip_flie.close();

    system("CLS");
    cout << "         Patient Information     " << endl;
    pat.showInformation();
    cout << endl;
    for(int i = 0; i < 16; i++) cout << "_ ";
    cout << endl;
    cout << endl << "System Generated Slip Code : " <<  pat.getSlip_code() << endl << endl;

    Box.upperDoubleLayerLine(38);
    cout << char(186) << "STATUS : Patient Successfully Assigned" << char(186) << endl;
    Box.lowerDoubleLayerLine(38);



}

