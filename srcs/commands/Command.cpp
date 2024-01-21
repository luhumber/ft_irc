# include "../includes/Command.hpp"

Command::Command(Server *_srv) : _srv(_srv)
{
	this->add("CAP",		&Command::_cap);
	this->add("PASS",		&Command::_pass);
	this->add("JOIN",		&Command::_join);
	this->add("PART",		&Command::_part);
	this->add("QUIT",		&Command::_quit);
	this->add("NICK",		&Command::_nick);
	this->add("USER",		&Command::_user);
	this->add("KICK",		&Command::_kick);
	this->add("MODE",		&Command::_mode);
	this->add("WHO",		&Command::_who);
	this->add("TOPIC",		&Command::_topic);
	this->add("INVITE",		&Command::_invite);
	this->add("PRIVMSG", 	&Command::_privmsg);
}

Command::~Command() {}

void	Command::add(std::string command, CommandFunction f)
{
	_commands.insert(std::pair<std::string, CommandFunction>(command, f));
}

void	Command::parse(std::string buffer, int userFd)
{
	std::vector<std::string> args;
	std::string				line;

	for (size_t i = 0; i < buffer.size(); i++)
	{
		if (buffer[i] == '\n')
		{
			line = buffer.substr(0, i);
			buffer = buffer.erase(0, i + 1);
			i = 0;
			for (size_t j = 0; j < line.size(); j++)
			{
				if (line[j] == ' ' || j == line.size() - 1)
				{
					args.push_back(line.substr(0, j));
					line = line.substr(j + 1);
					j = 0;
				}
			}
			if (args.size() > 0)
				this->execute(args[0], args, userFd);
			args.clear();
			line.clear();
		}
	}
}

bool	Command::isExecutable(User *user, std::string msg)
{
	std::string	commands[] = {"PASS", "NICK", "USER", "CAP", "QUIT"};
	if (user->getConnection() == false)
	{
		for (size_t i = 0; i < commands->size() + 1; i++)
			if (!commands[i].compare(msg))
				return (true);
		
		ERR_NOTREGISTERED(user);
		return (false);
	}
	return (true);
}

void	Command::execute(std::string command, std::vector<std::string> args, int userFd)
{
	std::map<std::string, CommandFunction>::iterator it = _commands.find(command);
	User *user = _srv->getUserByFd(userFd);

	if (user && it != _commands.end() && this->isExecutable(user, command))
		(this->*(it->second))(args, user);
}

// UTILS
std::vector<std::string>	Command::split(std::string str, char del)
{
	std::vector<std::string> tokens;
	std::string token;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == del)
		{
			tokens.push_back(token);
			token.clear();
		}
		else
			token += str[i];
	}
	tokens.push_back(token);
	return (tokens);
}

const std::string	Command::formatReason(std::vector<std::string> args, int idx)
{
	std::string reason = "";

	for (size_t i = idx; i < args.size(); i++)
        reason += args[i] + ' ';
	reason.erase(reason.size() - 1);
	return (reason);
}

void	toClient(int fd, const std::string &message)
{
	send(fd, message.c_str(), message.size(), 0);
}
