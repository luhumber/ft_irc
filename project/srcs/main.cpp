#include "Server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}
	try
	{
		int port = std::atoi(argv[1]);
		if (!port || port < 1024 || port > 65535)
			throw std::invalid_argument("Invalid port");
		Server ircserv(port, argv[2]);
		std::signal(SIGINT, ircserv.signalHandler);
		ircserv.run();
	}
	catch (std::invalid_argument &e)
	{
		std::cout << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
