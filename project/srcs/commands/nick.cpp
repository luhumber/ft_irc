#include "../includes/Command.hpp"

void	Command::_nick(std::vector<std::string> args, User *user)
{
	if (args.size() < 2)
		return (ERR_NONICKNAMEGIVEN(user), void());

	if (args.size() != 2)
		return (ERR_NEEDMOREPARAMS(user, "NICK"), void());

	std::string forbiddenChars = "# :[]\\`_^{|}";
	if (args[1].find_first_of(forbiddenChars) != std::string::npos)
		return (ERR_ERRONEUSNICKNAME(user, args[1]), void());
	
	std::map<int, User *> users = _srv->getUsers();
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if (it->second->getfd() != user->getfd() && it->second->getNickname() == args[1])
			return (ERR_NICKNAMEINUSE(user, args[1]), void());
	}

	RPL_CMD(user, "NICK", args[1]);
	user->setNickname(args[1]);
}
