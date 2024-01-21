#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <map>
# include <algorithm>

# include "User.hpp"

enum symbolsReply
{
    PUBLIC = '=',
    PRIVATE = '*',
    SECRET = '@'
};

enum groups
{
    ADMIN = '@',
    OPERATOR = '@',
    VOICE = '+'
};

class User;

class   Channel
{
    private:
        std::string                 _name;
        std::string                 _password;
        std::string                 _topic;
        std::vector<char>           _modes;
        std::map<int, User *>       _users;
        std::map<User *, char>      _groups;
        std::vector<int>            _invited;
        std::string                 _symbolsReply;
        ssize_t                     _max;

    public:
        Channel(void);
        Channel(const std::string name);
        ~Channel(void);

        const std::string         &getName(void)            const;
        const std::string         &getPassword(void)        const;
        const std::string         &getTopic(void)           const;
        const ssize_t             &getMax(void)             const;
        const std::string         getSymbolReply(void)      const;
        char                      getGroup(User *user)      const;

        void                      setName(const std::string &name);
        void                      setPassword(const std::string &password);
        void                      setTopic(const std::string &topic);
        void                      setMax(const ssize_t &max);
        void                      setSymbolReply(const std::string &symbolsReply);
        void                      setGroup(User *user, char c);

        std::string               getModes(void);
        std::map<int, User *>     getUsers(void);
        void                      addUser(User *user);
        void                      removeUser(int userFd);
        bool                      isOnChannel(int userFd);

        void                      addMode(char c);
        void                      removeMode(char c);
        bool                      isMode(char c);

        bool                      isInvited(int userFd);
        void                      addInvited(int userFd);
        void                      removeInvited(int userFd);

        void                      RefreshUsers(void);
        void                      broadcast(User *user, const std::string &command, const std::string &message);
};

#endif