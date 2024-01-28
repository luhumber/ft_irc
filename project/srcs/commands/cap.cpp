#include "../includes/Command.hpp"

void	Command::_cap(std::vector<std::string> args, User *user)
{
	(void)args;

	if (!user->getNickname().empty())
		return (ERR_ALREADYREGISTERED(user), void());

	RPL_CMD(user, "CAP", "Welcome to IRC, to login use: \nPASS <password>\nNICK <nickname>\nUSER <name> 0 * :realname\n");
}