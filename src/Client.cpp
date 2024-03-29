#include "Client.hpp"
#include <netinet/in.h>
#include <sstream>
#include <utility>
#include "Numeric_and_error_replies.hpp"

// void *get_in_addr(struct sockaddr *sa)
// {
//     if (sa->sa_family == AF_INET)
//         return &(((struct sockaddr_in*)sa)->sin_addr);
//     return &(((struct sockaddr_in6*)sa)->sin6_addr);
// }

Client::Client(int fd, const struct sockaddr& addr) : _fd(fd)
{
    this->_clientAddr = addr;
    this->_registered = false;
}

// std::string Client::getRemoteAddr() const
// {
//     return (inet_ntoa((struct sockaddr_in)_clientAddr.sin_addr));
// }

Client::~Client()
{

}

bool Client::isRegistered(void)
{
    return (this->_registered);
}

// void Client::checkForRegistered(void)
// {
//     if (!_pass.empty() && !_username.empty() && !_nick.empty() && !_registered)
//     {
//         this->_registered = true;
//          reply(RPL_WELCOME(_nick));
//     }
// }

bool Client::checkForRegistered(void)
{
    if (!_pass.empty() && !_username.empty() && !_nick.empty() && !_registered)
    {
        this->_registered = true;
        reply(RPL_WELCOME(_nick));
    }
    else
        this->_registered = false;

    return (this->_registered);
}

int Client::getFd(void)
{
    return (this->_fd);
}

void Client::setPASS(const std::string& pass)
{
    this->_pass = pass;
}

std::string Client::getPASS(void)
{
    return (_pass);
};

void Client::setNICK(const std::string& nick) // TODO sending??
{
    this->_nick = nick;  
}

void Client::setUSER(const std::string& username, const std::string& realname)
{
    this->_username = username;
    this->_realname = realname;
}

//   std::map<std::string, std::pair<Channel*, TypeClient>>
Channel* Client::createChannel(const std::string& name, const std::string& pass)
{
    // this->_channels.insert(name, std::pair<Channel*, TypeClient>(tmp, Owner));
    if (this->_channels.find(name) == this->_channels.end())
    {
        return (NULL);
    }
    Channel *tmp = new Channel(name, pass, this);
    this->_channels[name] = std::make_pair(tmp, Owner);
    return (tmp);
}

void Client::leaveChannel(const std::string& name)
{
    std::map<std::string, std::pair<Channel*, TypeClient> >::iterator it = this->_channels.find(name);
    if (it != this->_channels.end())
    {
        it->second.first->deleteClient(*this);
        this->_channels.erase(it);  //TODO - ha vor ?
    }
}

// void Client::joinToChannel(Client *client)
// {
//     channel->joinClient()
// }





std::string     trim(const std::string& str)
{
    std::string WHITESPACE = " \n\r\t\f\v";
    std::string result = "";

    size_t  start = str.find_first_not_of(WHITESPACE);
    if (start != std::string::npos)
        result = str.substr(start);

    size_t  end = result.find_last_not_of(WHITESPACE);
    if (end != std::string::npos)
        result = result.substr(0, end + 1);

    return result;
}

std::vector<std::string> split(std::string const &input) // TODO hamozvel vor isspace ova ashxatum
{
    std::istringstream buffer(input);
    std::vector<std::string> ret;

    std::copy(std::istream_iterator<std::string>(buffer), 
              std::istream_iterator<std::string>(),
              std::back_inserter(ret));
    return ret;
}


// std::vector<std::string> split(std::string s, std::string delimiter)
// {
//     size_t pos_start = 0, pos_end, delim_len = delimiter.length();
//     std::string token;
//     std::vector<std::string> res;

//     while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) 
//     {
//         token = s.substr (pos_start, pos_end - pos_start);
//         pos_start = pos_end + delim_len;
//         res.push_back (token);
//     }

//     res.push_back (s.substr (pos_start));
//     return res;
// }

// std::vector<std::string> split(std::string s)
// {
//     size_t pos_start = 0, pos_end, delim_len = delimiter.length();
//     std::string token;
//     std::vector<std::string> res;
//     std::stream

//     while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) 
//     {
//         token = s.substr (pos_start, pos_end - pos_start);
//         pos_start = pos_end + delim_len;
//         res.push_back (token);
//     }

//     res.push_back (s.substr (pos_start));
//     return res;
// }

std::string Client::getCommand(void)
{
    return (this->_command);
}

void Client::setArguments(void)
{
    _arguments.clear();
    _command.clear();
    if (!this->_vecBuffer.empty() && !this->_vecBuffer[0].empty())
    {
        std::vector<std::string> splitedVec = split(_vecBuffer[0]);
        _command = splitedVec[0];
        _arguments = std::vector<std::string>(splitedVec.begin() + 1, splitedVec.end());
    }
}

// void Client::setArguments(void)
// {
//     _arguments.clear();
//     _command.clear();
//     if (!this->_vecBuffer.empty())
//     {
//         std::string str(this->_vecBuffer.front());
//         std::string delimiter = " "; // TODO avelacnel
//         std::size_t end = 0;
//         std::size_t i = 0;

//         i = str.find(delimiter);
//         std::cout << "hajox\n";
//         if (i != std::string::npos)
//         {
//             std::cout << "barev\n";
//             this->_command = str.substr(0, i);
//             // std::cout << " his->_command = "<< this->_command << std::endl;
//             str = str.substr(i);
//         }

//         i = 0;
//         if (!str.empty())
//         {
//             // while (str[i] && str[i] == ' ')
//             // while (str[i] && str[i] <= 32)
//             //     i++;
//             // if (end != std::string::npos)
//             //     std::cout << "end != std::string::npos" << std::endl;
//             // else
//             //     std::cout << "end ==== std::string::npos" << std::endl;
//             end = str.find(delimiter, i);
//             while (end != std::string::npos)
//             {
//                 while (str[i] && str[i] <= 32)
//                     i++;
//                 if (str[i] && str[i] == ':') // TODO
//                 {
//                     std::cout << "::= ['@' <tags> SPACE] [':' <source> SPACE] <command> <parameters> <crlf>" << std::endl;
//                     break ;
//                 }
//                 // std::cout << "str = " << "'" << str[i] << "'" << std::endl;
//                 if (str[i])
//                 {
//                     // std::cout << "str: " << str.substr(i, end - i) << std::endl;
//                     this->_arguments.push_back(str.substr(i, end - i));
//                 //     if (!_arguments.empty())
//                 //     {
//                 //         std::vector<std::string>::iterator it = _arguments.begin();
//                 //         for (; it != _arguments.end(); ++it)
//                 //             std::cout << " VECTOR IS: " << *it << " ";
//                 // // std::cout << "count" << std::endl;
//                 //     }
//                 //     else
//                 //         std::cout << "_arguments SET  is empty" << std::endl;
//                 }
//                 i = end + 1;
//                 // while (str[i] && str[i] == ' ')
//                 while (str[i] && str[i] <= 32)
//                     i++;
//                 end = str.find(delimiter, i);
//             }
//         }
//         // this->_vecBuffer.pop_front();
//         // vec.erase(vec.begin());
//         this->_vecBuffer.erase(_vecBuffer.begin());
//     }
// }

std::vector<std::string> Client::getArguments(void)
{
    return (this->_arguments);
}


void Client::splitbuffer(void)
{
    std::string str = this->_buffer;
    std::string del = "\r\n";
    size_t start = 0;

    _vecBuffer.clear();
    if (str.find(del) == std::string::npos)
        del = '\n';
    
    size_t end = str.find(del);
    // if (end == std::string::npos)
    // {
    //     std::cout << "offofofof" << std::endl;
    // }

    while (end != std::string::npos)
    {
        this->_vecBuffer.push_back(str.substr(start, end - start));
        // if (this->_vecBuffer.empty())
        //     std::cout << "vector is empty" << std::endl; 
        // else
        //     std::cout << "vector is NOT empty" << std::endl;
        start = end + del.length();
        end = str.find(del, start);
    }
}



/* void            Client::write(const std::string& message) const 
{
    std::string buffer = message + "\r\n";
    if (send(_fd, buffer.c_str(), buffer.length(), 0) < 0)
        throw std::runtime_error("Error while sending a message to a client!");
}

void            Client::reply(const std::string& reply)
{
    this->write(":" + get_prefix() + " " + reply);
} */

// LA ~ LA ~ LA ~ LA ~ LA ~ LA 


void Client::reply(const std::string& reply) // TODO kisat!
{
    // (void)reply;
    std::string buff = ":" + this->getPrefix() + " " + reply + "\r\n";

    if (send(_fd, buff.c_str(), buff.length(), 0) < 0)
        std::cerr << "Error: can't send message to client." << std::endl;
}

std::string Client::getNICK(void) const
{
    return (this->_nick);
}

std::string Client::getPrefix(void)
{
    std::string prefix = this->_nick;

    if (!this->_username.empty())
    {
        prefix += "!" + this->_username;
    }

    if (!this->_hostname.empty())
    {
        prefix += "@" + this->_hostname;
    }

    return (prefix); 
}




Channel * Client::getChannel(const std::string& name)
{
    std::map<std::string, std::pair<Channel*, TypeClient> >::iterator it = this->_channels.find(name);
    if (it == this->_channels.end())
    {
        return (NULL);
    }
    return (it->second.first);
}

bool Client::joinToChannel(Channel &channel) //TODO  hery chanicel :D
{

    std::cout << "joinToChannel\n";

    std::map<std::string, std::pair<Channel*, TypeClient> >::iterator it = this->_channels.find(channel.getName());

    if (it == this->_channels.end())
    {
        // if (channel->_clients.empty())
        // channel.joinClient(*this);
        this->_channels.insert(std::pair<std::string, std::pair<Channel*, TypeClient> >(channel.getName(), std::pair<Channel*, TypeClient>(&channel, Admin))); //TODO
    }
    else
    {
        this->reply(ERR_USERONCHANNEL(this->getNICK(), this->getNICK(), channel._name + static_cast<char>(1)));
        return ;

    }

    // Send replies
    
    // reply(RPL_NAMREPLY(_nickname, channel->getName(), users));
    // reply(RPL_ENDOFNAMES(_nickname, channel->getName()));
    // channel->broadcast(RPL_JOIN(get_prefix(), channel->getName()));
}
