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

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>

#include "Publication.h"

namespace sdds {
  class Book: public Publication {
    char* m_author;
    void setEmpty();
  public:
    // default constructor
    Book();

    // rule of three (copy constructor, copy assignment operator, destructor)
    Book(const Book&);
    Book& operator=(const Book&);
    ~Book();

    // member functions
    virtual char type() const;
    std::ostream& write(std::ostream& ostr) const;
    std::istream& read(std::istream& istr);
    virtual void set(int member_id);
    operator bool() const;
  };
}

#endif