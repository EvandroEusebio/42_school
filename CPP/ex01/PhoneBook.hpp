#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <iostream>
#include "Contact.hpp"

class PhoneBook{
    public:
        static size_t total_contacts;
        void addContact();
        void searchContact();
        void showContacts();

    private:
        Contact _contacts[8];

};


#endif