// #pragma once

// // Numeric replies
// #define RPL_WELCOME(source)                     "001 " + source + " :Welcome to the ft_irc Network"
// #define RPL_ENDOFWHO(name, source)              "315 " + name + " " + source + " :End of WHO list"
// #define RPL_CHANNELMODEIS(channelName1, channelName2, mode_params) "324 " + channelName1 + " " + channelName2 + " " + " " + mode_params
// #define RPL_NOTOPIC(channelName)                "331 # " + channelName
// #define RPL_TOPIC(channelName, topic)           "332 # " + channelName + " :" + topic
// #define RPL_INVITING(name, nick, ch)            "341 " + name + " " + nick + " " + ch
// #define RPL_WHOREPLY(name, ch, us, hst, nick, fl, re)"352 " + name + " " + ch + " " + us + " " + hst + " ft_irc " + nick + " " + fl + " :" + re
// #define RPL_NAMREPLY(nick, ch, nickList)        "353 " + nick + " = " + ch + " :" + nickList
// #define RPL_ENDOFNAMES(name, ch)                "366 " + name +  " " + ch + " :End of /NAMES list"

// // Error replies 
// #define ERR_NOSUCHNICK(source, command)         "401 " + source + " " + command + " :No such nick/channel"
// #define ERR_NOSUCHCHANNEL(source, command)      "403 " + source + " " + command + " :No such channel"
// #define ERR_CANNOTSENDTOCHAN(source, command)   "404 " + source + " " + command + " :Cannot send to channel"
// #define ERR_NORECIPIENT(source, command)        "411 " + source + " :No recipient given (" + command + ")"
// #define ERR_NOTEXTTOSEND(source)                "412 " + source + " :No text to send"
// #define ERR_UNKNOWNCOMMAND(source, command)     "421 " + source + " " + command + " :Unknown command"
// #define ERR_NONICKNAMEGIVEN(source)             "431 " + source + " :No nickname given"
// #define ERR_ERRONEUSNICKNAME(source, command)   "432 " + source + " " + command + " :Erroneous nickname"
// #define ERR_NICKNAMEINUSE(source, command)      "433 " + source + " " + command + " :Nickname is already in use"
// #define ERR_USERNOTINCHANNEL(src, com1, com2)   "441 " + src + " " + com1 + " " + com2 + " :They aren't on that channel"
// #define ERR_NOTONCHANNEL(source, command)       "442 " + source + " " + command + " :You're not on that channel"
// #define ERR_USERONCHANNEL(src, com1, com2)      "443 " + src + " " + com1 + " " + com2 + " :is already on channel"
// #define ERR_NOTREGISTERED(source)               "451 " + source + " :You have not registered"
// #define ERR_NEEDMOREPARAMS(source, command)     "461 " + source + " " + command + " :Not enough parameters"
// #define ERR_ALREADYREGISTERED(source)           "462 " + source + " :You may not reregister"
// #define ERR_PASSWDMISMATCH(source)               source + " :Password incorrect" //464
// #define ERR_KEYSET(source, command)             "467 " + source + " " + command + " :Channel key already set"
// #define ERR_CHANNELISFULL(source, command)      "471 " + source + " " + command + " :Cannot join channel (+l)"
// #define ERR_UNKNOWNMODE(source, command, msg)   "472 " + source + " " + command + " " + msg
// #define ERR_INVITEONLYCHAN(source, command)     "473 " + source + " " + command + " :Cannot join channel (+i)"
// #define ERR_BADCHANNELKEY(source, command, msg) "475 " + source + " " + command + " " + msg
// #define ERR_NOCHANMODES(channelName)            "477 # " + channelName + " :TOPIC mode is OFF ('MODE <channel> +t' is needed)"
// #define ERR_BADCHANMASK(source, command)        "476 " + source + " " + command + " :Bad Channel Mask"
// #define ERR_CHANOPRIVSNEEDED(source, command)   "482 " + source + " " + command + " :You're not channel operator"

// #define RPL_MSG(prefix, command, target, massage)   ":" + prefix + " " + command + " " + target + " :" + massage
// #define RPL_KICK(prefix, channel, target, reason)   ":" + prefix + " KICK " + channel + " " + target + " :" + reason
// #define RPL_PING(prefix, massage)                   ":" + prefix + " PONG :" + massage
// #define RPL_QUIT(prefix, massage)                   ":" + prefix + " QUIT :Quit: " + massage
// #define RPL_JOIN(prefix, target)                    ":" + prefix + " JOIN " + target
// #define RPL_PART(prefix, target)                    ":" + prefix + " PART " + target
// #define RPL_MODE(prefix, channel, target)           ":" + prefix + " MODE " + channel + " " + target
// #define RPL_INVITE(prefix, target, channel)         ":" + prefix + " INVITE " + target + " " + channel




#ifndef IRC_RESPONSE_HPP
#define IRC_RESPONSE_HPP

#include <iostream>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <time.h>

/* Error Responses */

#define ERR_NOTREGISTERED(source)                       "451 " + source + " :You have not registered"
#define ERR_ALREADYREGISTERED(source)                   "462 " + source + " :You may not register"
#define ERR_PASSWDMISMATCH(source)                      "464 " + source + " :Password is incorrect"
#define ERR_NONICKNAMEGIVEN(source)                     "431 " + source + " :Nickname not given"
#define ERR_NICKNAMEINUSE(source)                       "433 " + source + " " + source  + " :Nickname is already in use"

#define ERR_UNKNOWNCOMMAND(source, command)             "421 " + source + " " + command + " :Unknown command"
#define ERR_NEEDMOREPARAMS(source, command)             "461 " + source + " " + command + " :Not enough parameters"

#define ERR_TOOMANYCHANNELS(source, channel)            "405 " + source + " " + channel + " :You have joined too many channels"
#define ERR_NOTONCHANNEL(source, channel)               "442 " + source + " " + channel + " :You're not on that channel"
#define ERR_NOSUCHCHANNEL(source, channel)              "403 " + source + " " + channel + " :No such channel"
#define ERR_BADCHANNELKEY(source, channel)              "475 " + source + " " + channel + " :Cannot join channel (+k)"
#define ERR_CHANNELISFULL(source, channel)              "471 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_CANNOTSENDTOCHAN(source, channel)           "404 " + source + " " + channel + " :Cannot send to channel"
#define ERR_CHANOPRIVSNEEDED(source, channel)           "482 " + source + " " + channel + " :You're not channel operator"

#define ERR_NOSUCHNICK(source, nickname)                "401 " + source + " " + nickname + " :No such nick/channel"
#define ERR_USERNOTINCHANNEL(source, nickname, channel) "441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"


/* Numeric Responses */

#define RPL_WELCOME(source)                             "001 " + source + " :Welcome " + source + " to the ft_irc network"
#define RPL_NAMREPLY(source, channel, users)            "353 " + source + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(source, channel)                 "366 " + source + " " + channel + " :End of /NAMES list."


/* Command Responses */

#define RPL_JOIN(source, channel)                       ":" + source + " JOIN :" + channel
#define RPL_PART(source, channel)                       ":" + source + " PART :" + channel
#define RPL_PING(source, token)                         ":" + source + " PONG :" + token
#define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
#define RPL_NOTICE(source, target, message)             ":" + source + " NOTICE " + target + " :" + message
#define RPL_QUIT(source, message)                       ":" + source + " QUIT :Quit: " + message
#define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK " + channel + " " + target + " :" + reason
#define RPL_MODE(source, channel, modes, args)          ":" + source + " MODE " + channel + " " + modes + " " + args


/* Log Response */

static inline void log(const std::string& message) 
{
    time_t      rawtime;
    struct tm   *timeinfo;
    char        buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    std::string str(buffer);

    (void)message;
    std::cout << "\033[0;34m[" << str << "]\033[0m ";
    std::cout << message << std::endl;
}

#endif

