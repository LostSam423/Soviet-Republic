#include "readfile.hpp"

std::string getFile(const char *filePath)
{
	std:: string lines;
	try
	{
		std::ifstream fileStream(filePath, std::ios::in);

		if(!fileStream.is_open()){
			std::cerr<<"The file "<<filePath<<" is not open/does not exist"<<std::endl;
			return "";
		}

		std::string line;
		while(!fileStream.eof()){
			std:: getline(fileStream, line);
			lines.append(line + "\n");
		}

		fileStream.close();	
	}
	catch (std::ifstream::failure e){
		std::cout<<"ERROR::SHADER::FILE NOT READ::"<<filePath<<std::endl;
	}
	return lines;
}

