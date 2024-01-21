#include "../../includes/Command.hpp"

void	Command::_user(std::vector<std::string> args, User *user)
{
	if (args.size() != 5 || args[2].compare("0") || args[3].compare("*") || args[4].empty())
		return (RPL_CMD(user, "USER", "USER <username> 0 * :<realname>\n"), void());

	if (user->getUsername().empty())
		_srv->logTime(user->getNickname() + " joined the server");

	user->setUsername(args[1]);
	user->setRealName(args[4]);
}
