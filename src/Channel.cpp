#include "Channel.hpp"

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

void Channel::sending(Client* C, const std::string& msg/* , const std::string& cmd */)
{
    std::map<int, Client *>::const_iterator it = this->_clients.cbegin(); // TODO nayel !!

    while (it != this->_clients.cend())
    {
        if (C->_fd != it->first)
        {
            if (send(it->first, msg.c_str(), msg.size(), 0) == -1)
            {

            }
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
