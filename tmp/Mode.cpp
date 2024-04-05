#include "Command.hpp"

Mode::Mode(IRC_Server& srv) : Command(srv) {}

Mode::~Mode() {}

// syntax:  MODE <nickname> <flags> (user)
//          MODE <channel> <flags> [<args>]

void    Mode::execute(Client& client, std::vector<std::string> args)
{
    // hanling errors

    if (!client.isRegistered())
    {
        client.reply(ERR_NOTREGISTERED(client.getNICK()));
        return ;
    }

    if (args.empty() || args.size() < 2)
    {
        client.reply(ERR_NEEDMOREPARAMS(client.getNICK(), "MODE"));
        return ;
    }
    
    // std::string target = args.at(0);
    std::string channelName = args[0];

    Channel* channel = _srv.getChannel(channelName);
    if (!channel)
    {
        client.reply(ERR_NOSUCHCHANNEL(client.getNICK(), channelName + static_cast<char>(1)));
        return ;
    }

    if (!channel->isInChannel(client))
    {
        client.reply(ERR_NOTONCHANNEL(client.getNICK(), channelName + static_cast<char>(1)));
        return ;
    }


    // if (channel->get_admin() != client) (pyunik)
    // {
    //     client.reply(ERR_CHANOPRIVSNEEDED(client.get_nickname(), target));
    //     return;
    // }

    // if (!channel->isOperator(C))
    // {
    //     client.reply(ERR_CHANOPRIVSNEEDED(client.getNICK(), channelName + static_cast<char>(1)));
    //     return ;
    // }

    if (args.size() > 1)
    {
        std::string mode = args[1];

        // MODE +/- i
        if (mode == "i" || mode == "+i" || mode == "-i")
        {
            bool condition = (mode == "-i") ? false : true;
            mode = (mode == "i") ? "+i" : mode;

            // channel->setInviteOnly(condition); TODO
            client.sendMsg(RPL_MODE(client.getPrefix(), channelName, mode));
            client.reply(RPL_CHANNELMODEIS(channelName, channelName + static_cast<char>(1), mode));
        }
        else if (mode == "t" || mode == "+t" || mode == "-t")
        {
            bool condition = (mode == "-t") ? false : true;
            mode = (mode == "t") ? "+t" : mode;

            // channel->setTopicMode(condition); TODO
            client.sendMsg(RPL_MODE(client.getPrefix(), channelName, mode));
            client.reply(RPL_CHANNELMODEIS(channelName, channelName + static_cast<char>(1), mode));
        }
         else if (mode == "k" || mode == "+k" || mode == "-k")
        {
            std::string key;
            if (args.size() > 2)
                key = args[2];

            if (mode != "-k")
            {
                if (channel->get_pass() != "")
                {
                    client.reply(ERR_KEYSET(client.getNICK(), mode));
                    return;
                }

                channel->set_pass(key);
                client.sendMsg(RPL_MODE(client.getPrefix(), channelName, "+k " + key));
            }
            else
            {
                if (channel->get_pass() == key)
                {
                    channel->set_pass("");
                    client.sendMsg(RPL_MODE(client.getPrefix(), channelName, "-k "));
                }
                else
                {
                    client.reply(ERR_BADCHANNELKEY(client.getNICK(), mode, ":invalid key"));
                    return ;
                }
            }
            client.reply(RPL_CHANNELMODEIS(channelName, channelName + static_cast<char>(1), mode));
        }
        // MODE +/- o
        else if (mode == "o" || mode == "+o" || mode == "-o")
        {
            if (args.size() < 3)
            {
                client.reply(ERR_NEEDMOREPARAMS(client.getNICK(), "MODE"));
                return ;
            }

            std::string nickname = args[2];
            Client* client = channel->getClientByNick(nickname);
            if (!client)
            {
                client.reply(ERR_USERNOTINCHANNEL(client.getNICK(), nickname, channelName + static_cast<char>(1)));
                return ;
            }

            if (mode != "-o")
            {
                client->sendMsg(RPL_MSG(client.getPrefix(), "MODE", channelName, ":you are now a channel operator"));
                channel->addOperator(client);
            }
            else
            {
                if (!channel->isAdmin(client) && channel->isOperator(client))
                {
                    client->sending(RPL_MSG(client.getPrefix(), "MODE", channelName, ":you are no longer a channel operator"));
                    channel->removeOperator(client);
                }
            }
            client.reply(RPL_CHANNELMODEIS(channelName, channelName + static_cast<char>(1), mode));
        }
    }
}





// void Command::commandMODE(Client *C)
// {

//     if (_arg.size() > 1)
//     {
//      
//         }
//         // MODE +/- o
//         else if (mode == "o" || mode == "+o" || mode == "-o")
//         {
//             if (_arg.size() < 3)
//             {
//                 C->reply(ERR_NEEDMOREPARAMS(C->getNICK(), "MODE"));
//                 DEBUGGER();
//                 return ;
//             }

//             std::string nickname = _arg[2];
//             Client* client = channel->getClientByNick(nickname);
//             if (!client)
//             {
//                 C->reply(ERR_USERNOTINCHANNEL(C->getNICK(), nickname, channelName + static_cast<char>(1)));
//                 DEBUGGER();
//                 return ;
//             }

//             if (mode != "-o")
//             {
//                 DEBUGGER();
//                 client->sending(RPL_MSG(C->getPrefix(), "MODE", channelName, ":you are now a channel operator"));
//                 channel->addOperator(client);
//             }
//             else
//             {
//                 if (!channel->isAdmin(client) && channel->isOperator(client))
//                 {
//                     DEBUGGER();
//                     client->sending(RPL_MSG(C->getPrefix(), "MODE", channelName, ":you are no longer a channel operator"));
//                     channel->removeOperator(client);
//                 }
//             }
//             C->reply(RPL_CHANNELMODEIS(channelName, channelName + static_cast<char>(1), mode));
//         }
//         // MODE +/- l
//         else if (mode == "l" || mode == "+l" || mode == "-l")
//         {
//             if (mode != "-l")
//             {
//                 if (_arg.size() < 3)
//                 {
//                     C->reply(ERR_NEEDMOREPARAMS(C->getNICK(), "MODE"));
//                     DEBUGGER();
//                     return ;
//                 }

//                 int new_limit = std::atoi(_arg[2].c_str());
//                 if (new_limit < 1)
//                 {
//                     C->reply(ERR_UNKNOWNMODE(C->getNICK(), mode, " :limit must be greater than 0"));
//                     DEBUGGER();
//                     return;
//                 }
//                 channel->setChannelLimit(new_limit);
//             }
//             else
//             {
//                 channel->setChannelLimit(0); // unlimit
//             }
            
//             C->reply(RPL_CHANNELMODEIS(channelName, channelName + static_cast<char>(1), mode));
//         }
//         else if (mode == "b")
//         {
//             // do nothink to prevent KVirc error message
//             DEBUGGER();
//         }
//         else
//         {
//             C->reply(ERR_UNKNOWNMODE(C->getNICK(), mode, " :is unknown mode char to me"));
//             DEBUGGER();
//             return;
//         }
//     }
// }
