
#include "Command.hpp"

Quit::Quit(IRC_Server& srv, bool auth) : Command(srv, auth) {}

Quit::~Quit() {}

// syntax: QUIT [<message>]

void    Quit::execute(Client& client, std::vector<std::string> args)
{
    // std::string reason = args.empty() ? "Leaving..." : args.at(0);

    // if (reason.at(0) == ':')
    //     reason = reason.substr(1);

    // client.reply(RPL_QUIT(client.getPrefix(), reason));
	// // _srv.on_client_disconnect(client.getFd()); // TODO offff



    std::string reply;
    if (!args.empty())
    {

        reply = args[0];
        for(size_t i = 1; i < args.size(); ++i)
            reply += " " + args[i];
    }
    // client.leavALLChannels(reply);

    // close(C->getFd());
    // FD_CLR(C->getFd(), &_server->Desc._READ_fds);
    // _server->addRemoveFd(C);
}
