#include "Command.hpp"

Join::Join(IRC_Server& srv) : Command(srv) {}

Join::~Join() {}

// syntax: JOIN <channels> [<keys>]


// std::map<std::string, std::string> stringToMap(std::string &keys, std::string &values) // TODO 
// {
//     std::map<std::string, std::string> result;

//     std::vector <std::string> key;
//     std::vector <std::string> value;
//     keys += ',';
//     values += ',';
//     size_t start = 0;
//     size_t index = keys.find(',', start);
//     while(index != std::string::npos)
//     {
//         key.push_back(keys.substr(start, index - start));
//         start = index + 1;
//         index = keys.find(',', start);
//     }

//     start = 0;
//     index = values.find(',', start);
//     while(index != std::string::npos)
//     {
//         value.push_back(values.substr(start, index - start));
//         start = index + 1;
//         index = values.find(',', start);
//     }
//     start = 0;
//     index =  key.size();
//     for( ; start < index; ++start)
//     {
//         if (!key[start].empty())
//         {
//             result[key[start]] = start >= value.size() ? "" : value[start];
//         }
//     }
    
//     return result;
// }

void    Join::execute(Client& client, std::vector<std::string> args)
{
     std::cout << "JOIN execute" << std::endl;
    std::vector<std::string>::iterator it = std::find(args.begin(), args.end(), "");
    std::vector<std::string> channelNames(args.begin(), it);

    std::vector<std::string> chanelKeys;
    if (it != args.end())
        chanelKeys.insert(chanelKeys.begin(), it + 1, args.end()) /* = std::vector<std::string>(it + 1, args.end()) */;

    if (!client.isRegistered())
    {
        client.reply(ERR_NOTREGISTERED(client.getNICK()));
        return ;
    }

    if (args.empty())
    {
        client.reply(ERR_NEEDMOREPARAMS(client.getNICK(), "JOIN"));
        return ;
    }

    if (args[0] == "0")
    {
        client.leavALLChannels();
        _srv.checkForCloseCannel();
        return ;
    }
    std::cout << "channelNames.size(): " << channelNames.size() << std::endl; 
    for (size_t i = 0; i < channelNames.size(); i++)
    {
        std::string name = channelNames[i];
        std::string pass = i < chanelKeys.size() ? chanelKeys[i] : "";

        std::cout << "name = " << name << std::endl << "pass = " << pass << std::endl;

        // std::map<std::string, std::string> ch = stringToMap(name, pass);
        // for (std::map<std::string, std::string>::iterator it = ch.begin(); it != ch.end(); ++it)
        // {
        //     name = it->first;
        //     pass = it->second;
            if (name[0] != '#' && name[0] != '&')
            {
                std::cout << "return1" << std::endl;
                client.reply(ERR_BADCHANMASK(client.getNICK(), name + static_cast<char>(1)));
                // return ;
                // break;
                continue;
            }

            // name.erase(0, 1);
            Channel* channel = _srv.getChannel(name);
            if (!channel)
            {
                std::cout << "return2" << std::endl;
                channel = _srv.createChannel(name, pass, client);
                channel->nameReply(client);
                // return ;
                // break;
                continue;
            }
            else  if (channel->isInChannel(client))
            {
                std::cout << "return3" << std::endl;
                client.reply(ERR_USERONCHANNEL(client.getNICK(), client.getNICK(), name + static_cast<char>(1)));
                // return ;
                // break;
                continue;
            }
            if (channel->isInviteOnly()) // TODO 
            {
                std::cout << "return4" << std::endl;
                client.reply(ERR_INVITEONLYCHAN(client.getNICK(), name + static_cast<char>(1)));
                // return ;
                // break;
                continue;
            }

            if (channel->channelIsFull())
            {
                std::cout << "return5" << std::endl;
                client.reply(ERR_CHANNELISFULL(client.getNICK(), name + static_cast<char>(1)));
                // return ;
                // break;
                continue;
            }

            if (channel->get_pass() != pass)
            {
                std::cout << "return6" << std::endl;
                client.reply(ERR_BADCHANNELKEY(client.getNICK(), name, "Cannot join channel (+k)"));
                // return ;
                // break;
                continue;
            }
            channel->joinClient(client);
            channel->sendInChannel(RPL_JOIN(client.getPrefix(), channel->getName()));
            
            channel->nameReply(client);

        // }
    }
            _srv.print_channels();
}