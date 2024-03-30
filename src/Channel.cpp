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
        this->joinClient(*client);
    this->_limit = 0;
//     this->_name = name;
//     this->_pass = pass;
}

Channel::~Channel()
{

}


// std::vector<std::string>    Channel::get_nicknames()
// {
//     std::vector<std::string> nicknames;

//     client_iterator it_b = _clients.begin();
//     client_iterator it_e = _clients.end();

//     while (it_b != it_e)
//     {
//         Client* client = *it_b;

//         std::string nick = (client == _admin ? "@" : "") + client->get_nickname();
//         nicknames.push_back(nick);

//         it_b++;
//     }

//     return nicknames;
// }

// void Channel::nameReply(Client &client) TODO "@" -i hamar 
// {
//     // sending TOPIC to new user    
//     // std::string topic = this->getTopic();
//     // if (topic.empty())            
//     //     client.sending(RPL_NOTOPIC(_channelName + static_cast<char>(1)));
//     // else            
//     //     client.sending(RPL_TOPIC(_channelName + static_cast<char>(1), topic));
    
//     // sending channal's users list to new user
//     std::string nickList;
//     std::map<int, Client *>::iterator it = this->_clients.begin();
//     for (; it != _clients.end(); ++it)
//     {
//         // std::string prefix = (_clients[i] == _admin) ? "@" : "+";
//         // nickList += prefix + _clients[i]->getNICK() + "  ";

//         std::string prefix = (it->second->_channels 
//     }
//     // client.sending(RPL_NAMREPLY(client.getNICK(), _channelName + static_cast<char>(1), nickList));
//     // client.sending(RPL_ENDOFNAMES(client.getNICK(), _channelName + static_cast<char>(1)));
// }


void Channel::joinClient(Client &client)
{
    this->_clients[client._fd] = &client;
    client.joinToChannel(*this);
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

void Channel::setChannelLimit(int limit)
{
    this->_limit = limit;
}

int Channel::getChannelLimit(void)
{
    return _limit;
}

bool Channel::emptyChannel(void)
{
    return (this->_clients.empty());
}

bool Channel::channelIsFull(void)
{
    if (_limit == 0)
        return false;

    return _limit <= static_cast<size_t>(_clients.size());
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

bool Channel::isInviteOnly(void)
{
    return _inviteOnly;
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