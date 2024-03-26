#pragma once
#include <iostream>
#include "Client.hpp"
#include <map>
#include <set>

class Client;
class Channel
{
    public:
        Channel(const std::string& name, const std::string& pass = "", Client *client = NULL);
        ~Channel();

        // void addClient(Client &client);
        void deleteClient(Client &client);
        void joinClient(Client *client);
        bool isInChannel(Client* client);
        void sending(Client* C, const std::string& msg/* , const std::string& cmd */);
        void addOperator(Client *clinet);
        bool channelIsFull(void);
        bool emptyChannel(void);

        size_t get_limit() const;
        size_t get_size()const;
        std::string get_pass() const;

        std::string getName(void);

        void broadcast(const std::string& message);
        void broadcast(const std::string& message, Client* exclude);

        void print() const;

    private:
        std::map<int, Client *> _clients;
        std::set<std::string> _admins;
        size_t _limit;
    public:
        std::string _name;
        std::string _pass;
};