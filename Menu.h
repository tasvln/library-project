// Final Project
// Module: Menu
// Filename: Menu.cpp
// Version 1.0
// Date 06/07/2023
// Author Temitope Oladimeji Samuel Adebayo
// Revision History
// -----------------------------------------------------------
// Date      Reason
// 
// -----------------------------------------------------------
// I have done all the coding by myself and only copied the code 
// that my professor provided to complete my workshops and assignments.
// -----------------------------------------------------------
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__

#include <iostream>

namespace sdds {
  const unsigned int MAX_MENU_ITEMS = 20;

  class Menu; // Forward declaration

  class MenuItem {
    char* m_content; // dynamically allocated Cstring
    friend class Menu; // make Menu a friend

    MenuItem(); // default constructor
    MenuItem(const char* name); // constructor

    MenuItem(const MenuItem& src) = delete; // copy constructor (deleted)
    MenuItem& operator=(const MenuItem& src) = delete; // copy assignment operator (deleted)

    ~MenuItem(); // destructor

    operator bool() const; // bool type conversion operator
    operator const char* () const; // const char* type conversion operator

    std::ostream& display(std::ostream& ostr = std::cout) const;
  };

  class Menu {
    MenuItem m_title; // dynamically allocated MenuItem
    MenuItem* m_menuItems[MAX_MENU_ITEMS]; // array of pointers to MenuItem
    unsigned int m_menuItemsAdded; // number of MenuItems added to the Menu
    void setEmpty(); // set the Menu to a safe empty state
    
    Menu(const Menu& src) = delete; // copy constructor (deleted)
    Menu& operator=(const Menu& src) = delete; // copy assignment operator (deleted)
  public:
    Menu(); // default constructor
    Menu(const char* title); // constructor
    ~Menu(); // destructor

    std::ostream& displayTitle(std::ostream& ostr = std::cout) const;
    std::ostream& displayMenu(std::ostream& ostr = std::cout) const;

    int run() const; // run the menu and return the result
    int operator~() const; // run the menu and return the result

    Menu& operator<<(const char* content); // add a MenuItem to the menu

    operator int() const; // int type conversion operator
    operator unsigned int() const; // unsigned int type conversion operator
    operator bool() const; // bool type conversion operator

    const char* operator[](int index) const; // indexing operator
  };
  
  std::ostream& operator<<(std::ostream& ostr, const Menu& menu);
}

#endif
