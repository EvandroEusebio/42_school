#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>

class Contact{
    public:
        void createContact(std::string first_name, std::string surname, std::string nickname, int phone_number, 
            std::string dark_secret);
        
    private:
        std::string _first_name;
        std::string _surname;
        std::string _nickname;
        int _phone_number;
        std::string _dark_secret;

};

#endif