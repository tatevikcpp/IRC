#include "Command.hpp"

Join::Join(IRC_Server* srv) : Command(srv) {}

Join::~Join() {}

// syntax: JOIN <channels> [<keys>]

void    Join::execute(Client* client, std::vector<std::string> args)
{
    if (args.empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNICK(), "JOIN"));
        return;
    }

    std::string name = args[0];
    std::string pass = args.size() > 1 ? args[1] : "";

  Channel *channel = client->getChannel(client->getNICK());
	if (channel) 
  {
		client->reply(ERR_TOOMANYCHANNELS(client->getNICK(), name));
		return;
	}

  channel = _srv->getChannel(name); //TODO nayel !!
	if (!channel)
		channel = _srv->createChannel(name, pass, client);

  if (channel->get_limit() > 0 && channel->get_size() >= channel->get_limit())
  {
		client->reply(ERR_CHANNELISFULL(client->getNICK(), name));
		return;
	}

  if (channel->get_pass() != pass) 
  {
		client->reply(ERR_BADCHANNELKEY(client->getNICK(), name));
		return;
	}

	client->jionToChannel(channel);
}
