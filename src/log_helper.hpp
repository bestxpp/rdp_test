#pragma once
#include <memory>

#define SPD_LOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/async.h"
#include "spdlog/cfg/env.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

// #define std_file_log

class conclelog
{
  public:
	enum log_size
	{
		one_kb = 1024,
		one_mb = 1024 * one_kb
	};

	conclelog()
	{
		consol_Log = spdlog::stderr_color_mt<spdlog::async_factory>("clog");
		consol_Log->set_pattern("[%t] %+");
	}

	std::shared_ptr<spdlog::logger> getConsolLog() { return consol_Log; }
	std::shared_ptr<spdlog::logger> consol_Log;
};

class spdlog_helper : public conclelog
{
  public:
	static spdlog_helper& get()
	{
		static spdlog_helper log;
		return log;
	}

	std::shared_ptr<spdlog::logger> getFileLog() { return async_file; }

  private:
	spdlog_helper()
	{
		// char  buffer[MAX_PATH];
		// DWORD code = GetEnvironmentVariable("tmp", buffer, MAX_PATH);
		// std::string logName = std::string(buffer).append("\\hd_sign.log");

		std::string logName = "sign.log";
		// async_file			= spdlog::rotating_logger_mt<spdlog::async_factory>("flog",
		// "my.log", one_mb
		// * 100, 100);
		async_file = spdlog::daily_logger_st<spdlog::async_factory>("flog", logName, 0, 0);
		async_file->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%l][%t][%s:%#]%v");

		async_file->set_level(spdlog::level::debug);
		async_file->flush_on(spdlog::level::debug);
	}
	~spdlog_helper() { spdlog::shutdown(); }

	void setLevel(spdlog::level::level_enum level)
	{
		async_file->set_level(level);
		// async_file->flush_on(spdlog::level::err);
	}
	std::shared_ptr<spdlog::logger> async_file;
};

#ifdef std_file_log
#define log_handle spdlog_helper::get().getFileLog()
#else
#define log_handle spdlog_helper::get().getConsolLog()
#endif	// std_log

/*
trace = SPDLOG_LEVEL_TRACE,
debug = SPDLOG_LEVEL_DEBUG,
info = SPDLOG_LEVEL_INFO,
warn = SPDLOG_LEVEL_WARN,
err = SPDLOG_LEVEL_ERROR,
critical = SPDLOG_LEVEL_CRITICAL,*/

#define LOG_TRACE(...) SPDLOG_LOGGER_TRACE(log_handle, __VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(log_handle, __VA_ARGS__)
#define LOG_INFO(...)  SPDLOG_LOGGER_INFO(log_handle, __VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_LOGGER_ERROR(log_handle, __VA_ARGS__)
#define LOG_WARN(...)  SPDLOG_LOGGER_WARN(log_handle, __VA_ARGS__)