#include <iostream>
#include <fstream>
#include <string>

std::string	replaceAll(const std::string &content, const std::string &s1, const std::string &s2)
{
	if (s1.empty())
		return content;
	
	std::string result;
	size_t pos = 0;
	size_t found;
	
	while ((found = content.find(s1, pos)) != std::string::npos)
	{

		result.append(content, pos, found - pos);
		result.append(s2);
		pos = found + s1.length();
	}
	result.append(content, pos);
	
	return result;
}

int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Error: Invalid number of arguments" << std::endl;
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return 1;
	}
	
	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	if (s1.empty())
	{
		std::cerr << "Error: String to replace (s1) cannot be empty" << std::endl;
		return 1;
	}
	
	std::ifstream inputFile(filename.c_str());
	if (!inputFile.is_open())
	{
		std::cerr << "Error: Cannot open file '" << filename << "'" << std::endl;
		return 1;
	}

	std::string content;
	std::string line;
	bool firstLine = true;
	
	while (std::getline(inputFile, line))
	{
		if (!firstLine)
			content += "\n";
		content += line;
		firstLine = false;
	}
	inputFile.close();

	std::string replacedContent = replaceAll(content, s1, s2);

	std::string outputFilename = filename + ".replace";

	std::ofstream outputFile(outputFilename.c_str());
	if (!outputFile.is_open())
	{
		std::cerr << "Error: Cannot create output file '" << outputFilename << "'" << std::endl;
		return 1;
	}

	outputFile << replacedContent;
	outputFile.close();
	
	std::cout << "Successfully created '" << outputFilename << "' with replacements" << std::endl;
	
	return 0;
}