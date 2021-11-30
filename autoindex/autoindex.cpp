#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

class response
{
private:
	std::string body;

public:
	response(/* args */);
	~response();
	int setAutoindexBody(std::string path, std::string host);
	std::string get_body() { return this->body; };
};

response::response(/* args */)
{
}

response::~response()
{
}

int response::setAutoindexBody(std::string path, std::string host)
{
	std::string buffer;
	struct dirent *dir_element; // element for directory entry
	DIR *dr;
	struct stat file_info;
	std::vector<std::string> listing;
	errno = 0;

	// for (unsigned int i = 0; i < dirFile.size(); ++i)
	// 	std::cout << dirFile[i] << "\n";
	body += "<head>\n";
	body += "<title >Index of /</title>\n";
	body += "</head>\n";
	body += "<body>\n";
	body += "<h1>";
	body += "Index of ";

	if (!strcmp(path.c_str(), "/"))
	{
		path = host;
		body += "/";
	}
	else
	{
		body += host;
		body += host;
	}
	dr = opendir(path.c_str());
	if (!dr)
	{
		perror("readdir() failed");
		return -1;
	}
	for (int len = path.size(); !strcmp(path.c_str(), "/") ; len--)
	{
		if (path[len] == '/')
		{
			path = &path[len];
			std::cout << path << std::endl;
			break;
		}
	}
	body += path;

	body += "</h1>\n";
	if (0 != errno)
		perror("readdir() failed");
	else
		std::cout << "No more entries." << std::endl;
	while ((dir_element = readdir(dr)))
	{
		listing.push_back(dir_element->d_name);
		lstat(dir_element->d_name, &file_info);
		if (S_ISREG(file_info.st_mode))
		{
			// body += "\"</h1>\n";
			std::string head = std::string("<a class=\"file\" href=");
			std::string path = std::string("\"127.0.0.1:80/");
			std::string file = std::string(dir_element->d_name);
			std::string label = std::string("\">");
			std::string text = std::string(dir_element->d_name);
			std::string end_label = std::string("</a>\n");
			body += head + path + file + label + text + end_label;
		}
		// file is a regular file
		else if (S_ISDIR(file_info.st_mode))
		{
			std::string head = std::string("<a class=\"dir\" href=");
			std::string path = std::string("\"127.0.0.1:80/");
			std::string file = std::string(dir_element->d_name);
			std::string label = std::string("\"/>");
			std::string text = std::string(dir_element->d_name);
			std::string end_label = std::string("</a>\n");
			body += head + path + file + label + text + end_label;
		}
	}
	body += "</body>\n";
	std::cout << body << std::endl;
	for (int i = 0; i < listing.size(); i++)
		std::cout << listing[i] << std::endl;
	return 0;
}

int main(int argc, char const *argv[])
{
	response res;
	const char *path = "/";
	res.setAutoindexBody(path, "/Users/yqodsi/Desktop/leet/autoindex");
	// std::cout << res.get_body() << std::endl;
	return 0;
}
