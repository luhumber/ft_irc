#include "../includes/Server.hpp"

const std::vector<Channel *> 	&Server::getChannels() const { return (this->_channels); }

Channel	*Server::getChannelByName(const std::string &name) const
{
	for (std::vector<Channel *>::const_iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
		if ((*it)->getName() == name)
			return (*it);
	return (NULL);
}

Channel	*Server::onChannelCreating(const std::string &name, const std::string &nameHost)
{
	Channel *channel = new Channel(name);

	_channels.push_back(channel);
	logTime(nameHost + " created channel " + channel->getName());
	return (channel);
}
