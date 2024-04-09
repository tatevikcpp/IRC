#include "Command.hpp"

User::User(IRC_Server& srv, bool auth) : Command(srv, auth) {}

User::~User() {}

// stntax: USER <username> <hostname> <servername> <realname>

void    User::execute(Client& client, std::vector<std::string> args) //USER -y 2-rd angam ell a anum
{
    if (client.getPASS().empty())
    {
        std::cout << "client.getPASS() "  << client.getPASS() << std::endl;
        std::cout << "user in execute" << std::endl;
        client.reply(ERR_NOTREGISTERED(client.getNICK()));
        return ;
    }
    if (client.isRegistered())
    {
        client.reply(ERR_ALREADYREGISTERED(client.getNICK()));
        return;
    }

    if (args.size() < 4 || args[1] != "0" || args[2] != "*")
    {
        client.reply(ERR_NEEDMOREPARAMS(client.getNICK(), "USER"));
        return;
    }


    // client.set_username(args[0]);
    // client.set_realname(args[3]);
    client.setUSER(args[0], args[3]);
    // client.welcome();
    client.checkForRegistered();
}
