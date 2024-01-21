#include "../includes/Server.hpp"

const std::map<int, User *> 	&Server::getUsers() const { return (this->_users); }

User	*Server::getUserByFd(int fd) const
{
	std::map<int, User *>::const_iterator it = this->_users.find(fd);
	if (it == this->_users.end())
		return (NULL);
	return (it->second);
}

User	*Server::getUserByNickname(const std::string &nickname) const
{
	for (std::map<int, User *>::const_iterator it = this->_users.begin(); it != this->_users.end(); it++)
		if (it->second->getNickname() == nickname)
			return (it->second);
	return (NULL);
}

void	Server::onUserMessage(Command &command, int fd)
{
	char buffer[1024];

	ssize_t bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0)
		return;
	buffer[bytes] = '\0';
	command.parse(buffer, fd);
}

void	Server::onUserConnecting()
{
	sockaddr_in addr = {};
	socklen_t   size = sizeof(addr);

	int fd = accept(this->_socket, (sockaddr *)&addr, &size);
	if (fd < 0)
		return ;

	pollfd  srv;
	srv.fd = fd;
	srv.events = POLLIN;
	_pollsets.push_back(srv);

	char hostname[NI_MAXHOST];
	int res = getnameinfo((struct sockaddr *) &addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
	if (res != 0)
		return (std::cout << "Error : new connection failed!" << std::endl, void());

	User *user = new User(srv);
	_users.insert(std::pair<int, User *>(fd, user));
}

void	Server::onUserDropped(int	userFd)
{
	std::vector<Channel *> channels = this->getChannels();
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i]->isOnChannel(userFd))
		{
			channels[i]->removeUser(userFd);
			channels[i]->RefreshUsers();
		}
	}
	logTime(this->getUserByFd(userFd)->getNickname() + " has disconnected");
	delete (this->_users[userFd]);
	this->_users.erase(userFd);
	close(userFd);
}
