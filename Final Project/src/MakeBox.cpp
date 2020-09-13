#include "MakeBox.h"
#include <iostream>

using namespace std;

void Table::upperLine(int width)
{
    cout << char(218); // special characters are used for making boxes around the text
    for(int i = 0; i < width; i++)
    {
        cout << char(196); // first line is printed
    }
    cout << char(191) << endl; // line finished, char 191 representing the corner
}

void Table::lowerLine(int width)
{
    cout << char(192);
    for(int i = 0; i < width; i++)
    {
        cout << char(196); // after printing each option add a line below it
    }
    cout << char(217) << endl;
}

void Table::upperDoubleLayerLine(int width)
{
    cout << char(201);
    for(int i = 0; i < width; i++)
    {
        cout << char(205);
    }
    cout << char(187) << endl;
}

void Table::lowerDoubleLayerLine(int width)
{
    cout << char(200);
    for(int i = 0; i < width; i++)
    {
        cout << char(205);
    }
    cout << char(188) << endl;
}
