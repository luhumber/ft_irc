#include "../includes/Command.hpp"

void	Command::_who(std::vector<std::string> args, User *user)
{
	std::string		channelName;
	Channel			*channel;

	if (args.size() < 2)
		return (ERR_NEEDMOREPARAMS(user, "WHO"), void());

	channelName = args[1];
	if (channelName[0] != '#')
		channelName = user->getNickname();
	channel = _srv->getChannelByName(channelName);
	if (!channel)
		return (ERR_NOSUCHCHANNEL(user, channelName), void());

	std::map<int, User *> users = channel->getUsers();
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
		RPL_WHOREPLY(user, it->second, channel);

	RPL_ENDOFWHO(user, channel);
}