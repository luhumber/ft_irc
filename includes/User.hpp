#ifndef USER_HPP
#define USER_HPP

# include "Server.hpp"

class User
{
    private :
        std::string _nickname;
        std::string _username;
        std::string _realName;
        bool        _isConnected;
        pollfd      _poll;

    public :
        User();
		User &operator=(User const &cpy);
        User(pollfd newPoll);
        User(User const &cpy);
        ~User();

        const std::string   &getNickname(void) const;
        const std::string   &getUsername(void) const;
        const std::string   &getRealName(void) const;
        const pollfd        &getPoll(void) const;
        const int           &getfd(void) const;
        const bool          &getConnection(void) const;

        void    setNickname(const std::string &nickname);
        void    setUsername(const std::string &username);
        void    setRealName(const std::string &realName);
        void    setConnection(const bool &connection);
};

#endif
