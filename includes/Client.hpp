#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "IRC_Server.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <map>

#include "Numeric_and_error_replies.hpp"

class IRC_Server;
class Channel;


enum TypeClient
{
    Owner,
    Operator,
    Primary
};

class Client
{

    public:

        Client(int fd, const struct sockaddr& addr);
        ~Client();


        const int _fd;
        void leaveChannel(const std::string& name);
        Channel* createChannel(const std::string& name, const std::string& pass = "");
        bool isRegistered(void);
        // std::string getNick(void);
        void setNICK(const std::string& nick);
        std::string getNICK(void);
        void setPASS(const std::string& pass);
        std::string getPASS(void);
        void setUSER(const std::string& username, const std::string& realname);
        // void checkForRegistered(void);
        bool checkForRegistered(void);
        void splitbuffer(void);



        // std::string     trim(const std::string& str);
        // std::vector<std::string> Client::split(std::string s, std::string delimiter);

        void setArguments(void);
        std::vector<std::string> getArguments(void);

        std::string getPrefix(void);
        void reply(const std::string& reply);
        
        std::string getCommand(void);

        int getFd(void);
        
        std::string _buffer;


        void print_vector()
        {
            if (!_arguments.empty())
            {
                std::vector<std::string>::iterator it = _arguments.begin();
                for (; it != _arguments.end(); ++it)
                    std::cout << *it << " " << std::endl;
            }
            else
                std::cout << "vector is empty" << std::endl;
        }

    private:

        // std::string _port;
        struct sockaddr _clientAddr;
        // std::map<std::string, Channel*> _channels;
        std::map<std::string, std::pair<Channel*, TypeClient> > _channels;


        std::string _pass;
        std::string _nick;
        std::string _username;
        std::string _hostname;
        std::string _realname;


        std::string _command;
        std::vector<std::string> _arguments;
        // std::list<std::string> _bufferlist; // or std::vector<std::string> _buffervec
        std::vector<std::string> _vecBuffer;

        bool _registered;
};