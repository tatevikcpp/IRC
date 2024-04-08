#include "Command.hpp"

PrivMsg::PrivMsg(IRC_Server& srv) : Command(srv) {}

PrivMsg::~PrivMsg() {}

// syntax: PRIVMSG <msgtarget> :<message>

void    PrivMsg::execute(Client& client, std::vector<std::string> args) //TODO send all
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

    std::string message = client.getMSG();
    if (message.empty())
    {
        client.reply(ERR_NOTEXTTOSEND(client.getNICK()));
        return ;
    }

    // extract the target and the message

    // std::vector<std::string> target = args[0];
    // std::string target = args[0];

    // std::vector<std::string>::iterator it = args.begin() + 1;
    // std::vector<std::string>::iterator end = args.end();

    // while (it != end)
    // {
    //     message.append(*it + " ");
    //     it++;
    // }

    // if (message[0] == ':')
    //     message.erase(message.begin());

    // if notice is for a channel

    for (size_t i = 0; i < args.size(); i++)
    {
        std::string target = args[i];
        if (target[i] == '#' || target[i] == '&')
        {
            target.erase(0, 1);
            Channel* channel = _srv.getChannel(target);
            if (!channel)
            {
                client.reply(ERR_NOSUCHNICK(client.getNICK(), target));
                continue; ;
            }
            if (!channel->isInChannel(client))
            {
                client.reply(ERR_CANNOTSENDTOCHAN(client.getNICK(), target));
                continue; ;
            }
            
            channel->sendMsg(client, message, "PRIVMSG");

            // if (message == "BOT" || (message.find(' ') != std::string::npos
            //     && message.substr(0, message.find(' ')) == "BOT"))
            // {
            //     _bot->Fetch(message);
            //     channel->sendingForBot(C, message, "PRIVMSG");
            //     DEBUGGER();
            // }
            // else
            // {
            //     channel->sending(C, message, "PRIVMSG");
            //     DEBUGGER();
            // }
        }
        else
        {
            Client* recv_client = _srv.getClient(target);
            if (!recv_client)
            {
                client.sendMsg(ERR_NOSUCHNICK(client.getNICK(), target));
                continue; ;
            }

            // client->sendMsg(RPL_MSG(client.getPrefix(), "PRIVMSG", target, message));
            // client.sendMsg(RPL_MSG(client.getPrefix(), "PRIVMSG", target, message));
            // recv_client->sendMsg(message);
            recv_client->sendMsg(RPL_MSG(client.getPrefix(), "PRIVMSG", target, message));

        }
    }
}





// void Command::commandPRIVMSG(Client *C)
// {
//     DEBUGGER();
//     if (!C->isRegistered())
//     {
//         C->reply(ERR_NOTREGISTERED(C->getNICK()));
//         DEBUGGER();
//         return;
//     }
//     if (_arg.empty())
//     {
//         C->reply(ERR_NEEDMOREPARAMS(C->getNICK(), "PRIVMSG"));
//         DEBUGGER();
//         return ;
//     }
//     if (_arg.size() < 2)
//     {
//         C->reply(ERR_NOTEXTTOSEND(C->getNICK()));
//         DEBUGGER();
//         return ;
//     }
     
//     DEBUGGER();
//     std::vector<std::string> targets;
//     std::string keys = _arg[0];

//     keys += ',';
//     size_t start = 0;
//     size_t index = keys.find(',', start);
//     DEBUGGER();
//     while(index != std::string::npos)
//     {
//         targets.push_back(keys.substr(start, index - start));
//         start = index + 1;
//         index = keys.find(',', start);
//     }

//     DEBUGGER();
//     size_t i = 1;
//     std::string message = _arg[i++];
//     for ( ; i < _arg.size(); ++i)
//         message.append(" " + _arg[i]);
    
//     DEBUGGER();
//     for (size_t i = 0; i < targets.size(); ++i)    
//     {
//         if (targets[i][0] == '#' || targets[i][0] == '&')
//         {
//             Channel* channel = _server->getChannel(targets[i]);
//             if (!channel)
//             {
//                 C->reply(ERR_NOSUCHNICK(C->getNICK(), targets[i]));
//                 return ;
//             }
//             if (!channel->isInChannel(C))
//             {
//                 C->reply(ERR_CANNOTSENDTOCHAN(C->getNICK(), targets[i]));
//                 return ;
//             }
//             DEBUGGER();


//             if (message == "BOT" || (message.find(' ') != std::string::npos
//                 && message.substr(0, message.find(' ')) == "BOT"))
//             {
//                 _bot->Fetch(message);
//                 channel->sendingForBot(C, message, "PRIVMSG");
//                 DEBUGGER();
//             }
//             else
//             {
//                 channel->sending(C, message, "PRIVMSG");
//                 DEBUGGER();
//             }
//         }
//         else
//         {
//             Client* client = _server->getClient(targets[i]);
//             if (!client)
//             {
//                 C->reply(ERR_NOSUCHNICK(C->getNICK(), targets[i]));
//                 DEBUGGER();
//                 return ;
//             }
//             DEBUGGER();

//             client->sending(RPL_MSG(C->getPrefix(), "PRIVMSG", targets[i], message));
//         }
//     }
//     DEBUGGER();
// }
