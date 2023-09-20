// Final Project
// Module: Streamable
// Filename: Streamable.h
// Version 1.0
// Date 25/07/2023
// Author Temitope Oladimeji Samuel Adebayo
// Revision History
// -----------------------------------------------------------
// Date      Reason
// 
// -----------------------------------------------------------
// I have done all the coding by myself and only copied the code 
// that my professor provided to complete my workshops and assignments.
// -----------------------------------------------------------

#include <iostream>
#include <cstring>
#include "Book.h"

using namespace std;

namespace sdds {
  void Book::setEmpty() {
    m_author = nullptr;
  }

  Book::Book(): Publication() {
    setEmpty();
  }

  Book::Book(const Book& src): Publication(src) {
    if (m_author != nullptr) {
      delete[] m_author;
    }
    setEmpty();
    if (src.m_author != nullptr) {
      m_author = new char[strlen(src.m_author) + 1];
      strcpy(m_author, src.m_author);
    }
  }

  Book& Book::operator=(const Book& src) {
    if (this != &src) {
      Publication::operator=(src);
      delete[] m_author;
      setEmpty();
      if (src.m_author != nullptr) {
        m_author = new char[strlen(src.m_author) + 1];
        strcpy(m_author, src.m_author);
      }
    }
    return *this;
  }

  Book::~Book() {
    delete[] m_author;
  }

  char Book::type() const {
    return 'B';
  }

  std::ostream& Book::write(std::ostream& ostr) const {
    char tempAuthor[SDDS_AUTHOR_WIDTH + 1] = { 0 };
    Publication::write(ostr);

    if (conIO(ostr)) {
      ostr << " ";
      strncpy(tempAuthor, m_author, SDDS_AUTHOR_WIDTH);
      ostr.width(SDDS_AUTHOR_WIDTH);
      ostr.setf(ios::left);
      ostr << tempAuthor;
      ostr.unsetf(ios::left);
      ostr << " |";
    } else {
      ostr << '\t' << m_author;
    }

    return ostr;
  }

  std::istream& Book::read(std::istream& istr) {
    char tempAuthor[SDDS_MAX_CHAR_SIZE + 1] = { 0 };
    Publication::read(istr);

    if (m_author != nullptr) {
      delete[] m_author;
      setEmpty();
    }

    if (conIO(istr)) {
      istr.ignore();
      cout << "Author: ";
      istr.get(tempAuthor, SDDS_MAX_CHAR_SIZE);
    } else {
      istr.ignore(1000, '\t');
      istr.get(tempAuthor, SDDS_MAX_CHAR_SIZE);
    }

    if (istr) {
      m_author = new char[strlen(tempAuthor) + 1];
      strcpy(m_author, tempAuthor);
    }

    return istr;
  }

  void Book::set(int member_id) {
    Publication::set(member_id);
    Publication::resetDate();
  }

  Book::operator bool() const {
    return m_author != nullptr && Publication::operator bool();
  }
}
