#include "../../includes/Command.hpp"

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream stream(s);
    std::string token;
    
    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

static std::string vecToStr(std::vector<std::string> args)
{
    std::string message;

    for (size_t i = 2; i < args.size(); i++)
        message += args[i] + ' ';
    message += '\n';
    return (message);
}

void    Command::_privmsg(std::vector<std::string> args, User *user)
{
    int userFd = user->getfd();

 
        
    if (args.size() == 2)
    {
        if (args[1][0] == ':')
            ERR_NORECIPIENT(user, "PRIVMSG");
        else
            ERR_NOTEXTTOSEND(user);
        return ;
    }

    if (args[2][0] != ':' || args.size() < 3)
        return (ERR_NEEDMOREPARAMS(user, "PRIVMSG"), void());

    std::vector<std::string>    target;
    target = split(args[1], ',');

	args[2].erase(0, 1);
    for (size_t i = 0; i < target.size(); i++)
    {
        if (target[i][0] == '#')
        {
            Channel *channel = _srv->getChannelByName(target[i]);
            if (channel == NULL)
                return (ERR_NOSUCHCHANNEL(user, target[i]), void());

            if (!channel->isOnChannel(userFd))
                return (ERR_NOSUCHNICK(user, target[i]), void());

            if (args.size() >= 3)
                channel->broadcast(user, "PRIVMSG", vecToStr(args));
            else
                return (ERR_NEEDMOREPARAMS(user, "PRIVMSG"), void());
        }
        else
        {
            User *targetUser = _srv->getUserByNickname(target[i]);
            if (targetUser == NULL)
                return (ERR_NOSUCHNICK(user, target[i]), void());

            if (targetUser->getfd() == userFd)
                return (ERR_NOSUCHNICK(user, target[i]), void());

            if (args.size() >= 3) {
                std::string message = user->getNickname();
                message += ' ' + vecToStr(args);
                RPL_CMD_TO_USER(targetUser, user, "PRIVMSG", message);
            }
            else
                return (ERR_NEEDMOREPARAMS(user, "PRIVMSG"), void());
        }
    }
}
