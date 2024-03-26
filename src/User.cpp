#include "Command.hpp"

User::User(IRC_Server* srv, bool auth) : Command(srv, auth) {}

User::~User() {}

// stntax: USER <username> <hostname> <servername> <realname>

void    User::execute(Client* client, std::vector<std::string> args)
{
    if (client->isRegistered())
    {
        client->reply(ERR_ALREADYREGISTERED(client->getNICK()));
        return;
    }

    if (args.size() < 4)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNICK(), "USER"));
        return;
    }

    // client->set_username(args[0]);
    // client->set_realname(args[3]);
    client->setUSER(args[0], args[0]);
    // client->welcome();
    client->checkForRegistered();
}
