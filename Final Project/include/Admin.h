#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>



using namespace std;

class Admin
{

    private:
        string password = "admin";
    public:
        Admin();
        ~Admin();
        int verifyPassword(string password);

        void createDepartment();
        void showDepartment();

        void addDoctor();
        void updateDoctor();
        void deleteDoctor();
        void searchInDepartment();
        void showDoctor();

        void addReceptionist();
        void updateReceptionist();
        void deleteReceptionist();
        void showReceptionist();

        void showPatient();



};

#endif // ADMIN_H
