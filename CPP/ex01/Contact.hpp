#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>

class Contact{
    public:
        void createContact(std::string first_name, std::string surname, std::string nickname, std::string phone_number, 
            std::string dark_secret);
        std::string getFistName();
        std::string getSurName();
        std::string getNickName();
        std::string getPhoneNumber();
        std::string getDarkSecret();
        
    private:
        std::string _first_name;
        std::string _surname;
        std::string _nickname;
        std::string _phone_number;
        std::string _dark_secret;
};

#endif