#include "Command.hpp"

Nick::Nick(IRC_Server& srv, bool auth) : Command(srv, auth) {}

Nick::~Nick() {}

// syntax: NICK <nickname>

bool nickIsCorrect(std::string buffer)
{
    std::string notAllowed = " ,*?!@$:#.";
    std::size_t pos = buffer.find_first_of(notAllowed);
    if (pos != std::string::npos)
    {
        return false;
    }
    return true;
}

void    Nick::execute(Client& client, std::vector<std::string> args)
{
    if (client.getPASS().empty())
    {
        std::cout << "nick" << std::endl;
        client.reply(ERR_NOTREGISTERED(client.getNICK()));
        return ;
    }
    if (args.empty() || args[0].empty()) 
    {
        client.reply(ERR_NONICKNAMEGIVEN(client.getNICK()));
        return;
    }

    std::string nickname = args[0];

    if (!nickIsCorrect(nickname))
    {
        client.reply(ERR_ERRONEUSNICKNAME(client.getNICK(), nickname));
        return ;
    }

    if (_srv.getClient(nickname))
    {
        client.reply(ERR_NICKNAMEINUSE(client.getNICK(), nickname));
        return;
    }

    client.setNICK(nickname);
    // client.welcome();
    client.checkForRegistered();
}



/* void Command::commandNICK(Client* C)
{
    if (C->getPASS().empty())
    {
        C->reply(ERR_NOTREGISTERED(C->getNICK()));
        return ;
    }
    if (_arg.empty())
    {
        C->reply(ERR_NONICKNAMEGIVEN(C->getNICK()));
        DEBUGGER();
        return ;
    }
    std::string nick = _arg[0];
    if (!nickIsCorrect(nick))
    {
        C->reply(ERR_ERRONEUSNICKNAME(C->getNICK(), nick));
        return ;
    }
    Client* client = _server->getClient(nick);
    if (client)
    {
        C->reply(ERR_NICKNAMEINUSE(C->getNICK(), nick));
        return ;
    }
    DEBUGGER();
    _server->updateNickMap(C, nick);
    DEBUGGER();
    C->setNICK(nick);
    DEBUGGER();
    C->checkForRegistered();
    DEBUGGER();
} */