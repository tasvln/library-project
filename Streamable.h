// Final Project
// Module: Streamable
// Filename: Streamable.h
// Version 1.0
// Date 20/07/2023
// Author Temitope Oladimeji Samuel Adebayo
// Revision History
// -----------------------------------------------------------
// Date      Reason
// 
// -----------------------------------------------------------
// I have done all the coding by myself and only copied the code 
// that my professor provided to complete my workshops and assignments.
// -----------------------------------------------------------

#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H

#include <iostream>

namespace sdds {
  class Streamable {
  public:
    virtual std::ostream& write(std::ostream&) const = 0;
    virtual std::istream& read(std::istream&) = 0;

    // pure virtual function of console IO
    virtual bool conIO(std::ios& io) const = 0;

    // pure virtual function of bool conversion overload
    virtual operator bool() const = 0;

    // pure virtual destructor
    virtual ~Streamable() {};
  };

  std::ostream& operator<<(std::ostream& ostr, const Streamable&);
  std::istream& operator>>(std::istream& istr, Streamable&);
}

#endif
