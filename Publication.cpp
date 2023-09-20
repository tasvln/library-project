// Final Project
// Module: Streamable
// Filename: Streamable.cpp
// Version 1.0
// Date 20/07/2023
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
#include "Publication.h"

using namespace std;

namespace sdds {
  void Publication::setEmpty() {
    m_title = nullptr;
    m_shelfId[0] = '\0';
    m_membership = 0;
    m_libRef = -1;
    resetDate();
  }

  Publication::Publication() {
    setEmpty();
  }

  Publication::Publication(const Publication& src) {
    if (m_title) {
      delete[] m_title;
      m_title = nullptr;
    }
    setEmpty();

    if (src.m_title) {
      m_title = new char[strlen(src.m_title) + 1];
      strcpy(m_title, src.m_title);
      setRef(src.m_libRef);
      strcpy(m_shelfId, src.m_shelfId);
      set(src.m_membership);
      m_date = src.m_date;
    }
  }

  Publication& Publication::operator=(const Publication& src) {
    if (this != &src) {
      if (m_title) {
        delete[] m_title;
        m_title = nullptr;
      }
      setEmpty();

      if (src.m_title) {
        m_title = new char[strlen(src.m_title) + 1];
        strcpy(m_title, src.m_title);
      } else {
        m_title = nullptr;
      }

      strcpy(m_shelfId, src.m_shelfId);
      set(src.m_membership);
      setRef(src.m_libRef);
      m_date = src.m_date;
    }

    return *this;
  }

  Publication::~Publication() {
    delete[] m_title;
  }

  void Publication::set(int member_id) {
    m_membership = member_id;
  }

  void Publication::setRef(int value) {
    m_libRef = value;
  }

  void Publication::resetDate() {
    m_date = Date();
  }

  char Publication::type()const {
    return 'P';
  }

  bool Publication::onLoan()const {
    return m_membership != 0;
  }

  Date Publication::checkoutDate()const {
    return m_date;
  }

  bool Publication::operator==(const char* title)const {
    return strstr(m_title, title) != nullptr;
  }

  Publication::operator const char* ()const {
    return m_title;
  }

  int Publication::getRef()const {
    return m_libRef;
  }

  bool Publication::conIO(std::ios& io)const {
    return &io == &std::cin || &io == &std::cout;
  }

  std::ostream& Publication::write(std::ostream& ostr) const {
    char tempTitle[SDDS_TITLE_WIDTH + 1] = { 0 };
    strncpy(tempTitle, m_title, SDDS_TITLE_WIDTH);

    if (conIO(ostr)) {
      ostr << "| " << m_shelfId << " | ";
      ostr.width(SDDS_TITLE_WIDTH);
      ostr.setf(ios::left);
      ostr.fill('.');
      ostr << tempTitle;
      ostr.unsetf(ios::left);
      ostr << " | ";
      if (m_membership != 0) {
        ostr << m_membership;
      }
      else {
        ostr << " N/A ";
      }
      ostr << " | " << m_date << " |";
    } else {
      // P	2001	P001	The Toronto Star	34037	2023/11/17
      ostr << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
    }

    return ostr;
  };

  std::istream& Publication::read(std::istream& istr) {
    // clear all the attributes
    if (m_title != nullptr) {
      delete[] m_title;
    }
    setEmpty();

    // local variables
    char tempTitle[SDDS_MAX_CHAR_SIZE + 1] = { 0 };
    char tempShelfId[SDDS_SHELF_ID_LEN + 1] = { 0 };
    int tempMembership = 0;
    int tempLibRef = -1;
    Date tempDate;

    if (conIO(istr)) {
      std::cout << "Shelf No: ";
      istr.getline(tempShelfId, SDDS_SHELF_ID_LEN + 1);

      if (strlen(tempShelfId) != SDDS_SHELF_ID_LEN) {
        istr.setstate(std::ios::failbit);
      }

      std::cout << "Title: ";
      istr.getline(tempTitle, SDDS_MAX_CHAR_SIZE + 1);

      std::cout << "Date: ";
      istr >> tempDate;
    } else {
      istr >> tempLibRef;
      istr.ignore();
      istr.getline(tempShelfId, SDDS_SHELF_ID_LEN + 1, '\t');
      istr.getline(tempTitle, SDDS_MAX_CHAR_SIZE + 1, '\t');
      istr >> tempMembership;
      istr.ignore();
      istr >> tempDate;
    }

    if (!tempDate) {
      istr.setstate(ios::failbit);
    }
    
    if (istr) {
      m_title = new char[strlen(tempTitle) + 1];
      strcpy(m_title, tempTitle);
      strcpy(m_shelfId, tempShelfId);
      set(tempMembership);
      m_date = tempDate;
      setRef(tempLibRef);
    }

    return istr;
  }

  Publication::operator bool() const {
    return m_title != nullptr && m_shelfId[0] != '\0';
  }
}
