#include "Admin.h"
#include "Doctor.h"
#include "Receptionist.h"
#include <fstream>
#include "Patient.h"
#include "MakeBox.h"


Admin::Admin()
{

}

Admin::~Admin()
{

}

int Admin::verifyPassword(string chk_password)
{
    if(chk_password == this->password)
    {
        return 1;
    }
    return 0;
}

void Admin::createDepartment()
{
    Table Box;
    string department;
    cout << "Create a New Department : ";
    getchar();
    getline(cin, department);

    ofstream new_department(department + ".txt", ios::app); // new_department represents the individual department file with the created department name

    ifstream in_department_info("Department.txt"); // Department.txt holds all the department names
    string check_department; // used to check if department already exists in Department.txt
    int is_department_found = 0; // flag

    if(in_department_info.is_open())
    {

        while(getline(in_department_info, check_department))
        {
            if(check_department == department)
            {
                is_department_found = 1;
            }
        }

        in_department_info.close();
    }

    cout << endl;
    if(!is_department_found) // if department already does not exist
    {
        ofstream out_department_info("Department.txt", ios::app);
        out_department_info << department << endl; // put department in Department.txt
        out_department_info.close();

        Box.upperDoubleLayerLine(44);
        cout << char(186) <<  "STATUS : Successfully Created New Department" << char(186) << endl;
        Box.lowerDoubleLayerLine(44);

    }
    else
    {

        Box.upperDoubleLayerLine(34);
        cout << char(186)   <<  "STATUS : Department Already Exists" << char(186) << endl;
        Box.lowerDoubleLayerLine(34);
    }


    new_department.close();
    cout << endl;
}


void Admin::showDepartment()
{
    string department;
    int is_file_empty = 0; //flag
    Table Box;
    ifstream in_department("Department.txt");
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

    }

}


void Admin::addDoctor()
{

    Table Box;
    showDepartment(); // shows all the department available

    for(int i = 0; i < 16; i++) cout << "_ ";
    cout << endl << endl;

    Doctor doc;

    string department;
    cout << "Enter Department for Doctor : ";
    getchar();
    getline(cin, department);

    ifstream open_department(department + ".txt");
    if(!open_department.is_open())
    {
        Box.upperDoubleLayerLine(29);
        cout << char(186) << "STATUS : Department Not Found" << char(186) << endl;
        Box.lowerDoubleLayerLine(29);
    }
    else
    {

        system("CLS");
        cout << "     Enter Doctor Information     " << endl << endl;
        for(int i = 0; i < 25; i++) cout <<  "_ ";
        cout << endl << endl;

        cin >> doc;
        doc.setDepartment(department);


        ofstream out_doctor("Doctor.txt", ios::app);
        ofstream out_department(department + ".txt", ios::app);




        out_doctor.write((char *)&doc, sizeof(doc));
        out_department.write((char *)&doc, sizeof(doc));
        out_doctor.close();
        out_department.close();

        system("CLS");





        cout << endl;
        cout << "     Doctor Information     " << endl << endl;


        doc.showInformation();
        cout << endl;
        Box.upperDoubleLayerLine(34);
        cout << char(186)   <<  "STATUS : Doctor Added Successfully" << char(186) << endl;
        Box.lowerDoubleLayerLine(34);
        cout << endl;

        for(int i = 0; i < 16; i++) cout << "_ ";
        cout << endl;
        cout << endl << "System Generated Password : " << doc.getPassword() << endl << endl;
    }


}

void Admin::updateDoctor()
{
    Table Box;
    int given_id;
    cout << "Enter Doctor ID to be updated : ";
    cin >> given_id;
    cout << endl;

    ifstream in_doctor("Doctor.txt");
    ofstream out_doctor("temp.txt", ios::app); // temp.txt holds all the doctors along with the edited doctor, this will become Doctor.txt

    int is_record_found = 0; // flag
    if(!in_doctor.is_open())
    {
        out_doctor.close();
        in_doctor.close();
        remove("temp.txt");
        Box.upperDoubleLayerLine(44);
        cout << char(186)   <<  "STATUS : Could Not Update Doctor Information" << char(186) << endl;
        Box.lowerDoubleLayerLine(44);
        cout << endl;
    }
    else
    {
        Doctor doc;
        Doctor point_to_doc = doc; // point_to_doc holds the updated doctor
        int option;
        while(in_doctor.read((char *)&doc, sizeof(doc)))
        {

            if(given_id == doc.getID())
            {
                cout << endl << "  Current Information of Dr. " << doc.getLastName() << "   " << endl;
                doc.showInformation();
                cout << endl << endl;

ll:
                Box.upperLine(30);


                cout << char(179) << "  What do you want to update? " << char(179) << endl;
                Box.lowerLine(30);
                cout << char(179) << setw(30) << left << " 1. Address" << char(179) << endl;
                Box.lowerLine(30);
                cout << char(179) << setw(30) << left << " 2. Mobile No" << char(179) << endl;
                Box.lowerLine(30);
                cout << char(179) << setw(30) << left << " 3. Salary" << char(179) << endl;
                Box.lowerLine(30);
                cout << char(179) << setw(30) << left << " 4. Degree" << char(179) << endl;
                Box.lowerLine(30);
                cout << char(179) << setw(30) << left << " 5. Department" << char(179) << endl;
                Box.lowerLine(30);
                cout << char(179) << setw(30) << left << " 6. Room No" << char(179) << endl;
                Box.lowerLine(30);

                for(int i = 0; i < 16; i++) cout << "_ ";

                cout << endl << endl;;

                cout << "Proceed to Update? (Y/N)" << endl << "-> ";
                char c;
                cin >> c;
                if(c == 'n' || c == 'N')
                {
                    out_doctor.close();
                    in_doctor.close();
                    remove("temp.txt");
                    return;
                }


                cout << setw(28) << " Enter Your Choice"   << " : ";
                cin >> option;
                switch(option)
                {

                case 1:
                {

                    cout << setw(28) << " Enter New Address" << " : ";
                    string new_address;
                    getchar();
                    getline(cin, new_address);
                    doc.setAddress(new_address);
                    break;
                }
                case 2:
                {
                    cout << setw(28) << " Enter New Mobile Number" << " : ";
                    string new_mobileNo;
                    cin >> new_mobileNo;
                    doc.setMobileNo(new_mobileNo);
                    break;
                }
                case 3:
                {
                    cout << setw(28) << " Change Salary" << " : ";
                    int new_salary;
                    cin >> new_salary;
                    doc.setSalary(new_salary);
                    break;
                }
                case 4:
                {
                    cout << setw(28) << " Update Degree" << " : ";
                    string new_degree;
                    getchar();
                    getline(cin, new_degree);
                    doc.setDegree(new_degree);
                    break;
                }
                case 5:
                {
                    cout << setw(28) << " Update Department" << " : ";
                    string old_department;
                    string new_department;
                    old_department = doc.getDepartment();

                    getchar();
                    getline(cin, new_department);

                    if(old_department != new_department)
                    {


                        ifstream in_new_department(new_department + ".txt"); // to check if new department exists
                        ifstream in_old_department(old_department + ".txt");
                        ofstream out_old_department("temp2.txt", ios::app);

                        int is_record_found_2 = 0;

                        if(!in_new_department.is_open())
                        {
                            Box.upperDoubleLayerLine(33);
                            cout << char(186) << "STATUS: No Such Department Exists" << char(186) << endl;
                            Box.lowerDoubleLayerLine(33);
                            out_old_department.close();
                            out_doctor.close();
                            remove("temp.txt");
                            remove("temp2.txt");
                            return;
                        }



                        else
                        {


                            in_new_department.close();
                            ofstream out_new_department(new_department + ".txt", ios::app);


                            doc.setDepartment(new_department);

                            out_new_department.write((char *)&doc, sizeof(doc)); // writing doctor information in changed department file
                            out_new_department.close();


                            Doctor doctor_from_department;
                            while(in_old_department.read((char *)&doctor_from_department, sizeof(doctor_from_department)))
                            {

                                if(doc.getID() == doctor_from_department.getID()) // removing the updated doctor from old department
                                {
                                    is_record_found_2 = 1;


                                }

                                else
                                {

                                    out_old_department.write((char *)&doctor_from_department, sizeof(doctor_from_department)); // writing all the doctors except the updated one in temp2.txt which will be renamed as old department
                                }

                            }
                            out_old_department.close();
                            in_old_department.close();

                            if(is_record_found_2 == 1)
                            {

                                if(remove((old_department + ".txt").c_str()) == 0 && rename("temp2.txt", (old_department + ".txt").c_str()) == 0)
                                {
                                    Box.upperDoubleLayerLine(40);
                                    cout << char(186) << "STATUS : Successfully Changed Department" << char(186) <<endl;
                                    Box.lowerDoubleLayerLine(40);
                                }
                                else
                                {
                                    remove("temp2.txt");
                                    Box.upperDoubleLayerLine(35);
                                    cout << char(186) <<"Could Not Update Doctor Information" << char(186) << endl;
                                    Box.lowerDoubleLayerLine(35);

                                }
                            }
                            else
                            {
                                cout << endl << "Invalid ID" << endl;
                            }

                        }


                    }

                    break;
                }
                case 6:
                {
                    cout << setw(28) << " Change Room No." << " : ";
                    string new_roomNo;
                    cin >> new_roomNo;
                    doc.setRoomNo(new_roomNo);
                    break;
                }
                default:
                {

                    system("CLS");
                    cout << endl << "Invalid Input! Select Again" << endl << endl;
                    goto ll;
                    break;
                }

                }
                point_to_doc = doc;
                is_record_found = 1;
                out_doctor.write((char *)&point_to_doc, sizeof(point_to_doc));


            }
            else
            {

                out_doctor.write((char *)&doc, sizeof(doc));
            }


        }

        out_doctor.close();
        in_doctor.close();

        if(is_record_found == 1)
        {

            if(remove("Doctor.txt") == 0 && rename("temp.txt", "Doctor.txt") == 0)
            {
                system("CLS");
                cout << endl <<  "     Updated Doctor Information     " << endl;
                point_to_doc.showInformation();
                cout << endl;
                if(option != 5) // case 5 has been handled earlier
                {
                    string department = point_to_doc.getDepartment();
                    ofstream out_department("Temp.txt", ios::app);
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



                    if(remove(point_to_doc.getDepartment()) == 0 && rename("Temp.txt", point_to_doc.getDepartment()) == 0 )
                    {
                        Box.upperDoubleLayerLine(29);
                        cout << char(186) << "STATUS : Successfully Updated" << char(186) << endl;
                        Box.lowerDoubleLayerLine(29);
                    }


                }

            }
            else
            {
                Box.upperDoubleLayerLine(44);
                cout << char(186) <<"STATUS : Could Not Update Doctor Information" << char(186) << endl;
                Box.lowerDoubleLayerLine(44);
            }


        }
        else
        {
            remove("temp.txt");
            cout << endl << "Invalid ID" << endl;
        }
    }
}

void Admin::deleteDoctor()
{
    Table Box;
    int given_id;
    cout << "Enter ID of Doctor to be Deleted : ";
    cin >> given_id;
    cout << endl;
    ifstream in_doctor("Doctor.txt");
    ofstream out_doctor("temp.txt", ios::app);
    int is_record_found = 0; // flag
    if(!in_doctor.is_open())
    {
        Box.upperDoubleLayerLine(44);
        cout << char(186)   <<  "STATUS : Could Not Delete Doctor Information" << char(186) << endl;
        Box.lowerDoubleLayerLine(44);
        cout << endl;
        out_doctor.close();
        remove("temp.txt");
    }
    else
    {
        Doctor doc, point_to_doc;
        int changed_mind = 0;
        while(in_doctor.read((char *)&doc, sizeof(doc)))
        {

            if(given_id == doc.getID())
            {
                cout << "        Profile of Dr. " << doc.getLastName() << endl << endl;
                doc.showInformation();
                cout << endl;
                for(int i = 0; i < 16; i++) cout << "_ ";

                cout << endl << endl;
ll:
                cout << "Proceed To Delete? (Y/N)" << endl << "-> " ;
                char c;
                cin >> c;
                if(c != 'N' && c != 'n' && c != 'Y' && c != 'y')
                {
                    cout << endl;
                    goto ll;
                }
                if(c != 'Y' && c != 'y') // if admin changes his mind then do not delete doctor
                {
                    changed_mind = 1;
                    out_doctor.write((char *)&doc, sizeof(doc));
                }
                is_record_found = 1;
                point_to_doc = doc; // found doctor is not written on temp.txt
            }
            else
            {
                out_doctor.write((char *)&doc, sizeof(doc));
            }

        }

        out_doctor.close();
        in_doctor.close();

        if(changed_mind)
        {
            remove("temp.txt");
            cout << endl;
            return;
        }

        if(is_record_found)
        {

            Doctor doctor_from_department;
            ofstream out_department("temp2.txt", ios::app);
            ifstream in_department(strcat(point_to_doc.getDepartment(), ".txt"));
            while(in_department.read((char *)&doctor_from_department, sizeof(doctor_from_department)))
            {

                if(point_to_doc.getID() != doctor_from_department.getID()) // found doctor is not written on his modified department file
                {
                    out_department.write((char *)&doctor_from_department, sizeof(doctor_from_department));


                }



            }
            out_department.close();
            in_department.close();



            if(remove("Doctor.txt") == 0 && rename("temp.txt", "Doctor.txt") == 0 && remove(point_to_doc.getDepartment()) == 0 && rename("temp2.txt", point_to_doc.getDepartment()) == 0)
            {
                Box.upperDoubleLayerLine(29);
                cout << char(186) << "STATUS : Successfully Deleted" << char(186) << endl;
                Box.lowerDoubleLayerLine(29);
                cout << endl;
            }
            else
            {
                Box.upperDoubleLayerLine(32);
                cout << char(186) <<"STATUS : Could Not Delete Doctor" << char(186) << endl;
                Box.lowerDoubleLayerLine(32);
            }


        }
        else
        {
            remove("temp.txt");
            cout << endl << "Invalid ID" << endl << endl;
        }
    }
}

void Admin::searchInDepartment()
{
    showDepartment();
    Table Box;
    string department;
    cout << endl << "Enter Department Name : ";
    getchar();
    getline(cin, department);
    int length_department = department.size();
    system("CLS");
    ifstream doctor_in_department(department + ".txt");

    int is_file_empty = 0; // flag
    Doctor doc;

    if(!doctor_in_department.is_open())
    {
        Box.upperDoubleLayerLine(29);
        cout << char(186) <<"STATUS : Department Not Found" << char(186) << endl;
        Box.lowerDoubleLayerLine(29);
        return;

    }
    else
    {
        Doctor doc;

        while(doctor_in_department.read((char *)&doc, sizeof(doc)))
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

        doctor_in_department.close();

        if(!is_file_empty)
        {
            Box.upperDoubleLayerLine(43);
            cout << char(186) << "STATUS : No Doctor Found in This Department" << char(186) << endl;
            Box.lowerDoubleLayerLine(43);
            return;
        }

        for(int i = 0; i < 16; i++) cout << "_ ";
        cout << endl << endl;
        int detailed_search = 0;
ll:
        cout << "See Full Details of Doctor? (Y/N)" << endl << "-> ";
        char c;
        cin >> c;
        if(c != 'N' && c != 'n' && c != 'Y' && c != 'y')
        {
            cout << endl;
            goto ll;
        }
        if(c != 'n' && c != 'N') // if c is yes then go for details searching
        {
            detailed_search = 1;
        }
        else
        {
            return;
        }
        if(detailed_search)
        {


ll1:
            cout << endl << "Enter ID to See Full Details : " ;
            int id;
            cin >> id;
            ifstream in_department(department + ".txt");
            int is_doctor_found = 0; // flag
            while(in_department.read((char *)&doc, sizeof(doc)))
            {
                if(id == doc.getID())
                {
                    is_doctor_found = 1;
                    doc.showInformation();
                    cout << endl;
                    break;
                }

            }

            if(!is_doctor_found)
            {
                cout << "Invalid Input, Try Again!" << endl;
                goto ll1;
            }
            for(int i = 0; i < 16; i++) cout << "_ ";
            cout << endl << endl;;
ll2:
            cout << "Search Again? (Y/N)" << endl << "-> ";
            cin >> c;
            if(c != 'N' && c != 'n' && c != 'Y' && c != 'y')
            {
                cout << endl;
                goto ll2;
            }
            if(c != 'n' && c != 'N') // if c is yes then go again for details searching
            {
                cout << endl;
                goto ll1;
            }
            else
            {
                return;
            }
        }

    }
}


void Admin::showDoctor()
{
    Table Box;
    ifstream in_doctor("Doctor.txt");
    ifstream in_department("Department.txt");
    string department;
    if(!in_doctor.is_open() || !in_department.is_open())
    {
        cout << endl;
        Box.upperDoubleLayerLine(42);
        cout << char(186) << "STATUS : Could Not Show Doctor Information" << char(186) << endl;
        Box.lowerDoubleLayerLine(42);
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


            if(is_file_empty == 0)
            {
                Box.upperLine(40);
                cout << char(179) << "         Department : " << setw(length_department) << left << department << setw(40 - length_department - 22 + 1) << right << char(179) << endl;
                Box.lowerLine(40);
                cout << char(179) << "  No Doctor Present in This Department  " << char(179) << endl;
                Box.lowerLine(40);
            }
            individual_department.close();

            cout << endl << endl;

        }

        for(int i = 0; i < 16; i++) cout << "_ ";
        cout << endl << endl;

        cout << "Do You Want to Find Details of Doctors? (Y/N)" << endl << "-> " ;
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
            is_doctor_present = 0; // falg
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

                doc.showInformation();
                cout << endl;
            }
            if(!is_doctor_present)
            {
                Box.upperLine(40);
                cout << char(179) << "         Department : " << setw(length_department) << left << department << setw(40 - length_department - 22 + 1) << right << char(179) << endl;
                Box.lowerLine(40);
                Box.upperLine(40);
                cout << char(179) << "  No Doctor Present in This Department  " << char(179) << endl;
                Box.lowerLine(40);

            }
            individual_department.close();
            cout << endl << "Search for Another Department? (Y/N)" << endl << "-> ";
            goto ll;
        }

        else
        {
            cout << "Invalid Input, Try Again!" << endl << "-> ";
            goto ll;
        }

    }

}



void Admin::addReceptionist()
{

    Table Box;
    string newFirstName, newLastName, newAddress, newMobileNo, newGender;
    int newYear_of_birth, newSalary;
    cout << "     Enter Receptionist Information     " << endl << endl;
    for(int i = 0; i < 25; i++) cout <<  "_ ";
    cout << endl << endl;

    cout << setw(25) << left << "Enter First Name" << " : ";
    cin >> newFirstName;
    cout << setw(25) << left << "Enter Last Name" << " : ";
    cin >> newLastName;
    cout << setw(25) << left << "Enter Address" << " : ";
    cin >> newAddress;
    cout << setw(25) << left << "Enter Mobile No" << " : ";
    cin >> newMobileNo;
    cout << setw(25) << left << "Enter Year of Birth" << " : ";
    cin >> newYear_of_birth;
    cout << setw(25) << left << "Enter Gender" << " : ";
    cin >> newGender;
    cout << setw(25) << left << "Enter Salary" << " : ";
    cin >> newSalary;

    Receptionist receptionist(newFirstName, newLastName, newAddress, newMobileNo, newYear_of_birth, newGender, newSalary);

    ofstream out_receptionist("Receptionist.txt", ios::app);
    out_receptionist.write((char *)&receptionist, sizeof(receptionist));
    out_receptionist.close();

    system("CLS");
    cout << endl;
    cout << "     Receptionist Information     " << endl << endl;


    receptionist.showInformation();
    cout << endl;
    Box.upperDoubleLayerLine(40);
    cout << char(186)   <<  "STATUS : Receptionist Added Successfully" << char(186) << endl;
    Box.lowerDoubleLayerLine(40);
    cout << endl;

    for(int i = 0; i < 16; i++) cout << "_ ";
    cout << endl;
    cout << endl << "System Generated Password : " << receptionist.getPassword() << endl << endl;



}

void Admin::updateReceptionist()
{
    Table Box;
    int given_id;
    cout << "Enter Receptionist ID to be Updated : ";
    cin >> given_id;
    cout << endl;

    ifstream in_receptionist("Receptionist.txt");
    ofstream out_receptionist("temp.txt", ios::app);
    int is_record_found = 0;
    if(!in_receptionist.is_open())
    {
        in_receptionist.close();
        out_receptionist.close();
        Box.upperDoubleLayerLine(50);
        cout << char(186)   <<  "STATUS : Could Not Update Receptionist Information" << char(186) << endl;
        Box.lowerDoubleLayerLine(50);
        cout << endl;
        out_receptionist.close();
        remove("temp.txt");
    }
    else
    {
        Receptionist receptionist;
        Receptionist point_to_receptionist = receptionist;
        while(in_receptionist.read((char *)&receptionist, sizeof(receptionist)))
        {

            if(given_id == receptionist.getID())
            {
                cout << endl << "Current Information of Receptionist " << receptionist.getLastName() << "   " << endl;
                receptionist.showInformation();
                cout << endl;
                cout << endl;

ll:
                Box.upperLine(30);

                cout << char(179) << "  What do you want to update? " << char(179) << endl;
                Box.lowerLine(30);
                cout << char(179) << setw(30) << left << " 1. Address" << char(179) << endl;
                Box.lowerLine(30);
                cout << char(179) << setw(30) << left << " 2. Mobile No" << char(179) << endl;
                Box.lowerLine(30);
                cout << char(179) << setw(30) << left << " 3. Salary" << char(179) << endl;
                Box.lowerLine(30);

                for(int i = 0; i < 16; i++) cout << "_ ";

                cout << endl << endl;;

                cout << "Proceed to Update? (Y/N)" << endl << "-> ";
                char c;
                cin >> c;
                if(c == 'n' || c == 'N')
                {
                    out_receptionist.close();
                    in_receptionist.close();
                    remove("temp.txt");
                    return;
                }


                cout << setw(28) << " Enter Your Choice"   << " : ";

                int option;
                cin >> option;
                switch(option)
                {

                case 1:
                {
                    cout << setw(28) << " Enter New Address" << " : ";
                    string new_address;
                    getchar();
                    getline(cin, new_address);
                    receptionist.setAddress(new_address);
                    break;
                }
                case 2:
                {
                    cout << setw(28) << " Enter New Mobile Number" << " : ";
                    string new_mobileNo;
                    cin >> new_mobileNo;
                    receptionist.setMobileNo(new_mobileNo);
                    break;
                }
                case 3:
                {

                    cout << setw(28) << " Change Salary" << " : ";
                    int new_salary;
                    cin >> new_salary;
                    receptionist.setSalary(new_salary);
                    break;
                }

                default:
                {
                    system("CLS");
                    cout << endl << "Invalid Input! Select Again" << endl << endl;
                    goto ll;
                    break;
                }

                }

                point_to_receptionist = receptionist;
                is_record_found = 1;
                out_receptionist.write((char *)&point_to_receptionist, sizeof(point_to_receptionist));
            }
            else
            {
                out_receptionist.write((char *)&receptionist, sizeof(receptionist));
            }

        }

        out_receptionist.close();
        in_receptionist.close();

        if(is_record_found == 1)
        {

            if(remove("Receptionist.txt") == 0 && rename("temp.txt", "Receptionist.txt") == 0)
            {
                system("CLS");
                cout << endl;
                point_to_receptionist.showInformation();
                cout << endl;
                Box.upperDoubleLayerLine(41);
                cout << char(186) <<"STATUS : Updated Receptionist Information" << char(186) << endl;
                Box.lowerDoubleLayerLine(41);
                cout << endl;
            }
            else
            {
                Box.upperDoubleLayerLine(50);
                cout << char(186) <<"STATUS : Could Not Update Receptionist Information" << char(186) << endl;
                Box.lowerDoubleLayerLine(50);
            }
        }
        else
        {
            remove("temp.txt");
            cout << "Invalid ID" << endl;
        }
    }
}

void Admin::deleteReceptionist()
{
    Table Box;
    int given_id;
    cout << "Enter ID of Receptionist to be Deleted : ";
    cin >> given_id;
    cout << endl;


    ifstream in_receptionist("Receptionist.txt");
    ofstream out_receptionist("temp.txt", ios::app);
    int is_record_found = 0;
    if(!in_receptionist.is_open())
    {
        Box.upperDoubleLayerLine(50);
        cout << char(186)   <<  "STATUS : Could Not Delete Receptionist Information" << char(186) << endl;
        Box.lowerDoubleLayerLine(50);
        cout << endl;
        out_receptionist.close();
        remove("temp.txt");

    }
    else
    {
        Receptionist receptionist;
        int changed_mind = 0;
        while(in_receptionist.read((char *)&receptionist, sizeof(receptionist)))
        {

            if(given_id == receptionist.getID())
            {
                is_record_found = 1;
                receptionist.showInformation(); cout << endl;

                for(int i = 0; i < 16; i++) cout << "_ ";

                cout << endl << endl;
ll:
                cout << "Proceed To Delete? (Y/N)" << endl << "-> " ;
                char c;
                cin >> c;
                if(c != 'N' && c != 'n' && c != 'Y' && c != 'y')
                {
                    cout << endl;
                    goto ll;
                }
                if(c != 'Y' && c != 'y') // if admin changes his mind then do not delete doctor
                {
                    changed_mind = 1;
                    out_receptionist.write((char *)&receptionist, sizeof(receptionist));
                }
                is_record_found = 1;

            }
            else
            {
                out_receptionist.write((char *)&receptionist, sizeof(receptionist));
            }

        }

        out_receptionist.close();
        in_receptionist.close();

        if(changed_mind)
        {
            remove("temp.txt");
            cout << endl;
            return;
        }





        if(is_record_found == 1)
        {

            if(remove("Receptionist.txt") == 0 && rename("temp.txt", "Receptionist.txt") == 0)
            {
                Box.upperDoubleLayerLine(42);
                cout << char(186)   <<  "STATUS : Successfully Deleted Receptionist" << char(186) << endl;
                Box.lowerDoubleLayerLine(42);
                cout << endl;
            }
            else
            {
                Box.upperDoubleLayerLine(38);
                cout << char(186)   <<  "STATUS : Could Not Delete Receptionist" << char(186) << endl;
                Box.lowerDoubleLayerLine(38);
                cout << endl;
            }
        }
        else
        {
            remove("temp.txt");
            cout << "Invalid ID" << endl << endl;
        }
    }
}





void Admin::showReceptionist()
{
    Table Box;
    ifstream in_receptionist("Receptionist.txt");
    if(!in_receptionist.is_open())
    {
        in_receptionist.close();
        cout << endl;
        Box.upperDoubleLayerLine(48);
        cout << char(186) << "STATUS : Could Not Show Receptionist Information" << char(186) << endl;
        Box.lowerDoubleLayerLine(48);
    }
    else
    {
        Receptionist receptionist;
        int is_file_empty = 0; // flag
        //int count = 0;
        in_receptionist.read((char *)&receptionist, sizeof(receptionist));
        while(!in_receptionist.eof())
        {
            //count++;
            if(is_file_empty == 0)
            {
                cout << endl;
                Box.upperLine(40);
                cout << char(179) << setw(12) << left << "     ID     " << "|" << setw(27) << left << "        Name         " << char(179) << endl;
                Box.lowerLine(40);
                is_file_empty = 1;
            }

            cout << char(179) << setw(12) << left << receptionist.getID() << "| " << setw(26) << left << receptionist.getName() << char(179) << endl;
            Box.lowerLine(40);
            in_receptionist.read((char *)&receptionist, sizeof(receptionist));
        }
       // cout << count << endl << endl;
        in_receptionist.close();
        if(!is_file_empty)
        {
            Box.upperDoubleLayerLine(30);
            cout << char(186) << "STATUS : No Receptionist Found" << char(186) << endl;
            Box.lowerDoubleLayerLine(30);
            return;
        }

        for(int i = 0; i < 16; i++) cout << "_ ";
        cout << endl << endl;
        int detailed_search = 0;
ll:
        cout << "See Full Details of Receptionist? (Y/N)" << endl << "-> ";
        char c;
        cin >> c;
        if(c != 'N' && c != 'n' && c != 'Y' && c != 'y')
        {
            cout << endl;
            goto ll;
        }
        if(c != 'n' && c != 'N') // if c is yes then go for details searching
        {
            detailed_search = 1;
        }
        else
        {
            in_receptionist.close();
            return;
        }
        if(detailed_search)
        {


ll1:
            cout << endl << "Enter ID to See Full Details : " ;
            int id;
            cin >> id;
            int is_receptionist_found = 0; // flag
            ifstream in_receptionist("Receptionist.txt");
            while(in_receptionist.read((char *)&receptionist, sizeof(receptionist)))
            {
                if(id == receptionist.getID())
                {
                    is_receptionist_found = 1;
                    receptionist.showInformation();
                    cout << endl;
                    break;
                }

            }

            if(!is_receptionist_found)
            {
                cout << "Invalid Input, Try Again!" << endl;
                goto ll1;
            }
            for(int i = 0; i < 16; i++) cout << "_ ";
            cout << endl << endl;;
ll2:
            cout << "Search Again? (Y/N)" << endl << "-> ";
            cin >> c;
            if(c != 'N' && c != 'n' && c != 'Y' && c != 'y')
            {
                cout << endl;
                goto ll2;
            }
            if(c != 'n' && c != 'N') // if c is yes then go again for details searching
            {
                cout << endl;
                goto ll1;
            }
            else
            {
                in_receptionist.close();
                return;
            }
        }


    }
}


void Admin::showPatient()
{
    Table Box;
    ifstream inpatient("Patient.txt");
    if(!inpatient.is_open())
    {
        Box.upperDoubleLayerLine(31);
        cout << char(186)   <<  "STATUS : Patient File Not Found" << char(186) << endl;
        Box.lowerDoubleLayerLine(31);
        cout << endl;
    }
    else
    {
        Patient pat;

        while(inpatient.read((char *)&pat, sizeof(pat)))
        {
            pat.showInformation();
            cout << endl;
        }
        inpatient.close();
    }
}

