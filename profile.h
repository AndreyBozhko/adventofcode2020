#pragma once

#include <chrono>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;

class LogDuration {
public:
    explicit LogDuration(const string& msg = "")
            : message(msg + ": ")
            , start(steady_clock::now())
    {
    }

    ~LogDuration() {
        auto finish = steady_clock::now();
        auto dur = duration_cast<microseconds>(finish - start).count();
        cerr << message
             << static_cast<double>(dur)/1000.0
             << " ms" << endl;
    }
private:
    string message;
    steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
  LogDuration UNIQ_ID(__LINE__){message};
