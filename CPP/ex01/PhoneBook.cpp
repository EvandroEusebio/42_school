#include "PhoneBook.hpp"
#include <sstream>

size_t PhoneBook::total_contacts = 0;

static size_t ft_length(std::string const str)
{
    size_t i = 0;

    while (str[i])
        i++;
    return i;
}

static std::string format_text(std::string str)
{
    const size_t total_char = 10;
    size_t len_str = str.size();
    size_t space;
    std::string new_str;

    if (len_str < total_char)
    {
        space = total_char - len_str;
        for (size_t i = 0; i < space; i++)
            new_str += " ";
        new_str += str;
    }
    else if (len_str > total_char)
    {
        for (size_t i = 0; i < total_char; i++)
        {
            if (i < 9)
                new_str += str[i];
            else
                new_str += ".";
        }
    }
    else
        new_str += str;
    return new_str;
}

void PhoneBook::addContact()
{
    std::string name;
    std::string surname;
    std::string nickname;
    std::string phone_number;
    std::string dark_secret;

    std::cout << "Insert Name: ";
    std::cin >> name;

    if (name.size() == 0)
    {
        std::cout << "Error Name can't be empty!" << std::endl;
        return;
    }

    std::cout << "Insert Surname: ";
    std::cin >> surname;

    if (surname.size() == 0)
    {
        std::cout << "Error Surname can't be empty!" << std::endl;
        return;
    }

    std::cout << "Insert Nickname: ";
    std::cin >> nickname;

    if (nickname.size() == 0)
    {
        std::cout << "Error Nickname can't be empty!" << std::endl;
        return;
    }

    std::cout << "Insert Phone number: ";
    std::cin >> phone_number;

    if (phone_number.size() == 0)
    {
        std::cout << "Error phone_number can't be empty!" << std::endl;
        return;
    }

    std::cout << "Insert Dark secret: ";
    std::cin >> dark_secret;

    if (dark_secret.size() == 0)
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

void PhoneBook::showContacts()
{
    size_t i = 0;
    std::stringstream convert_to_str;

    if (this->total_contacts == 0)
    {
        std::cout << "No registered contact" << std::endl;
        return;
    }
    std::cout << "=====> YOURS CONTACTS <=====" << std::endl;
    while (i < total_contacts)
    {
        convert_to_str << i;
        std::string index = convert_to_str.str();
        std::cout << format_text(index) << "|";
        std::cout << format_text(this->_contacts[i].getFistName()) << "|";
        std::cout << format_text(this->_contacts[i].getSurName()) << "|";
        std::cout << format_text(this->_contacts[i].getNickName()) << "|";
        std::cout << format_text(this->_contacts[i].getPhoneNumber()) << "|";
        std::cout << format_text(this->_contacts[i].getDarkSecret()) << std::endl;
        i++;
    }
}

void PhoneBook::searchContact()
{
    int index;
    this->showContacts();
    if (this->total_contacts == 0)
        return;
    std::cout << "Insert Index of contact: ";
    std::cin >> index;

    if(index + 1 > this->total_contacts || index < 0)
        std::cout << "Contact Not Found" << std::endl;
    else
    {
        std::cout << this->_contacts[index].getFistName() << std::endl;
        std::cout << this->_contacts[index].getSurName() << std::endl;
        std::cout << this->_contacts[index].getNickName() << std::endl;
        std::cout << this->_contacts[index].getPhoneNumber() << std::endl;
        std::cout << this->_contacts[index].getDarkSecret() << std::endl;
    }
}