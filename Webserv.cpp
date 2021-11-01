#include "Webserv.hpp"

int main()
{
	int sockfd;
	int new_socket;
	long valread;
	struct sockaddr_in address;
	std::string response = std::string("HTTP/1.1 200 OK\r\n") + std::string("Content-Type: text/html\r\n") + 
	std::string("Connection: close\r\n\r\n") + std::string("<html>\r\n") + std::string("<body>\r\n") + 
	std::string("<h1 style='background-color:powderblue;'>Hello, World!</h1>\r\n") + std::string("<body>\r\n") + std::string("<html>\r\n");
	int addrlen = sizeof(address);
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Cannot create socket");
		return 0;
	}

	memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed!");
		return 0;
	}
	if (listen(sockfd, 3) < 0)
	{
		perror("In listen");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf("\n+++++++ Waiting for new connection ++++++++\n\n");
		if ((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
		{
			perror("In accept");
			exit(EXIT_FAILURE);
		}

		char buffer[30000] = {0};
		valread = read(new_socket, buffer, 30000);
		// printf("%s\n", buffer);
		std::cout << response << std::endl;
		write(new_socket, response.c_str(), response.length());
		close(new_socket);
	}
	return 0;
}
