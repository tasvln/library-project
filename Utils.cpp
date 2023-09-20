/***********************************************************************
// Utils Module
// File	Utils.cpp
// Version 1.0
// Date 20/07/2023
// Author Temitope Oladimeji Samuel Adebayo
// Description
// Project Milestone Utils Module
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// Temitope Adebayo 02/08/2023     Workshop 10
// -----------------------------------------------------------
// I have done all the coding by myself and only copied the code 
// that my professor provided to complete my workshops and assignments.
// -----------------------------------------------------------
/////////////////////////////////////////////////////////////////
***********************************************************************/

#include <iostream>
#include "Utils.h"
#include <string>

using namespace std;

namespace sdds {
  int inputIntRange(int min, int max, const char* errorMessage) {
    int value;
    bool done = false;

    while (!done) {
      cin >> value;
      if (cin.fail()) {
        cin.clear();
        cout << errorMessage;
      }
      else {
        if (value < min || value > max) {
          cout << errorMessage;
          cin.clear();
        }
        else {
          done = true;
        }
      }
      cin.ignore(1000, '\n');
    }
    return value;
  }

}
