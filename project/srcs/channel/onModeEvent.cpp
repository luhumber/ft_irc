# include "../includes/Channel.hpp"

std::string	Channel::getModes(void)
{
	std::string	mode;

	mode = "+";
	for (size_t idx = 0; idx < _modes.size(); idx++)
		mode += this->_modes[idx];
	return (mode);
}

void	Channel::addMode(char c)
{ 
	_modes.push_back(c);
}

void	Channel::removeMode(char c)
{
	_modes.erase(std::find(_modes.begin(), _modes.end(), c));
}

bool	Channel::isMode(char c)
{
	for(std::vector<char>::iterator it = _modes.begin(); it != _modes.end(); it++)
        if (*it == c)
			return (true);
	return (false);
}