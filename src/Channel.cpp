#include "Channel.hpp"

void Channel::print() const {
    std::map<int, Client *>::const_iterator it = _clients.cbegin();
    std::cout << "-----------------------------------------------------\n";
    std::cout << _name << std::endl; 

    while (it != _clients.end())
    {
        std::cout << it->second->getNICK() << std::endl;
        it++;
    }

    std::cout << "\n-----------------------------------------------------\n";
};

Channel::Channel(const std::string& name, const std::string& pass, Client *client) : _name(name), _pass(pass)
{
    if (client)
        this->joinClient(client);
    this->_limit = 0;
//     this->_name = name;
//     this->_pass = pass;
}

Channel::~Channel()
{

}

void Channel::joinClient(Client *client)
{
    this->_clients[client->_fd] = client;
}

void Channel::deleteClient(Client &client)
{
    this->_clients.erase(client._fd);
}

void Channel::sending(Client* C, const std::string& msg/* , const std::string& cmd */) //TODO
{
    std::map<int, Client *>::const_iterator it = this->_clients.cbegin(); // TODO nayel !!

    while (it != this->_clients.cend())
    {
        if (C->_fd != it->first)
        {
            if (send(it->first, msg.c_str(), msg.size(), 0) < 0)
                throw std::runtime_error("Error while sending a message to a client!");
        }
        it++;
    }
}

bool Channel::emptyChannel(void)
{
    return (this->_clients.empty());
}


size_t Channel::get_limit() const
{
    return (this->_limit);
}

size_t Channel::get_size() const 
{ 
    return this->_clients.size();
}

std::string Channel::get_pass() const
{
    return (this->_pass);
}


std::string Channel::getName(void)
{
    return (this->_name);
}


void Channel::broadcast(const std::string& message)
{
    std::map<int, Client *>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        it->second->reply(message);
    }
}

void Channel::broadcast(const std::string& message, Client* exclude)
{
    std::map<int, Client *>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        if (it->second == exclude)
        {
            ++it;
            continue;
        }
        it->second->reply(message);
    }
}