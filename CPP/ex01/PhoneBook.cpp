#include "PhoneBook.hpp"

static size_t ft_length(std::string const str)
{
    size_t i = 0;

    while (str[i])
        i++;
    return i;
}

void PhoneBook::addContact()
{
    std::string name;
    std::string surname;
    std::string nickname;
    int phone_number;
    std::string dark_secret;
    
    std::cout << "Insert Name: " << std::endl;
    std::cin >> name;

    if(ft_length(name) == 0)
    {
        std::cout << "Error Name can't be empty!" << std::endl;
        return;
    }

    std::cout << "Insert Surname: " << std::endl;
    std::cin >> surname;

    if(ft_length(surname) == 0)
    {
        std::cout << "Error Surname can't be empty!" << std::endl;
        return;
    }

    std::cout << "Insert Nickname: " << std::endl;
    std::cin >> nickname;

    if(ft_length(nickname) == 0)
    {
        std::cout << "Error Nickname can't be empty!" << std::endl;
        return;
    }

    std::cout << "Insert Phone number: " << std::endl;
    std::cin >> phone_number;

    if(phone_number <= 0)
    {
        std::cout << "Error phone_number can't be empty!" << std::endl;
        return;
    }

    std::cout << "Insert Dark secret: " << std::endl;
    std::cin >> dark_secret;

    if(ft_length(dark_secret) == 0)
    {
        std::cout << "Error dark_secret can't be empty!" << std::endl;
        return;
    }

    Contact new_contact;
    new_contact.createContact(name, surname, 
        nickname, phone_number, dark_secret);
    
    this->_contacts[this->total_contacts] = new_contact;
    this->total_contacts++;

    std::cout << "CONTACT ADD SUCESSIFULY!" << std::endl;
}