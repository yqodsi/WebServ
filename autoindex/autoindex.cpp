#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
class response
{
private:
	std::string body;

public:
	response(/* args */);
	~response();
	void setAutoindexBody(const char *path);
	std::string get_body() { return this->body; };
};

response::response(/* args */)
{
}

response::~response()
{
}

void response::setAutoindexBody(const char *path)
{
	std::string buffer;
	struct dirent *dir_element; // element for directory entry
	DIR *dr = opendir(path);
	struct stat file_info;
	std::vector<std::string> dirFile;

	char *command = (char *)"/bin/ls > /tmp/command_output.txt";
	system(command);
	std::ifstream command_output;
	command_output.open("/tmp/command_output.txt");
	if (command_output.is_open())
	{
		while (command_output)
		{
			getline(command_output, buffer, ' ');
			dirFile.push_back(buffer);
			buffer.clear();
		}
	}
	command_output.close();
	// for (unsigned int i = 0; i < dirFile.size(); ++i)
	// 	std::cout << dirFile[i] << "\n";
	body += "<head>\n";
	body += "<title >Index of /</title>\n";
	body += "</head>\n";
	body += "<body>\n";

	dir_element = readdir(dr);
	body += "<h1>";
	body += "Index of ";
	if (!strcmp(dir_element->d_name, "."))
		body += "/";

	else
		body += dir_element->d_name;
	body += "</h1>\n";
	while ((dir_element = readdir(dr)))
	{
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
	// std::cout << body << std::endl;
}

int main(int argc, char const *argv[])
{
	response res;
	const char *path = "/Users/yqodsi/Desktop/leet/autoindex/";
	res.setAutoindexBody(path);
	// std::cout << res.get_body() << std::endl;
	return 0;
}
