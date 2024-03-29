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
    if (!client.isRegistered())
    {
       client.reply(ERR_NOTREGISTERED(client.getNICK()));
       return ;
    }

    if (args.empty())
    {
        client.reply(ERR_NEEDMOREPARAMS(client.getNICK(), "JOIN"));
        return;
    }

     if (args[0] == "0")
    {
        // client.leavingForChannels(NULL, ""); // TODO
        // srv.checkForCloseCannel();
        // DEBUGGER();
        return ;
    }

    std::string name = args[0];
    std::string pass = args.size() > 1 ? args[1] : "";

    std::map<std::string, std::string> _valid_name = stringToMap(name, pass);
    for (std::map<std::string, std::string>::iterator it = ch.begin(); it != ch.end(); ++it)
    {
        name = it->first;
        pass = it->second;
        if (name[0] != '#' && name[0] != '&')
        {
            client.reply(ERR_BADCHANMASK(client.getNICK(), name + static_cast<char>(1)));
            return ;
        }
        Channel* channel = srv.getChannel(name);
        if (!channel)
        {
            channel = srv.createChannel(name, pass);
        }

        // if (channel->isInChannel(client))
        // {
        //     client.reply(ERR_USERONCHANNEL(client.getNICK(), client.getNICK(), name + static_cast<char>(1)));
        //     return ;
        // }

        if (channel->isInviteOnly())
        {
            client.reply(ERR_INVITEONLYCHAN(client.getNICK(), name + static_cast<char>(1)));
            return ;
        }

        if (channel->channelIsFull())
        {
            client.reply(ERR_CHANNELISFULL(client.getNICK(), name + static_cast<char>(1)));
            return ;
        }

        if (channel->getKey() != pass)
        {
            client.reply(ERR_BADCHANNELKEY(client.getNICK(), channelName, "Cannot join channel (+k)"));
            return ;
        }
    }

    Channel *channel = client.getChannel(client.getNICK());
	// if (channel) 
    // {
	// 	client.reply(ERR_TOOMANYCHANNELS(client.getNICK(), name));
	// 	return;
	// }

    channel = _srv.getChannel(name); //TODO nayel !!
	if (!channel)
		channel = _srv.createChannel(name, pass, client);

    if (channel->get_limit() > 0 && channel->get_size() >= channel->get_limit()) //TODO esim ?
    {
		client.reply(ERR_CHANNELISFULL(client.getNICK(), name));
		return;
	}

    if (channel->get_pass() != pass)
    {
		client.reply(ERR_BADCHANNELKEY(client.getNICK(), name, "Cannot join channel (+k)"));
		return;
	}
    channel->joinClient(client);
}



// void Command::CommandJOIN(Client *C)
// {

    // if (_arg[0] == "0") // TODO
    // {
    //     C->leavingForChannels(NULL, "");
    //     srv.checkForCloseCannel();
    //     DEBUGGER();
    //     return ;
    // }

    std::map<std::string, std::string> ch = stringToMap(channelName, pass);
    for (std::map<std::string, std::string>::iterator it = ch.begin(); it != ch.end(); ++it)
    {
        channelName = it->first;
        pass = it->second;
        if (channelName[0] != '#' && channelName[0] != '&')
        {
            C->reply(ERR_BADCHANMASK(C->getNICK(), channelName + static_cast<char>(1)));
            DEBUGGER();
            return ;
        }
        Channel* channel = srv.getChannel(channelName);
        if (!channel)
        {
            channel = srv.createChannel(channelName, pass);
            DEBUGGER();
        }

        if (channel->isInChannel(C))
        {
            C->reply(ERR_USERONCHANNEL(C->getNICK(), C->getNICK(), channelName + static_cast<char>(1)));
            DEBUGGER();
            return ;
        }

        if (channel->isInviteOnly())
        {
            C->reply(ERR_INVITEONLYCHAN(C->getNICK(), channelName + static_cast<char>(1)));
            DEBUGGER();
            return ;
        }

        if (channel->channelIsFull())
        {
            C->reply(ERR_CHANNELISFULL(C->getNICK(), channelName + static_cast<char>(1)));
            DEBUGGER();
            return ;
        }

        if (channel->getKey() != pass)
        {
            C->reply(ERR_BADCHANNELKEY(C->getNICK(), channelName, "Cannot join channel (+k)"));
            DEBUGGER();
            return ;
        }
        C->joinToChannel(channel);

        
        DEBUGGER();
    }
}