#include "Client.hpp"
#include <netinet/in.h>

Client::Client(int fd, const struct sockaddr& addr) : _fd(fd)
{
    this->_clientAddr = addr;
    this->_registered = false;
}

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
    Channel *tmp = new Channel(name, this, pass);
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



std::vector<std::string> split(std::string s, std::string delimiter) 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) 
    {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::string Client::getCommand(void)
{
    return (this->_command);
}

void Client::setArguments(void)
{
    _arguments.clear();
    _command.clear();
    if (!this->_vecBuffer.empty())
    {
        std::string str(this->_vecBuffer.front());
        std::string delimiter = " "; // TODO avelacnel
        std::size_t end = 0;
        std::size_t i = 0;

        i = str.find(delimiter);
        std::cout << "hajox\n";
        if (i != std::string::npos)
        {
            std::cout << "barev\n";
            this->_command = str.substr(0, i);
            // std::cout << " his->_command = "<< this->_command << std::endl;
            str = str.substr(i);
        }

        i = 0;
        if (!str.empty())
        {
            // while (str[i] && str[i] == ' ')
            // while (str[i] && str[i] <= 32)
            //     i++;
            // if (end != std::string::npos)
            //     std::cout << "end != std::string::npos" << std::endl;
            // else
            //     std::cout << "end ==== std::string::npos" << std::endl;
            end = str.find(delimiter, i);
            while (end != std::string::npos)
            {
                while (str[i] && str[i] <= 32)
                    i++;
                if (str[i] && str[i] == ':') // TODO
                {
                    std::cout << "::= ['@' <tags> SPACE] [':' <source> SPACE] <command> <parameters> <crlf>" << std::endl;
                    break ;
                }
                // std::cout << "str = " << "'" << str[i] << "'" << std::endl;
                if (str[i])
                {
                    // std::cout << "str: " << str.substr(i, end - i) << std::endl;
                    this->_arguments.push_back(str.substr(i, end - i));
                //     if (!_arguments.empty())
                //     {
                //         std::vector<std::string>::iterator it = _arguments.begin();
                //         for (; it != _arguments.end(); ++it)
                //             std::cout << " VECTOR IS: " << *it << " ";
                // // std::cout << "count" << std::endl;
                //     }
                //     else
                //         std::cout << "_arguments SET  is empty" << std::endl;
                }
                i = end + 1;
                // while (str[i] && str[i] == ' ')
                while (str[i] && str[i] <= 32)
                    i++;
                end = str.find(delimiter, i);
            }
        }
        // this->_vecBuffer.pop_front();
        // vec.erase(vec.begin());
        this->_vecBuffer.erase(_vecBuffer.begin());
    }
}

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



// LA ~ LA ~ LA ~ LA ~ LA ~ LA 


void Client::reply(const std::string& reply) // TODO kisat!
{
    // (void)reply;
    std::string buff = ":" + this->getPrefix() + " " + reply + "\r\n";

    if (send(_fd, buff.c_str(), buff.length(), 0) == -1)
        std::cerr << "Error: can't send message to client." << std::endl;
}

std::string Client::getNICK(void)
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








