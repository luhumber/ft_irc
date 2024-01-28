#include "../includes/Command.hpp"

void Command::_pass(std::vector<std::string> args, User *user)
{
	if (args.size() != 2)
		return (ERR_NEEDMOREPARAMS(user, "PASS"), void());

	if (user->getConnection() == true)
		return (ERR_ALREADYREGISTERED(user), void());

	if (_srv->getPassword().compare(args[1]))
		return (ERR_PASSWDMISMATCH(user), void());

	user->setConnection(true);
}
