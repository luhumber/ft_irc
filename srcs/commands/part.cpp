#include "../../includes/Command.hpp"

void	Command::_part(std::vector<std::string> args, User *user)
{	
	if (args.size() < 2)
		return (ERR_NEEDMOREPARAMS(user, "PART"), void());

	std::vector<std::string> channels = this->split(args[1], ',');
	for (size_t i = 0; i < channels.size(); i++)
	{
		Channel *channel = _srv->getChannelByName(channels[i]);
		if (channel == NULL)
			return (ERR_NOSUCHCHANNEL(user, channels[i]), void());

		if (channel->getName()[0] != '#')
        	return (ERR_BADCHANMASK(user, args[1]), void());

		if (!channel->isOnChannel(user->getfd()))
			return (ERR_NOTONCHANNEL(user, channels[i]), void());

		channel->removeUser(user->getfd());

		std::map<int, User *> users = channel->getUsers();

		if (users.size() == 0 && channel->isMode('i'))
			channel->removeMode('i');

		if (channel->getGroup(user) == ADMIN && users.size() > 0)
		{
			User *newAdmin = NULL;
			for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); ++it)
			{
				if (channel->getGroup(it->second) == OPERATOR)
				{
					newAdmin = it->second;
					break ;
				} else if (newAdmin == NULL)
					newAdmin = it->second;
			}
			channel->setGroup(newAdmin, ADMIN);
		}

		RPL_CMD(user, "PART", channel->getName());
		std::string reason = formatReason(args, 2);
		channel->broadcast(user, "PART", reason);
		channel->RefreshUsers();
	}
}
