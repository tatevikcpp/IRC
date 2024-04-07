#include "Command.hpp"

PrivMsg::PrivMsg(IRC_Server& srv) : Command(srv) {}

PrivMsg::~PrivMsg() {}

// syntax: PRIVMSG <msgtarget> :<message>

void    PrivMsg::execute(Client& client, std::vector<std::string> args)
{
    if (!client.isRegistered())
    {
        client.reply(ERR_NOTREGISTERED(client.getNICK()));
        return;
    }
    if (args.empty())
    {
        client.reply(ERR_NEEDMOREPARAMS(client.getNICK(), "PRIVMSG"));
        return ;
    }
    if (args.size() < 2)
    {
        client.reply(ERR_NOTEXTTOSEND(client.getNICK()));
        return ;
    }

    // extract the target and the message

    // std::vector<std::string> target = args[0];
    std::string target = args[0];
    std::string message;

    std::vector<std::string>::iterator it = args.begin() + 1;
    std::vector<std::string>::iterator end = args.end();

    while (it != end)
    {
        message.append(*it + " ");
        it++;
    }

    if (message[0] == ':')
        message.erase(message.begin());

    // if notice is for a channel

    if (target[0] == '#' || target[0] == '&')
    {
        Channel* channel =  _srv.getChannel(target);
        // if (client._channels.find(target) == client._channels.end())

        // channel not found
        if (!channel)
        {
            // client.reply(ERR_NOSUCHCHANNEL(client.getNick(), target));
            client.reply(ERR_NOSUCHNICK(client.getNICK(), target));
			return;
        }

        // channel is not for external messages
        // if (!channel->ext_msg())
        // {
        //     std::vector<std::string> nicknames = channel->getNick();

        //     std::vector<std::string>::iterator it = nicknames.begin();
        //     std::vector<std::string>::iterator end = nicknames.end();

        //     // check if client is in the channel
        //     while (it != end)
        //     {
        //         if (*it == client.getNick())
        //             break;

        //         it++;
        //     }

        //     // if not in channel
        //     if (it == end)
        //     {
        //         client.reply(ERR_CANNOTSENDTOCHAN(client.getNick(), target));
        //         return;
        //     }
        // }

        // channel->broadcast(RPL_PRIVMSG(client.getPrefix(), target, message), client);
        return;
    }

    // else if notice is for a client

    // Client  *dest = _srv.getClient(target);
    // if (!dest)
    // {
    //     client.reply(ERR_NOSUCHNICK(client.getNick(), target));
	// 	return;
    // }
    // dest->write(RPL_PRIVMSG(client.getPrefix(), target, message));
}
