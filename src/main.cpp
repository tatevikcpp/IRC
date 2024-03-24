#include "IRC_Server.hpp"

bool validArgv(const std::string& port, const std::string& password)
{
    if (password.empty() || password.length() < 8)
    {
        std::cout << "Error: password must contain at least 8 symbols!" << std::endl;
        return false;
    }
    
    if (port.empty())
    {
        std::cout << "Error: empty port!" << std::endl;
        return false;
    }

    for (size_t i = 0; i < port.size(); ++i)
    {
        if (!std::isdigit(port[i]))
        {
            std::cout << "Error: port must contain only digits!" << std::endl;
            return false;
        }
    }

    int portNum = std::atoi(port.c_str());
    if (portNum <= 0 || portNum > 65535)
    {
        std::cout << "Error: port must be in range [1:65535]!" << std::endl;
        return false;
    }
    
    return true;
}


int main(int c, char **v)
{
    if (c != 3)
    {
        std::cout<< "Too many arguments" << std::endl;
        return (1);
    }

    if (!validArgv(v[1], v[2]))
    {
        return (1);
    }

    try
    {
        IRC_Server s(v[1], v[2]);
        s.start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}