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

#include <iostream>
#include <fstream>
#include <cstring>
#include "LibApp.h"
#include "Book.h"
#include "PublicationSelector.h"
#include "Utils.h"

using namespace std;

namespace sdds {
  // Private methods
  void LibApp::setEmpty() {
    m_changed = false;
    m_filename[0] = '\0';
    m_ppa[0] = nullptr;
    m_noOfLoadedPubs = 0;
    m_lastLibRefNum = 0;
  }

  bool LibApp::confirm(const char* message) {
    bool confirmed = false;
    if (message) {
      Menu menu(message);
      menu << "Yes";

      if (menu.run() == 1) {
        confirmed = true;
      }
    }

    return confirmed;
  }

  void LibApp::load() {
    char type;
    int i;
    m_noOfLoadedPubs = 0;
    cout << "Loading Data" << endl;

    // open the file
    ifstream file(m_filename);

    // read all the publications from the file
    for (i = 0; file && i < SDDS_LIBRARY_CAPACITY; i++) {
      file >> type;
      file.ignore();

      if (file) {
        if (type == 'B') {
          m_ppa[i] = new Book;
        } else if (type == 'P') {
          m_ppa[i] = new Publication;
        }

        if (m_ppa[i]) {
          file >> *m_ppa[i];
          m_noOfLoadedPubs++;

          m_lastLibRefNum = m_ppa[i]->getRef();
        }
      }
    }
  }

  void LibApp::save() {
    int i;
    cout << "Saving Data" << endl;

    ofstream file(m_filename);

    for (i = 0; i < m_noOfLoadedPubs; i++) {
      if (m_ppa[i]->getRef() != 0) {
        file << *m_ppa[i] << endl;
      }
    }

    file.close();
  }

int LibApp::search(int type) {
    char title[SDDS_MAX_CHAR_SIZE + 1]{};
    char charType;
    int selection, i, libRef = 0;

    PublicationSelector pubSelection("Select one of the following found matches:", 15);

    selection = m_pubType.run();

    if (selection == 1) {
      charType = 'B';
    } else if (selection == 2) {
      charType = 'P';
    } 

    cout << "Publication Title: ";
    cin.getline(title, SDDS_MAX_CHAR_SIZE + 1);

    if (type == 1) {
      for (i = 0; i < m_noOfLoadedPubs; i++) {
        if (m_ppa[i]->operator==(title) && charType == m_ppa[i]->type() && m_ppa[i]->getRef() != 0) {
          pubSelection << m_ppa[i];
        }
      }
    } else if (type == 2){
      for (i = 0; i < m_noOfLoadedPubs; i++) {
        if (m_ppa[i]->operator==(title) && charType == m_ppa[i]->type() && m_ppa[i]->getRef() != 0 && m_ppa[i]->onLoan()) {
          pubSelection << m_ppa[i];
        }
      }
    } else if (type == 3){
      for (i = 0; i < m_noOfLoadedPubs; i++) {
        if (m_ppa[i]->operator==(title) && charType == m_ppa[i]->type() && m_ppa[i]->getRef() != 0 && !m_ppa[i]->onLoan()) {
          pubSelection << m_ppa[i];
        }
      }
    }

    if (pubSelection) {
      pubSelection.sort();
      libRef = pubSelection.run();

      if (libRef != 0) {
        cout << *getPub(libRef) << endl;
      } else {
        cout << "Aborted!" << endl;
      }
    } else {
      cout << "No matches found!" << endl;
    }

    return libRef;
  }

  void LibApp::returnPub() {
    int ref;
    int days, lateDays;
    double fee;
    bool confirmed = false;

    cout << "Return publication to the library" << endl;
    ref = search(2);

    if (ref != 0) {
      confirmed = confirm("Return Publication?");
      if (confirmed) {
        days = Date() - getPub(ref)->checkoutDate();

        if (days > SDDS_MAX_LOAN_DAYS) {
          fee = (days - SDDS_MAX_LOAN_DAYS) * SDDS_PENALTY_PER_DAY;
          lateDays = days - SDDS_MAX_LOAN_DAYS;
          cout << "Please pay $";
          cout.setf(ios::fixed);
          cout.precision(2); 
          cout << fee;
          cout.unsetf(ios::fixed);
          cout << " penalty for being " << lateDays << " days late!" << endl;
        }

        getPub(ref)->set(0);
        m_changed = true;
      }

      cout << "Publication returned" << endl;
    }
  }

  // the address of a publication
  Publication* LibApp::getPub(int libRef) {
    Publication* pub{ nullptr };

    for (int i = 0; i < m_noOfLoadedPubs; i++) {
      if (m_ppa[i]->getRef() == libRef) {
        pub = m_ppa[i];
      }
    }

    return pub;
  }

  // Methods with confirmation
  void LibApp::newPublication() {
    int pubType;
    bool flag = false;

    if (m_noOfLoadedPubs == SDDS_LIBRARY_CAPACITY) {
      flag = true;
      cout << "Library is at its maximum capacity!" << endl;
    }

    if (!flag) {
      cout << "Adding new publication to the library" << endl;
      pubType = m_pubType.run();

      Publication *pub{ nullptr };

      if (pubType == 0) {
        cout << "Aborted!" << endl;
        flag = true;
      } else if (pubType == 1) {
        pub = new Book;
        cin >> *pub;
      } else if (pubType == 2) {
        pub = new Publication;
        cin >> *pub;
      }

      if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Aborted!" << endl;
      } else {
        if (!flag && confirm("Add this publication to the library?")) {
          if (*pub) {
            m_lastLibRefNum++;
            pub->setRef(m_lastLibRefNum);

            m_ppa[m_noOfLoadedPubs++] = pub;

            m_changed = true;
            cout << "Publication added" << endl;
          } else {
            cout << "Failed to add publication!" << endl;
            delete pub;
          }
        }
      }
    }
  }

  void LibApp::removePublication() {
    int ref;
    bool confirmed = false;
    cout << "Removing publication from the library" << endl;
    ref = search(1);
    if (ref != 0) {
      confirmed = confirm("Remove this publication from the library?");
      if (confirmed) {
        getPub(ref)->setRef(0);
        
        m_changed = true;
        cout << "Publication removed" << endl;
      }
    } 
  }

  void LibApp::checkOutPub() {
    int ref, input;
    bool confirmed = false;
    cout << "Checkout publication from the library" << endl;
    ref = search(3);
    
    if (ref != 0) {
      confirmed = confirm("Check out publication?");
      if (confirmed) {
        cout << "Enter Membership number: ";
        input = inputIntRange(10000, 99999, "Invalid membership number, try again: ");
        
        getPub(ref)->set(input);

        m_changed = true;
        cout << "Publication checked out" << endl;
      }
    }
  }

  // Contructor
  LibApp::LibApp(const char* filename) : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_pubType("Choose the type of publication:") {
    setEmpty();

    if (filename) {
      strcpy(m_filename, filename);
    }

    m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
    m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
    m_pubType << "Book" << "Publication";

    load();
  }

  // Destructor
  LibApp::~LibApp() {
    for (int i = 0; i < m_noOfLoadedPubs; i++) {
      delete m_ppa[i];
      m_ppa[i] = nullptr;
    }
  }

  // run method
  void LibApp::run() {
    int selection, exitSelection;
    bool confirmed = false;
    bool flag = false;

    do {
      selection = m_mainMenu.run();

      switch (selection) {
      case 1:
        newPublication();
        cout << endl;
        break;
      case 2:
        removePublication();
        cout << endl;
        break;
      case 3:
        checkOutPub();
        cout << endl;
        break;
      case 4:
        returnPub();
        cout << endl;
        break;
      case 0:
        if (m_changed) {
          exitSelection = m_exitMenu.run();

          if (exitSelection == 2) {
            cout << endl;
            selection = 1;
          } else if (exitSelection == 1) {
            save();
            flag = true;
            cout << endl;
          } else if (exitSelection == 0) {
            confirmed = confirm("This will discard all the changes are you sure?");
            if (confirmed) {
              cout << endl;
              m_changed = false;
              flag = true;
            }
          }
        } else {
          cout << endl;
          flag = true;
        }
      }
    } while (!flag);

    cout << "-------------------------------------------" << endl;
    cout << "Thanks for using Seneca Library Application" << endl;
  }
}
