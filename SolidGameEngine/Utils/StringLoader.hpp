#ifndef __SOLID_UTILS_STRING_LOADER_HPP__
#define __SOLID_UTILS_STRING_LOADER_HPP__
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

namespace Solid
{
	namespace Utils
	{
		class StringLoader
		{
			public:
				StringLoader() {}

			public:
				std::string operator()(std::istream& is)
				{
					return loadFromStream(is);
				}
				std::string operator()(std::string filename)
				{
					return loadFromFile(filename);
				}

			public:
				static std::string loadFromStream(std::istream& is)
				{
					std::stringstream result;
					std::string temp;
					while (getline(is, temp))
					{
						result << temp << std::endl;
					}
					return result.str();
				}

				static std::string loadFromFile(std::string filename)
				{
					std::string result = std::string();
					std::ifstream fin;
					try
					{
						fin.open(filename);
						if (fin.fail())
						{
							std::stringstream sstr;
							sstr << "Failed to open file:\"" << filename << "\"";
							Solid::Utils::loge("Load String From File", sstr.str());
							return "";
						}
						result = loadFromStream(fin);
						fin.close();
					}
					catch (std::ifstream::failure& e)
					{
						Solid::Utils::loge("Load String From File", e.what());
						//Solid::loge("Load String From File", e.what());
					}
					return result;
				}

				static std::vector<std::string> split(std::string data, char ch)
				{
					std::vector<std::string> result;
					std::stringstream temp;
					for (char i : data)
					{
						if (i == ch)
						{
							result.push_back(temp.str());
							temp.str("");
						}
						else
						{
							temp << i;
						}
					}
					result.push_back(temp.str());
					return result;
				}

				static std::vector<std::string> split_no_none(std::string data, char ch)
				{
					std::vector<std::string> result;
					std::stringstream temp;
					for (char i : data)
					{
						if (i == ch)
						{
							if (temp.str().length() != 0)
							{
								result.push_back(temp.str());
								temp.str("");
							}
						}
						else
						{
							temp << i;
						}
					}
					if (temp.str().length() != 0)
					{
						result.push_back(temp.str());
					}
					return result;
				}
		};
	}
}

#endif
