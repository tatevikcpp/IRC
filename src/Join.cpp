#include "Command.hpp"

Join::Join(IRC_Server& srv) : Command(srv) {}

Join::~Join() {}

// syntax: JOIN <channels> [<keys>]


std::map<std::string, std::string> stringToMap(std::string &keys, std::string &values)
{
    std::map<std::string, std::string> result;

    std::vector <std::string> key;
    std::vector <std::string> value;
    keys += ',';
    values += ',';
    size_t start = 0;
    size_t index = keys.find(',', start);
    while(index != std::string::npos)
    {
        key.push_back(keys.substr(start, index - start));
        start = index + 1;
        index = keys.find(',', start);
    }

    start = 0;
    index = values.find(',', start);
    while(index != std::string::npos)
    {
        value.push_back(values.substr(start, index - start));
        start = index + 1;
        index = values.find(',', start);
    }
    start = 0;
    index =  key.size();
    for( ; start < index; ++start)
    {
        if (!key[start].empty())
        {
            result[key[start]] = start >= value.size() ? "" : value[start];
        }
    }
    
    return result;
}

void    Join::execute(Client& client, std::vector<std::string> args)
{
    std::vector<std::string>::iterator it = std::find(args.begin(), args.end(), "");
    std::vector<std::string> channelNames(args.begin(), it);
    std::vector<std::string> chanelKeys(it, args.end());

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

    if (args[0] == "0") //TODO  harmaracnel!
    {
        client.leavALLChannels();
        _srv.checkForCloseCannel();
        return ;
    }
    for (size_t i = 0; i < channelNames.size(); i++)
    {
        std::string name = channelNames[i];
        std::string pass = args.size() > 1 ? chanelKeys[i] : "";

        std::cout << "name = " << name << std::endl << "pass = " << pass << std::endl;

        // std::map<std::string, std::string> ch = stringToMap(name, pass);
        // for (std::map<std::string, std::string>::iterator it = ch.begin(); it != ch.end(); ++it)
        // {
            // name = it->first;
            // pass = it->second;
            if (name[0] != '#' && name[0] != '&')
            {
                client.reply(ERR_BADCHANMASK(client.getNICK(), name + static_cast<char>(1)));
                return ;
            }
            Channel* channel = _srv.getChannel(name);
            if (!channel)
            {
                channel = _srv.createChannel(name, pass, client);
                channel->nameReply(client);
                return ;
            }
            else  if (channel->isInChannel(client))
            {
                client.reply(ERR_USERONCHANNEL(client.getNICK(), client.getNICK(), name + static_cast<char>(1)));
                return ;
            }
            if (channel->isInviteOnly()) // TODO 
            {
                client.reply(ERR_INVITEONLYCHAN(client.getNICK(), name + static_cast<char>(1)));
                return ;
            }

            if (channel->channelIsFull())
            {
                client.reply(ERR_CHANNELISFULL(client.getNICK(), name + static_cast<char>(1)));
                return ;
            }

            if (channel->get_pass() != pass)
            {
                client.reply(ERR_BADCHANNELKEY(client.getNICK(), name, "Cannot join channel (+k)"));
                return ;
            }
            channel->joinClient(client);
            channel->nameReply(client);
        // }
    }
}