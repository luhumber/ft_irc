#include "../../includes/Command.hpp"

void    restrictionMode(Channel *channel, std::vector<std::string> args, char sign, size_t i)
{
    if (sign == '-') {
        if (channel->isMode(args[2][i]))
            channel->removeMode(args[2][i]);
    }
    else {
        if (!channel->isMode(args[2][i]))
            channel->addMode(args[2][i]);
    }
}

void    operatorMode(Channel *channel, User *targetuser, char sign, User *user)
{
    if (!channel->isOnChannel(targetuser->getfd()))
        return (ERR_NOSUCHNICK(user, targetuser->getNickname()), void());

    if (sign == '-')
    {
        if (channel->getGroup(targetuser) != VOICE)
            channel->setGroup(targetuser, VOICE);
    }
    else
    {
        if (channel->getGroup(targetuser) != VOICE)
            return (ERR_NOSUCHNICK(user, targetuser->getNickname()), void());

        channel->setGroup(targetuser, OPERATOR);
    }
}

void    passwordMode(Channel *channel, std::vector<std::string> args, char sign, size_t argument, User *user)
{
    if (argument < 3 || args.size() <= argument)
        return (ERR_NEEDMOREPARAMS(user, "MODE"), void());

    if (sign == '-' && !channel->getPassword().empty() && args[argument] == channel->getPassword())
    {
        if (channel->isMode('k')) {
            channel->removeMode('k');
            channel->setPassword("");
        }
    }
    else
    {
        if (!channel->isMode('k'))
            channel->addMode('k');
        channel->setPassword(args[argument]);
    }
    return ;
}

void    maxMode(Channel *channel, std::vector<std::string> args, char sign, size_t argument, User *user)
{
    if (sign == '-')
    {
        if (channel->isMode('l')) {
            channel->removeMode('l');
            channel->setMax(-1);
        }
    }
    else
    {
        if (argument < 3 || args.size() <= argument)
            return (ERR_NEEDMOREPARAMS(user, "MODE"), void());

        for (size_t i = 0; i < args[argument].size(); i++) {
            if (!isdigit(args[argument][i]))
                return (ERR_UMODEUNKNOWNFLAG(user), void());
        }

        ssize_t max = atoi(args[argument].c_str());
        if (max > 0 && max >= static_cast<int>(channel->getUsers().size()))
            channel->setMax(max);
        else 
            return (ERR_UMODEUNKNOWNFLAG(user), void());
        if (!channel->isMode('l'))
            channel->addMode('l');
    }
    return ;
}

void    Command::_mode(std::vector<std::string> args, User *user)
{ 
    if (args.size() < 2)
        return (ERR_NEEDMOREPARAMS(user, "MODE"), void());

    Channel *channel = _srv->getChannelByName(args[1]);
    if (channel == NULL)
        return (ERR_NOSUCHCHANNEL(user, args[1]), void());


    if (args.size() == 2)
        return (RPL_UMODEIS(user, channel->getModes()), void());

    if (channel->getGroup(user) == VOICE)
        return (ERR_CHANOPRIVSNEEDED(user, channel->getName()), void());
        
    std::string modes = args[2];
    if (modes.empty() || (modes[0] != '-' && modes[0] != '+'))
        return (ERR_UMODEUNKNOWNFLAG(user), void());

    size_t      argument = 0;
    char        sign = modes[0];
    User        *targetUser;
    if (args.size() > 3)
        argument = 3;
    
    for (size_t i = 1; i < modes.size(); ++i) {
        switch (modes[i]) {
            case '+':
                sign = '+';
                break ;
            case '-':
                sign = '-';
                break ;
            case 'i':
                restrictionMode(channel, args, sign, i);
                break ;
            case 't':
                restrictionMode(channel, args, sign, i);
                break ;
            case 'k':
                passwordMode(channel, args, sign, argument, user);
                break ;
            case 'o':
                if (channel->getGroup(user) == VOICE)
                    return (ERR_CHANOPRIVSNEEDED(user, channel->getName()), void());
                targetUser = _srv->getUserByNickname(args[argument]);
                if (targetUser == NULL)
                    return (ERR_NOSUCHNICK(user, argument));
                operatorMode(channel, targetUser, sign, user);
                argument++;
                break ;
            case 'l':
                maxMode(channel, args, sign, argument, user);
                argument++;
                break ;
            default:
                return (ERR_UMODEUNKNOWNFLAG(user), void());
        }
    }

    RPL_UMODEIS(user, channel->getModes());
}
