#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <iostream>
#include "Contact.hpp"

class PhoneBook{
    public:
        int total_contacts = 0;
        void addContact();
        //void searchContact();

    private:
        Contact _contacts[8];

};


#endif