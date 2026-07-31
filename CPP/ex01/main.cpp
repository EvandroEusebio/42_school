#include <iostream>
#include "PhoneBook.hpp"

int main()
{
    int option;
    int loop = 0;
    std::cout << "=====> WELCOME TO PHONE_BOOK APP <=====" << std::endl;
    PhoneBook myPhoneBook;
    while (loop == 0)
    {
        std::cout << "Choose options" << std::endl;
        std::cin >> option;
        std::cout << "0 -> ADD\n1 -> SEARCH\n2-> EXIT" << std::endl;

        switch (option)
        {
        case 0:
            myPhoneBook.addContact();
            break;
        case 1:
            //myPhoneBook.searchContact();
            break;
        case 2:
            loop = 1;
            break;
        default:
            break;
        }
    }
    return 0;
}