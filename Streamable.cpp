// Final Project
// Module: Streamable
// Filename: Streamable.cpp
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

#include <iostream>
#include "Streamable.h"

namespace sdds {
  std::ostream& operator<<(std::ostream& ostr, const Streamable& src) {
    if (src) {
      src.write(ostr);
    }
    return ostr;
  }

  std::istream& operator>>(std::istream& istr, Streamable& src) {
    return src.read(istr);
  }
}
