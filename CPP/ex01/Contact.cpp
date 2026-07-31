#include "Contact.hpp"

void Contact::createContact(std::string first_name, std::string surname, std::string nickname, std::string phone_number, 
            std::string dark_secret)
{
    this->_first_name = first_name;
    this->_surname = surname;
    this->_nickname = nickname;
    this->_phone_number = phone_number;
    this->_dark_secret = dark_secret;
}

std::string Contact::getFistName()
{
    return this->_first_name;
}

std::string Contact::getSurName()
{
    return this->_surname;
}

std::string Contact::getNickName()
{
    return this->_nickname;
}

std::string Contact::getPhoneNumber()
{
    return this->_phone_number;
}

std::string Contact::getDarkSecret()
{
    return this->_dark_secret;
}