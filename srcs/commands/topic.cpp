#include "../../includes/Command.hpp"

static std::string vecToStr(std::vector<std::string> args)
{
    std::string topic;

    if (!args.empty() && args[2][0] == ':')
        topic += args[2].substr(2) + ' ';
    else
        topic += args[2] + ' ';

    for (size_t i = 3; i < args.size(); i++)
        topic += args[i] + ' ';
    return (topic);
}

void Command::_topic(std::vector<std::string> args, User *user)
{
    int userFd = user->getfd();

    if (args.size() < 2)
        return (ERR_NEEDMOREPARAMS(user, "TOPIC"), void());

    Channel *channel = _srv->getChannelByName(args[1]);
    if (channel == NULL)
        return (ERR_NOSUCHCHANNEL(user, args[1]), void());

    if (!channel->isOnChannel(userFd))
        return (ERR_NOTONCHANNEL(user, args[1]), void());

    if (args.size() == 2)
    {
        if (channel->getTopic().empty())
            return (RPL_NOTOPIC(user, channel), void());
        std::string topic = channel->getTopic() + "\n";
        RPL_TOPIC(user, channel);
        return ;
    }
    else if (args.size() >= 3)
    {
        if (channel->isMode('t') && channel->getGroup(user) == VOICE)
            return (ERR_CHANOPRIVSNEEDED(user, args[1]), void());
        
        if (args[2][1] != ':')
            return (ERR_NEEDMOREPARAMS(user, "TOPIC"), void());

        if (args[2] == ":" && args.size() == 3)
            channel->setTopic("");
        else if (args.size() >= 3 && args[2][0] == ':')
            channel->setTopic(vecToStr(args));
        else
            return (ERR_NEEDMOREPARAMS(user, "TOPIC"), void());

        RPL_TOPIC(user, channel);
    }
}
