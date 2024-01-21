# include "../includes/User.hpp"

User::User() {}

User::User(pollfd newPoll) : _poll(newPoll)
{
    this->_nickname = "";
    this->_username = "";
    this->_realName = "";
    this->_isConnected = false;
}

User::User(User const &cpy)
{
    *this = cpy;
}

User &User::operator=(User const &cpy)
{
    this->_poll = cpy._poll;
    this->_nickname = cpy._nickname;
    this->_username = cpy._username;
    return (*this);
}

User::~User(void) {}

const std::string   &User::getNickname(void) const { return (this->_nickname); }
const std::string   &User::getUsername(void) const { return (this->_username); }
const std::string   &User::getRealName(void) const { return (this->_realName); }
const pollfd        &User::getPoll(void) const { return (this->_poll); }
const int           &User::getfd(void) const { return (this->_poll.fd); }
const bool          &User::getConnection(void) const { return (this->_isConnected); }

void    User::setNickname(const std::string &nickname) { this->_nickname = nickname; }
void    User::setUsername(const std::string &username) { this->_username = username; }
void    User::setRealName(const std::string &realName) { this->_realName = realName; }
void    User::setConnection(const bool &connection) { this->_isConnected = connection; }
