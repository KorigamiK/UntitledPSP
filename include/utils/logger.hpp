#pragma once

#include <SDL2/SDL.h>

namespace Logger
{
    enum class Level
    {
        Error = SDL_LOG_PRIORITY_ERROR,
        Warning = SDL_LOG_PRIORITY_WARN,
        Info = SDL_LOG_PRIORITY_INFO,
        Debug = SDL_LOG_PRIORITY_DEBUG
    };

#ifdef VERBOSE
    template <typename... Targs>
    void Log(Level level, const char *message, Targs... args)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, static_cast<SDL_LogPriority>(level), message, args...);
    }
#else
    void Log(Level level, const char *message, ...)
    {
    }
#endif

    template <typename... Targs>
    void Warning(const char *message, Targs... args)
    {
        Log(Level::Warning, message, args...);
    }

    template <typename... Targs>
    void Info(const char *message, Targs... args)
    {
        Log(Level::Info, message, args...);
    }

    template <typename... Targs>
    void Debug(const char *message, Targs... args)
    {
        Log(Level::Debug, message, args...);
    }

    template <typename... Targs>
    void Error(const char *message, Targs... args)
    {
        Log(Level::Error, message, args...);
    }

}