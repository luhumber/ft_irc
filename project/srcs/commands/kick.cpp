#include "../../includes/Command.hpp"

void    Command::_kick(std::vector<std::string> args, User *user)
{
    if (args.size() < 3)
        return (ERR_NEEDMOREPARAMS(user, "KICK"), void());

    if (args[1][0] != '#')
        return (ERR_BADCHANMASK(user, args[1]), void());

    Channel *channel = _srv->getChannelByName(args[1]);
    if (channel == NULL)
        return (ERR_NOSUCHCHANNEL(user, args[1]), void());

    User *currentUser = _srv->getUserByNickname(args[2]);
    if (currentUser == NULL)
        return (ERR_NOSUCHNICK(user, args[2]), void());

    if (channel->getGroup(user) == VOICE)
        return (ERR_CHANOPRIVSNEEDED(user, channel->getName()), void());

    if (!channel->isOnChannel(currentUser->getfd()))
        return (ERR_USERNOTINCHANNEL(user, currentUser->getNickname(), channel->getName()), void());

    if (!channel->isOnChannel(user->getfd()))
        return (ERR_NOTONCHANNEL(user, channel->getName()), void());

    std::map<int, User *> users = channel->getUsers();
    if (args.size() >= 4)
    {
        std::string reason = this->formatReason(args, 3);
        for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); ++it)
            KICK_WITH_REASON(it->second, channel->getName(), currentUser->getNickname(), reason);
    }
    else
    {
        for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); ++it)
            KICK_WITHOUT_REASON(it->second, channel->getName(), currentUser->getNickname());
    }

    channel->removeUser(currentUser->getfd());
    channel->RefreshUsers();
    _srv->logTime(currentUser->getNickname() + " has been kicked from channel " + channel->getName());
}
