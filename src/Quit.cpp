#include "Command.hpp"

Quit::Quit(IRC_Server& srv, bool auth) : Command(srv, auth) {}

Quit::~Quit() {}

// syntax: QUIT [<message>]

void    Quit::execute(Client& client, std::vector<std::string> args)
{
    std::string reason;
    if (args.empty())
    {
        reason = client.getMSG().empty() ? "Leaving ..." :  client.getMSG();
    }

    client.sendMsg(RPL_QUIT(client.getPrefix(), reason));
    client.leavALLChannels();
    // std::cout << "_srv channles = " << _channels.size() << std::endl;
    _srv.checkForCloseCannel();
    // close(client.getFd());
    // FD_CLR(C->getFd(), &_server->Desc._READ_fds);
}
