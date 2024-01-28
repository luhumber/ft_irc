#include "../../includes/Command.hpp"

void    Command::_invite(std::vector<std::string> args, User *user)
{
    if (args.size() != 3)
        return (ERR_NEEDMOREPARAMS(user, "INVITE"), void());

    User *invitedUser = _srv->getUserByNickname(args[1]);
    if (invitedUser == NULL)
        return (ERR_NOSUCHNICK(user, args[1]), void());

    Channel *channel = _srv->getChannelByName(args[2]);
    if (channel == NULL)
        return (ERR_NOSUCHCHANNEL(user, args[2]), void());

    if (!channel->isOnChannel(user->getfd()))
        return (ERR_USERNOTINCHANNEL(user, user->getNickname(), channel->getName()), void());

    if (channel->isMode('i') && channel->getGroup(user) == VOICE)
        return (ERR_CHANOPRIVSNEEDED(user, channel->getName()), void());

    if (channel->isOnChannel(invitedUser->getfd()))
        return (ERR_USERONCHANNEL(user, invitedUser->getNickname(), channel->getName()), void());

    if (static_cast<ssize_t>(channel->getUsers().size()) == channel->getMax())
        return (ERR_CHANNELISFULL(user, channel->getName()), void());

    channel->addInvited(invitedUser->getfd());
    INVITE_MSG(user, invitedUser, channel);
    RPL_INVITING(user, channel);
    _srv->logTime(user->getNickname() + " invited " + \
    invitedUser->getNickname() + " to " + channel->getName());
}
