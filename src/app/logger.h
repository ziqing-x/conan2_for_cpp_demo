#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "make_unique.h"
#include "singleton.h"
#include "config.h"

#include "spdlog/async.h"
#include "spdlog/fmt/bin_to_hex.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <memory>
#include <thread>

#define LOG_FLUSH_ON spdlog::level::warn // 当打印这个级别日志时flush
#define LOGE(...) Singleton<Logger>::instance().log_error(__VA_ARGS__)
#define LOGW(...) Singleton<Logger>::instance().log_warn(__VA_ARGS__)
#define LOGI(...) Singleton<Logger>::instance().log_info(__VA_ARGS__)
#define LOGD(...) Singleton<Logger>::instance().log_debug(__VA_ARGS__)
#define LOGC(...) Singleton<Logger>::instance().log_critical(__VA_ARGS__)

#define TO_HEX(data, len) spdlog::to_hex(data, data + len)

class Logger {
private:
    std::unique_ptr<spdlog::logger> _logger;

private:
    bool is_debug_mode() {
        char *var = getenv("debug");
        if (nullptr == var) {
            return false;
        }
        if (0 == strcmp(var, "on")) {
            return true;
        }
        return false;
    }

public:
    Logger() {
        auto &config = Singleton<Config>::instance();
        auto function = [&]() {
            auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                config.logger.log_file_name, config.logger.log_fize_size, config.logger.log_rotation);
            std::vector<spdlog::sink_ptr> sinks{ stdout_sink, rotating_sink };
            _logger = std::make_unique<spdlog::logger>(config.logger.log_name, sinks.begin(), sinks.end());
            _logger->set_pattern(config.logger.log_pattern);
            if (is_debug_mode()) {
                _logger->set_level(spdlog::level::debug);
            } else {
                _logger->set_level(spdlog::level::info);
            }
            _logger->flush_on(LOG_FLUSH_ON);
        };
        try {
            function();
        } catch (const std::exception &e) {
            std::cout << "Construct logger error: " << e.what() << std::endl;
        }
        std::thread([&]() {
            while (true) {
                _logger->flush();
                std::this_thread::sleep_for(std::chrono::seconds(config.logger.log_flush));
            }
        }).detach();
    }

    template <typename... Args>
    inline void log_error(const char *fmt, Args... args) {
        _logger->error(fmt, args...);
    }

    template <typename... Args>
    inline void log_warn(const char *fmt, Args... args) {
        _logger->warn(fmt, args...);
    }

    template <typename... Args>
    inline void log_info(const char *fmt, Args... args) {
        _logger->info(fmt, args...);
    }

    template <typename... Args>
    inline void log_debug(const char *fmt, Args... args) {
        _logger->debug(fmt, args...);
    }

    template <typename... Args>
    inline void log_critical(const char *fmt, Args... args) {
        _logger->critical(fmt, args...);
    }
};

#endif // __LOGGER_H__