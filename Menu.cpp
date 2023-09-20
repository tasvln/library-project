// Final Project
// Module: Menu
// Filename: Menu.cpp
// Version 1.0
// Date 06/07/2023
// Author Temitope Oladimeji Samuel Adebayo
// Revision History
// -----------------------------------------------------------
// Date       Reason
// 02/08/2023 Workshop 10
// -----------------------------------------------------------
// I have done all the coding by myself and only copied the code 
// that my professor provided to complete my workshops and assignments.
// -----------------------------------------------------------

#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace sdds {
  // MenuItem class member functions
  MenuItem::MenuItem() {
    m_content = nullptr;
  }

  MenuItem::MenuItem(const char* name) {
    if (name) {
      m_content = new char[strlen(name) + 1];
      strcpy(m_content, name);
    }
    else {
      m_content = nullptr;
    }
  }

  MenuItem::~MenuItem() {
    delete[] m_content;
    m_content = nullptr;
  }

  MenuItem::operator bool() const {
    return m_content != nullptr;
  }

  MenuItem::operator const char* () const {
    return m_content;
  }

  ostream& MenuItem::display(ostream& ostr) const {
    if (*this) {
      ostr << m_content;
    }
    return ostr;
  }

  // Menu class member functions

  void Menu::setEmpty() {
    m_title.m_content = nullptr;
    
    for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
      m_menuItems[i] = nullptr;
    }

    m_menuItemsAdded = 0;
  }

  Menu::Menu() {
    setEmpty();
  }

  Menu::Menu(const char* title) {
    setEmpty();
    if (title) {
      m_title.m_content = new char[strlen(title) + 1];
      strcpy(m_title.m_content, title);
    }
  }

  Menu::~Menu() {
    delete[] m_title.m_content;
    m_title.m_content = nullptr;

    for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
      delete m_menuItems[i];
    }
  }

  ostream& Menu::displayTitle(ostream& ostr) const {
    if (*this) {
      ostr << m_title.m_content;
    }
    return ostr;
  }

  ostream& Menu::displayMenu(ostream& ostr) const {
    if (*this) {
      displayTitle(ostr);
      ostr << endl;
    }

    if (m_menuItemsAdded > 0) {
      for (unsigned int i = 0; i < m_menuItemsAdded; i++) {
        ostr.width(2);
        ostr.setf(ios::right);
        ostr << i + 1 << "- " << m_menuItems[i]->m_content << endl;
      }

      ostr << " 0- Exit" << endl;
      ostr << "> ";
    }

    return ostr;
  }

  int Menu::run() const {
    int input;
    displayMenu();
    input = inputIntRange(0, m_menuItemsAdded, "Invalid Selection, try again: ");
    return input;
  }

  int Menu::operator~() const {
    return run();
  }

  Menu& Menu::operator<<(const char* content) {
    if (content) {
      if (m_menuItemsAdded < MAX_MENU_ITEMS) {
        m_menuItems[m_menuItemsAdded++] = new MenuItem(content);
      }
    }
    return *this;
  }

  Menu::operator int() const {
    return m_menuItemsAdded;
  }

  Menu::operator unsigned int() const {
    return m_menuItemsAdded;
  }

  Menu::operator bool() const {
    return m_title != nullptr;
  }

  const char* Menu::operator[](int index) const {
    if (index >= 0 && (unsigned)index < m_menuItemsAdded) {
      return m_menuItems[index %= m_menuItemsAdded]->m_content;
    }
    else {
      return nullptr;
    }
  }

  std::ostream& operator<<(ostream& ostr, const Menu& menu) {
    return menu.displayTitle(ostr);
  }
}
