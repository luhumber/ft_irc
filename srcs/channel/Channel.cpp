# include "../includes/Channel.hpp"

Channel::Channel() {}

Channel::Channel(const std::string name) : _name(name)
{
	this->_max = -1;
	this->_password = "";
	this->_symbolsReply = SECRET;
}

Channel::~Channel(void)
{
	this->_users.clear();
	this->_groups.clear();
	this->_invited.clear();
	this->_modes.clear();
}

const std::string   &Channel::getName(void) const { return (this->_name); }
const std::string	&Channel::getPassword(void) const { return (this->_password); }
const std::string	&Channel::getTopic(void) const { return (this->_topic); }
const ssize_t		&Channel::getMax(void) const { return (this->_max); }
const std::string	Channel::getSymbolReply(void) const { return (this->_symbolsReply); }
char				Channel::getGroup(User *user) const { return (this->_groups.at(user)); }

void                Channel::setName(const std::string &name) { this->_name = name; }
void				Channel::setPassword(const std::string &password) { this->_password = password; }
void				Channel::setTopic(const std::string &topic) { this->_topic = topic; }
void				Channel::setMax(const ssize_t &max) { this->_max = max; }
void				Channel::setSymbolReply(const std::string &symbolsReply) { this->_symbolsReply = symbolsReply; } 
void				Channel::setGroup(User *user, char c) { this->_groups[user] = c; }

std::map<int, User *>	Channel::getUsers(void) { return (this->_users); }

void    Channel::addUser(User  *user)
{
	if (user)
		_users.insert(std::pair<int, User *>(user->getfd(), user));
}

void    Channel::removeUser(int userFd)
{
	for(std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (it->first == userFd)
		{
			_users.erase(it);
			return ;
		}
	}
}

bool    Channel::isOnChannel(int userFd) {

	for(std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); ++it)
		if (it->first == userFd)
			return (true);
	return (false);
}

bool	Channel::isInvited(int userFd)
{
	for (size_t i = 0; i < _invited.size(); i++)
	{
		std::cout << userFd << _invited[i] << std::endl;
		if (_invited[i] == userFd)
			return (true);
	}
	return (false);
}

void	Channel::addInvited(int userFd)
{
	_invited.push_back(userFd);
}

void	Channel::removeInvited(int userFd)
{
	for (size_t i = 0; i < _invited.size(); i++)
	{
		if (_invited[i] == userFd)
		{
			_invited.erase(_invited.begin() + i);
			return ;
		}
	}
}

void	Channel::RefreshUsers(void)
{
	std::map<int, User *> users = this->getUsers();

	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		for (std::map<int, User *>::iterator it2 = users.begin(); it2 != users.end(); it2++)
			RPL_NAMREPLY(it->second, this, it2->second);
		RPL_ENDOFNAMES(it->second, this);
	}
}

void   Channel::broadcast(User *user, const std::string &command, const std::string &message)
{
	for(std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (it->first != user->getfd())
			RPL_CMD_CHANNEL(it->second, user, command, this->getName(), message);
	}
}
