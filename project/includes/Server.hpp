#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cstring>
# include <cstdlib>
# include <csignal>
# include <sstream>
# include <string>

# include <csignal>
# include <sys/socket.h>
# include <sys/poll.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <poll.h>
# include <fcntl.h>
# include <unistd.h>

# include <vector>
# include <map>
# include <stdexcept>
# include <cerrno>

# include "User.hpp"
# include "Channel.hpp"
# include "Command.hpp"
# include "utils/Numerics.hpp"

class User;
class Channel;
class Command;

# define to_string(value) static_cast<const std::ostringstream&>((\
std::ostringstream() << std::dec << value)).str()

# define MAX_CONNECTIONS 999

class 	Server
{
	private :
		std::string				_password;
		std::string				_host;
		int						_port;

		int						_socket;

		std::vector<pollfd>     _pollsets;
		std::map<int, User *>	_users;
		std::vector<Channel *> 	_channels;

		Server(Server const &cpy);
		Server &operator=(Server const &cpy);

	public :
		Server();
		Server(int port, std::string password);
		~Server();

		const int						&getPort()										const;
		const std::string				&getPassword()									const;
		const std::map<int, User *> 	&getUsers()										const;
		User							*getUserByFd(int fd)							const;
		User							*getUserByNickname(const std::string &nickname)	const;
		const std::vector<Channel *> 	&getChannels()									const;
		Channel							*getChannelByName(const std::string &name)		const;

		static void			signalHandler(int signal);
		int					initializeSocket();
		void				run();
		void				logTime(const std::string &message);

		void				onUserConnecting();
		void				onUserMessage(Command &command, int fd);
		void				onUserDropped(int userFd);

		Channel				*onChannelCreating(const std::string &name, \
							const std::string &nameHost);
};
#endif