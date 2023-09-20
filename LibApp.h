// Final Project
// Module: Menu
// Filename: Menu.cpp
// Version 1.0
// Date 02/08/2023
// Author Temitope Oladimeji Samuel Adebayo
// Revision History
// -----------------------------------------------------------
// Date      Reason
// 
// -----------------------------------------------------------
// I have done all the coding by myself and only copied the code 
// that my professor provided to complete my workshops and assignments.
// -----------------------------------------------------------

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H

#include "Lib.h"
#include "Menu.h"
#include "Publication.h"

namespace sdds {
  class LibApp {
    bool m_changed;

    char m_filename[SDDS_MAX_CHAR_SIZE + 1];
    Publication* m_ppa[SDDS_LIBRARY_CAPACITY];
    int m_noOfLoadedPubs;
    int m_lastLibRefNum;

    Menu m_mainMenu;
    Menu m_exitMenu;
    
    Menu m_pubType;

    bool confirm(const char* message); // initialize menu function with message and pass "yes"

    void load();  // display "Loading Data"
    void save(); // display "Saving Data"
    int search(int type); // display "Searching for publication"
    void returnPub(); // call search, display "Returning publication", "Publication returned" and set m_changed to true
    
    void newPublication(); // add new publication with confirmation
    void removePublication(); // remove publication with confirmation
    void checkOutPub(); // check out publication with confirmation

    void setEmpty(); // set m_changed to false
  public:
    LibApp(const char* filename);
    ~LibApp();

    void run();

    Publication* getPub(int libRef);
  };
}
#endif // !SDDS_LIBAPP_H



