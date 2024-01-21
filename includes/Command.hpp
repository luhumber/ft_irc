
#ifndef Command_HPP
# define Command_HPP

# include "Server.hpp"
# include "utils/Numerics.hpp"

class Server;
class User;

class Command
{
	private :
		Server *_srv;

		typedef void (Command::*CommandFunction)(std::vector<std::string>, User *);
		std::map<std::string, CommandFunction> _commands;

	public :
		Command(Server *_srv);
		virtual ~Command();

		void	add(std::string command, CommandFunction f);
		void	parse(std::string buffer, int userFd);
		bool	isExecutable(User *user, std::string msg);
		void	execute(std::string command, std::vector<std::string> args, int userFd);

		std::vector<std::string>	split(std::string str, char del);
		const std::string			formatReason(std::vector<std::string> args, int idx);

		// commands
		void	_cap(std::vector<std::string> args, User *user);
		void	_pass(std::vector<std::string> args, User *user);
		void	_join(std::vector<std::string> args, User *user);
		void	_part(std::vector<std::string> args, User *user);
		void	_quit(std::vector<std::string> args, User *user);
		void	_nick(std::vector<std::string> args, User *user);
		void	_kick(std::vector<std::string> args, User *user);
		void	_mode(std::vector<std::string> args, User *user);
		void	_who(std::vector<std::string> args, User *user);
		void	_invite(std::vector<std::string> args, User *user);
		void	_topic(std::vector<std::string> args, User *user);
		void	_user(std::vector<std::string> args, User *user);
		void	_privmsg(std::vector<std::string> args, User *user);
};

void	toClient(int fd, const std::string &message);

#endif