#include "Contact.hpp"

void Contact::createContact(std::string first_name, std::string surname, std::string nickname, int phone_number, 
            std::string dark_secret)
{
    this->_first_name = first_name;
    this->_surname = surname;
    this->_nickname = nickname;
    this->_phone_number = phone_number;
    this->_dark_secret = dark_secret;
}