#include "Command.hpp"

Part::Part(IRC_Server& srv) : Command(srv) {}

Part::~Part() {}

// syntax: PART <channels> [<message>]

void    Part::execute(Client& client, std::vector<std::string> args)
{
    if (args.empty()) 
    {
        client.reply(ERR_NEEDMOREPARAMS(client.getNICK(), "PART"));
        return;
    }

    std::string name = args[0];
    Channel     *channel = _srv.getChannel(name);

    if (!channel || !client.getChannel(name) /* || client.getChannel()->getName() != name */)
    {
        client.reply(ERR_NOSUCHCHANNEL(client.getNICK(), name));
        return;
    }

    client.leaveChannel(name); // TODO im function-y nayel 
}
