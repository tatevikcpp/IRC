#pragma once

#include <iostream>
#include "Client.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include "utils.hpp"


// esim e

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <map>



#define PORT "9034"   // port we're listening on

// senc eli
class Client;
class Channel;
class Command;

class IRC_Server
{
    public:
        // IRC_Server(const std::string& v1, const std::string& v2);
        IRC_Server(const char *port, const char *password);
        ~IRC_Server();
        void addChannel(Channel &);
        void delChannel(Channel *);
        Channel* createChannel(const std::string& name, const std::string& pass, Client &client);
        void addClientToChannel(const std::string& name, Client &);
        int start(void);
        // void initStruct(void);+

        // Channel *createChannel(const std::string& name, const std::string& pass);

        std::string getPASS(void);
        // Client *getClient(const std::string& nick);
        bool checkNickname(const std::string& nick);
        void changeNickname(Client &, const std::string& newNick);

        Client * getClient(const std::string& nick);
        Channel * getChannel(const std::string& name);

        void checkForCloseCannel(void);



        void print_channels();

    private:
        unsigned short _port;
        std::string _password;
        struct sockaddr_in _s_addr;
        std::map<std::string, Channel *> _channels;
        std::map<int, Client *> _clients;

        std::map<std::string, Command *> _commands;

        std::map<std::string, int> _nickname;
        int _select_fd;
        int _fdmax;
        int _listener;
        int _newfd;
        // Command* _command;
};