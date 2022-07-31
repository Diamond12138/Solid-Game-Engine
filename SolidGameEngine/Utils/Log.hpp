#ifndef __SOLID_UTILS_LOG_HPP__
#define __SOLID_UTILS_LOG_HPP__
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>

namespace Solid
{
	namespace Utils
	{
		enum LogLevel
		{
			UNKNOW,
			INFO,
			DEBUG,
			ERROR,
			WARNNING
		};

		struct LogItem
		{
			time_t time;
			LogLevel level;
			std::string title;
			std::string content;
		};

		class Log
		{
			private:
				std::vector<LogItem> m_logs;
				bool m_is_output_to_console;
				std::ostream* m_output_stream;

			public:
				Log(bool is_output_to_console = false) : m_is_output_to_console(is_output_to_console), m_output_stream(nullptr) {}
				Log(std::ostream* output_stream, bool is_output_to_console = false) : m_is_output_to_console(is_output_to_console), m_output_stream(output_stream) {}

			public:
				Log& setIsOutputToConsole(bool is_output_to_console)
				{
					m_is_output_to_console = is_output_to_console;
					return *this;
				}
				bool getIsOutputToConsole()
				{
					return m_is_output_to_console;
				}
				Log& setIsOutputStream(std::ostream* output_stream)
				{
					m_output_stream = output_stream;
					return *this;
				}
				std::ostream* getIsOutputStream()
				{
					return m_output_stream;
				}

			public:
				static std::string getLevelString(LogLevel level)
				{
					if (level == LogLevel::INFO)
					{
						return "Info";
					}
					else if (level == LogLevel::DEBUG)
					{
						return "Debug";
					}
					else if (level == LogLevel::ERROR)
					{
						return "Error";
					}
					else if (level == LogLevel::WARNNING)
					{
						return "Warnning";
					}
					else
					{
						return "Unknow";
					}
				}
				static  std::string default_format_item(LogItem item)
				{
					std::stringstream str = std::stringstream();
					str << "time:" << ctime(&item.time);
					str << "level:" << getLevelString(item.level) << std::endl;
					str << "title:" << item.title << std::endl;
					str << "content:" << item.content << std::endl;
					return str.str();
				}

			public:
				virtual std::string format_item(LogItem item)
				{
					return default_format_item(item);
				}
				Log& output_all_to_console()
				{
					return output_all_to_stream(std::cout);
				}
				Log& output_all_to_stream()
				{
					return output_all_to_stream(*m_output_stream);
				}
				Log& output_all_to_stream(std::ostream& os)
				{
					for (unsigned int i = 0; i < m_logs.size(); i++)
					{
						os << format_item(m_logs.at(i)) << std::endl;
					}
					return *this;
				}

			public:
				Log& log(time_t time, LogLevel level, std::string title, std::string content)
				{
					LogItem item = {time, level, title, content};
					m_logs.push_back(item);
					std::string itemstr = format_item(item);
					if (m_output_stream != nullptr)
					{
						(*m_output_stream) << itemstr << std::endl;
					}
					if (m_is_output_to_console)
					{
						std::cout << itemstr << std::endl;
					}
					return *this;
				}
				Log& u(std::string title, std::string content)
				{
					return log(time(nullptr), LogLevel::UNKNOW, title, content);
				}
				Log& i(std::string title, std::string content)
				{
					return log(time(nullptr), LogLevel::INFO, title, content);
				}
				Log& d(std::string title, std::string content)
				{
					return log(time(nullptr), LogLevel::DEBUG, title, content);
				}
				Log& e(std::string title, std::string content)
				{
					return log(time(nullptr), LogLevel::ERROR, title, content);
				}
				Log& w(std::string title, std::string content)
				{
					return log(time(nullptr), LogLevel::WARNNING, title, content);
				}
		};

		void log(std::string title, std::string content, LogLevel level = LogLevel::UNKNOW)
		{
			LogItem item = {time(nullptr), level, title, content};
			std::cout << Log::default_format_item(item) << std::endl;
		}

		void logu(std::string title, std::string content)
		{
			log(title, content, LogLevel::UNKNOW);
		}
		void loge(std::string title, std::string content)
		{
			log(title, content, LogLevel::ERROR);
		}
		void logi(std::string title, std::string content)
		{
			log(title, content, LogLevel::INFO);
		}
		void logd(std::string title, std::string content)
		{
			log(title, content, LogLevel::DEBUG);
		}
	}
}

#endif
