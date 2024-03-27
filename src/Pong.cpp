#include "Command.hpp"

Pong::Pong(IRC_Server& srv) : Command(srv) {}

Pong::~Pong() {}

// syntax: PONG <server1> [<server2>]

void    Pong::execute(Client& client, std::vector<std::string> args)
{
    if (args.empty())
    {
        client.reply(ERR_NEEDMOREPARAMS(client.getNICK(), "PONG"));
        return;
    }

    // client.write(RPL_PING(client.getPrefix(), args.at(0)));
    client.reply(RPL_PING(client.getPrefix(), args.at(0))); // TODO veranayel 
}
