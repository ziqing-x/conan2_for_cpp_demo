#include "logger.h"
#include "config.h"
#include "singleton.h"

#include <execinfo.h>
#include <signal.h>

#define BLUE "\033[;34m"  // 蓝色
#define GREE "\033[;32m"  // 绿色
#define YELL "\033[;33m"  // 黄色
#define PURP "\033[;35m"  // 紫色
#define RESET "\033[0m\n" // 结束

bool is_runing = true;

void print_info() {
    // clang-format off
    LOGI("\n"
        GREE "   ____ ___  __  ______/ /__  ____ ___  ____  " RESET
        GREE "  / __ `__ \\/ / / / __  / _ \\/ __ `__ \\/ __ \\ " RESET
        GREE " / / / / / / /_/ / /_/ /  __/ / / / / / /_/ / " RESET
        GREE "/_/ /_/ /_/\\__, /\\__,_/\\___/_/ /_/ /_/\\____/  " RESET
        GREE "          /____/                              " RESET
        BLUE "───────────────────────────────────────────── " RESET
    );   
    // clang-format on
}

void segv_handler(int sig) {
    void *array[10] = { 0 };
    // 获取堆栈内容，Debug模式下可用
    auto size = backtrace(array, 10);
    char **strings = backtrace_symbols(array, size);
    for (auto i = 0; i < size; i++) {
        LOGC("Backtrace: {}", strings[i]);
    }
    free(strings);
    signal(sig, SIG_DFL);
    raise(sig);
    is_runing = false;
}

void int_handler(int sig) {
    is_runing = false;
}

int main(int argc, char *argv[]) {
    auto &config = Singleton<Config>::instance();
    if (!config.load_config("./config/config.yaml"))
    {
        return -1;
    }
    print_info();
    signal(SIGSEGV, segv_handler);
    signal(SIGINT, int_handler);
    while (is_runing) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    LOGW("Exit");
    return 0;
}
