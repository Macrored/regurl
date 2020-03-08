#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdint>

typedef enum log_rank {
	LOG_INFO = 0,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL,
} log_rank_t;

void initLogger(const std::string &info_filename, const std::string &warn_filename,
	const std::string &error_filename);

class Logger {
	friend void initLogger(const std::string &info_filename, const std::string &warn_filename,
		const std::string &error_filename);
public:
	Logger(log_rank_t log_rank) :m_log_rank(log_rank) {};
	~Logger();
	static std::ostream &start(log_rank_t log_rank, const int line, const std::string &fun);

private:
	static std::ostream &getStream(log_rank_t log_rank);

	static std::ofstream m_info_file;
	static std::ofstream m_warn_file;
	static std::ofstream m_error_file;
	log_rank_t m_log_rank;
};

#define CplusLog(log_rank) \
        Logger(log_rank).start(log_rank, __LINE__, __FUNCTION__)

#endif