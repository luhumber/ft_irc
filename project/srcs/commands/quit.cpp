#include "../includes/Command.hpp"

void	Command::_quit(std::vector<std::string> args, User *user)
{	
	(void)args;
	_srv->onUserDropped(user->getfd());
}
