/** \file log.cpp */
#include "engine_pch.h"
#include "systems/log.h"

namespace Engine {

	std::shared_ptr<spdlog::logger> Log::s_consoleLogger = nullptr;
	std::shared_ptr<spdlog::logger> Log::s_fileLogger = nullptr;
	void Log::start(SystemSignal init, ...)
	{
		spdlog::set_pattern("%^[T]: %v%$");
		spdlog::set_level(spdlog::level::trace);

		s_consoleLogger = spdlog::stderr_color_mt("Console");
		s_consoleLogger = spdlog::stderr_color_mt("File");
	}

	void Log::stop(SystemSignal close, ...)
	{
		s_consoleLogger->info("Stopping console logger");
		s_consoleLogger.reset();
		s_fileLogger->info("Stopping file logger");
		s_fileLogger.reset();
	}

}

