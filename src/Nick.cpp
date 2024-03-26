#include "Command.hpp"

Nick::Nick(IRC_Server* srv, bool auth) : Command(srv, auth) {}

Nick::~Nick() {}

// syntax: NICK <nickname>

void    Nick::execute(Client* client, std::vector<std::string> args)
{
    if (args.empty() || args[0].empty()) 
    {
        client->reply(ERR_NONICKNAMEGIVEN(client->getNICK()));
        return;
    }

    std::string nickname = args[0];

    if (_srv->getClient(nickname))
    {
        client->reply(ERR_NICKNAMEINUSE(client->getNICK()));
        return;
    }

    client->setNICK(nickname);
    // client->welcome();
    client->checkForRegistered();
}
