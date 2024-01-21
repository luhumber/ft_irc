#include "../includes/Server.hpp"

bool _executing = true;

Server::Server() {}

Server::Server(int port, std::string password)
{
	this->_port = port;
	this->_password = password;
	this->_host = "localhost";
	this->_socket = this->initializeSocket();
}

Server::~Server()
{
	std::vector<Channel *>::iterator it = this->_channels.begin();
	while (it != this->_channels.end())
	{
		delete (*it);
		it++;
	}
	this->_channels.clear();
	std::map<int, User *>::iterator it2 = this->_users.begin();
	while (it2 != this->_users.end())
	{
		delete (it2->second);
		close(it2->first);
		it2++;
	}
	this->_users.clear();
}

const int						&Server::getPort() const { return (this->_port); }
const std::string				&Server::getPassword() const { return (this->_password); }

void	Server::signalHandler(int signal)
{
	if (signal == SIGINT)
		_executing = false;
}

int	Server::initializeSocket()
{
	int optVal = 1;
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
		throw std::runtime_error("Error : socket() failed!");

	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)))
		throw std::runtime_error("Error : setsockopt() failed!");

	if (fcntl(sock_fd, F_SETFL, O_NONBLOCK))
		throw std::runtime_error("Error : fcntl() failed!");

	struct sockaddr_in  service;    
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;
	service.sin_port = htons(this->_port);

	if (bind(sock_fd, (sockaddr *)&service, sizeof(service)) < 0)
		throw std::runtime_error("Error : bind() failed!");

	if (listen(sock_fd, MAX_CONNECTIONS) < 0)
		throw std::runtime_error("Error : listen() failed!");
	return (sock_fd);
}

void	Server::logTime(const std::string &message)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	if (ltm->tm_hour < 10)
		std::cout << "[0" << ltm->tm_hour << ":";
	else
		std::cout << "[" << ltm->tm_hour << ":";
	if (ltm->tm_min < 10)
		std::cout << "0" << ltm->tm_min << "] ";
	else
		std::cout << ltm->tm_min << "]";
	std::cout << " -> " << message << std::endl;
}

void	Server::run()
{
	pollfd srv;
	srv.fd = this->_socket;
	srv.events = POLLIN;
	_pollsets.push_back(srv);

	Command command(this);
	logTime("Server is running on port " + to_string(this->_port));
	while (_executing)
	{
		if (poll(_pollsets.data(), _pollsets.size(), -1) < 0)
			break;

		for (std::vector<pollfd>::iterator it = _pollsets.begin(); it != _pollsets.end(); it++)
		{
			if (it->revents == 0)
				continue;
			if ((it->revents & POLLIN) == POLLIN && it->fd == this->_socket)
			{
				this->onUserConnecting();
				break;
			}
			this->onUserMessage(command, it->fd);
		}
	}
	this->_pollsets.clear();
	close(this->_socket);
}
