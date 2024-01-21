#include "../../includes/Command.hpp"

bool    channelConnection(Channel *channel, User *user)
{
    if (channel->isOnChannel(user->getfd()))
        send(user->getfd(), "You are already on this channel\n", 33, 0);
    else
    {
        if (static_cast<ssize_t>(channel->getUsers().size()) == channel->getMax())
            return (ERR_CHANNELISFULL(user, channel->getName()), false);

        channel->addUser(user);

        std::map<int, User *> users = channel->getUsers(); 
        channel->setGroup(user, users.size() == 1 ? ADMIN : VOICE);
    
        RPL_CMD(user, "JOIN", channel->getName());
        if (!channel->getTopic().empty())
            RPL_TOPIC(user, channel);
        channel->RefreshUsers();
        return (true);
    }
    return (false);
}

void    Command::_join(std::vector<std::string> args, User *user)
{
    int onCreated = 1;

    if (args.size() < 2)
        return (ERR_NEEDMOREPARAMS(user, "JOIN"), void());

    std::vector<std::string> channels = this->split(args[1], ',');
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i][0] != '#')
            return (ERR_BADCHANMASK(user, args[1]), void());
    
        Channel *channel = _srv->getChannelByName(channels[i]);
        if (channel == NULL)
        {
            onCreated = 0;
            channel = _srv->onChannelCreating(channels[i], user->getNickname());
            if (args.size() == 3)
                channel->setPassword(args[2]);
        }
        else if (!channel->isInvited(user->getfd()))
        {
            if (!channel->getPassword().empty() && args[2] != channel->getPassword())
                return (ERR_BADCHANNELKEY(user, channel->getName()), void());

            if (channel->isMode('i'))
                return (ERR_INVITEONLYCHAN(user, channel->getName()), void());

            if (channel->getUsers().size() == (size_t)channel->getMax())
                return (ERR_CHANNELISFULL(user, channel->getName()), void());
        }
        else
            channel->removeInvited(user->getfd());

        if (channelConnection(channel, user) && onCreated)
            _srv->logTime(user->getNickname() + " joined " + channel->getName() + " channel");
    }
}
