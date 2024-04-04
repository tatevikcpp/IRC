#include "Channel.hpp"
#include <algorithm>

void Channel::print() const {
    std::map<int, Client *>::const_iterator it = _clients.cbegin();
    std::cout << "-----------------------------------------------------\n";
    std::cout << _name << std::endl; 
    std::cout << "size = " << this->_clients.size() << std::endl;
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

void Channel::nameReply(Client &client) //TODO "@" -i hamar
{
    std::cout << "Channel::nameReply" << std::endl;
    // sending TOPIC to new user    
    // std::string topic = this->getTopic();
    // if (topic.empty())            
    //     client.sending(RPL_NOTOPIC(_channelName + static_cast<char>(1)));
    // else            
    //     client.sending(RPL_TOPIC(_channelName + static_cast<char>(1), topic));
    // sending channal's users list to new user
    std::string nickList;
    std::map<int, Client *>::iterator it = this->_clients.find(client.getFd());
    if (it != _clients.end())
    {
        // std::string prefix = (_clients[i] == _admin) ? "@" : "+";
        // nickList += prefix + _clients[i]->getNICK() + "  ";

        std::string prefix = client.isAdmin(*this) == true ? "@" : "+";
        std::cout << "prefix " << prefix << std::endl;
        nickList += prefix + client.getNICK() + "  ";
    }
    client.sendMsg(RPL_NAMREPLY(client.getNICK(), _name + static_cast<char>(1), nickList));
    client.sendMsg(RPL_ENDOFNAMES(client.getNICK(), _name + static_cast<char>(1)));
}


void Channel::joinClient(Client &client)
{
    if (this->_clients.find(client._fd) != this->_clients.end())
    {
        return ;
    }
    if (this->_clients.empty())
    {
        this->_admins.insert(&client);

    }
    this->_clients[client._fd] = &client;
    this->_listClient.push_back(&client);
    client.joinToChannel(*this);
}

void Channel::deleteClient(Client &client)
{
    this->_clients.erase(client._fd);
    std::list<Client *>::iterator it = std::find(this->_listClient.begin(), this->_listClient.end(), &client);
    if (it !=  this->_listClient.end())
    {
        this->_listClient.erase(it);
    }
    if (this->_admins.size() == 1 &&  this->_admins.find(&client) != this->_admins.end())
    {
        this->_admins.erase(&client);
        this->_admins.insert(this->_listClient.front());
    }

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

std::string Channel::getName(void) const
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



bool Channel::emptyClients(void)
{
    return _clients.empty();
}

// void Channel::removeClient(Client &client) // TODO offff
// {
//     std::map<int, Client *>::iterator it = this->_clients.find(client.getFd());
//     if (it == this->_clients.end())
//         return ;
//     std::map<std::string, std::pair<Channel*, TypeClient> >::iterator it_c = client._channels.find(this->getName());
//     if (it_c != client._channels.end())
//     {
//         if (this->_clients.size() == 1)
//         {
//             this->_clients.erase(client.getFd());
//             //TODO jnjel map -y???
//         }
//         if (it_c->second.second == Admin)
//         {
//             this->_clients.erase(client.getFd());
//             this->_clients.begin()->second._channels->second.second = Admin;
//         }
//     }

//     // this->_clients.erase(client.getFd());
// }


bool Channel::isInChannel(Client& client)
{
    if (this->_clients.find(client.getFd()) == this->_clients.end())
        return false;
    return true;
}