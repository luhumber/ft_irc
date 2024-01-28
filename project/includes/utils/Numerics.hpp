#ifndef NUMERICS_HPP
# define NUMERICS_HPP

# include <vector>
# include <iostream>

# define SEND toClient
# define RN + "\r\n"

// ERROR
# define ERR_ALREADYREGISTERED(user) \
SEND (user->getfd(), ":localhost 462 " + user->getNickname() + " :Unauthorized command (already registered)" RN)

# define ERR_NOTREGISTERED(user) \
SEND (user->getfd(), ":localhost 462 " + user->getNickname() + " :You have not registered" RN)

# define ERR_NONICKNAMEGIVEN(user) \
SEND (user->getfd(), std::string(":localhost 431 :No nickname given") RN)

# define ERR_NICKNAMEINUSE(user, nickname) \
SEND (user->getfd(), ":localhost 433 " + nickname + " :Nickname is already in use" RN)

# define ERR_ERRONEUSNICKNAME(user, nickname) \
SEND (user->getfd(), ":localhost 432 " + nickname + " :Erroneous nickname" RN)

# define ERR_NEEDMOREPARAMS(user, command) \
SEND (user->getfd(), ":localhost 461 " + user->getNickname() + " " + command + " :Not enough parameters" RN)

# define ERR_PASSWDMISMATCH(user)	\
SEND (user->getfd(), ":localhost 464 " + user->getNickname() + " :Password incorrect" RN)

# define ERR_CHANNELISFULL(user, channel) \
SEND (user->getfd(), ":localhost 471 " + channel + " :Cannot join channel (+l)" RN)

# define ERR_INVITEONLYCHAN(user, channel) \
SEND (user->getfd(), ":localhost 473 " + channel + " :Cannot join channel (+i)" RN)

# define ERR_BADCHANNELKEY(user, channel) \
SEND (user->getfd(), ":localhost 475 " + channel + " :Cannot join channel (+k)" RN)

# define ERR_BADCHANMASK(user, channel) \
SEND (user->getfd(), channel + " :BAD Channel Mask" RN)

# define ERR_NORECIPIENT(user, command) \
SEND(user->getfd(), (std::string(":localhost 411 :No recipient given (") + command + ")" RN).c_str())

# define ERR_NOTEXTTOSEND(user) \
SEND (user->getfd(), (std::string(":localhost 412 :No text to send") RN).c_str())

# define ERR_NOSUCHNICK(user, nickname) \
SEND (user->getfd(), ":localhost 401 " + user->getNickname() + " :No such nick/channel" RN)

# define ERR_NOSUCHCHANNEL(user, channel) \
SEND (user->getfd(), ":localhost 403 " + channel + " :No such channel" RN)

# define ERR_NOTONCHANNEL(user, channel) \
SEND (user->getfd(), ":localhost 442 " + channel + " :You're not on that channel" RN)

# define ERR_USERNOTINCHANNEL(user, nickname, channel) \
SEND (user->getfd(), ":localhost 441 " + nickname + " " + channel + " :They aren't on that channel" RN)

# define ERR_USERONCHANNEL(user, nick, channel) \
SEND (user->getfd(), ":localhost 482 " + nick + " " + channel + " :is already on channel" RN)

# define ERR_CHANOPRIVSNEEDED(user, channel) \
SEND (user->getfd(), ":localhost 482 " + channel + " :You're not channel operator" RN)

# define ERR_CANTKILLSERVER(user) \

# define ERR_UMODEUNKNOWNFLAG(user) \
SEND (user->getfd(), ":localhost 501 Unknown MODE flag\r\n")



// REPLY CMD
# define RPL_CMD(user, cmd, msg) \
SEND (user->getfd(), ":" + user->getNickname() + "!" + user->getUsername() + "@localhost " + cmd + " " + msg RN)

# define RPL_CMD_CHANNEL(recvuser, user, cmd, namechnl, msg) \
SEND (recvuser->getfd(), ":" + user->getNickname() + "!" + user->getUsername() + "@localhost " + cmd + " " + namechnl + " " + msg RN)

# define RPL_CMD_TO_USER(recvuser, user, cmd, msg) \
SEND (recvuser->getfd(), ":" + user->getNickname() + "!" + user->getUsername() + "@localhost " + cmd + " " + ":" + msg RN)


// KICK
# define KICK_WITH_REASON(user, channel, nickname, reason) \
SEND (user->getfd(), ":" + user->getNickname() + "!" + user->getUsername() + "@localhost KICK " + channel + " " + nickname + " :" + reason + RN)

# define KICK_WITHOUT_REASON(user, channel, nickname) \
SEND (user->getfd(), ":" + user->getNickname() + "!" + user->getUsername() + "@localhost KICK " + channel + " " + nickname + RN)

// NAME USER
# define RPL_NAMREPLY(user, channel, otherUsers) \
SEND (user->getfd(), ":localhost 353 " + user->getNickname() + " " + channel->getSymbolReply() + " " + channel->getName() + " :" + channel->getGroup(otherUsers) + otherUsers->getNickname() + RN)

# define RPL_ENDOFNAMES(user, channel) \
SEND (user->getfd(), ":localhost 366 " + user->getNickname() + " " + channel->getName() + " :End of NAMES list" RN)

// WHO
# define RPL_WHOREPLY(user, users, channel) \
SEND (user->getfd(), ":localhost 352 " + user->getNickname() + " " + channel->getName() + " " + users->getUsername() + " localhost localhost " + users->getNickname() + " H :0 " + users->getRealName() RN)

#define RPL_ENDOFWHO(user, channel) \
SEND (user->getfd(), ":localhost 315 " + user->getNickname() + " " + channel->getName() + " :End of WHO list" RN)

// INVITE
# define INVITE_MSG(user, invitedUser, channel) \
SEND (invitedUser->getfd(), "You have been invited by " + user->getNickname() + " to join " + channel->getName() + RN)

# define RPL_INVITING(user, channel) \
SEND (user->getfd(), ":localhost 341 " + user->getNickname() + " " + channel->getName() + RN)

// TOPIC
# define RPL_TOPIC(user, channel) \
SEND (user->getfd(), (":localhost 332 " + user->getNickname() + " " + channel->getName() + " :" + channel->getTopic() + RN))

# define RPL_NOTOPIC(user, channel) \
SEND (user->getfd(), (":localhost 331 " + user->getNickname() + " " + channel->getName() + " :No topic is set" RN))

// LIST
# define RPL_UMODEIS(user, modes) \
SEND (user->getfd(), ":localhost 221 " + modes RN)

#endif