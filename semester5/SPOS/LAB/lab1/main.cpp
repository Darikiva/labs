#include <iostream>
#include "boost/process.hpp"
#include "boost/process/extend.hpp"
#include <string>
#include "chrono"
#include "ncurses.h"

enum State {
    DEFAULT, RESULTED
};

namespace MyNamespace {
    using namespace std::chrono;
    int f_res;
    int g_res;
    system_clock::time_point start_point;
    long f_time = -1;
    long g_time = -1;

    std::string path_f = "../function_f/function_f";
    std::string path_g = "../function_g/function_g";

    void startTimer() {
        start_point = system_clock::now();
    }

    long getTimer() {
        system_clock::time_point finish = system_clock::now();
        return duration_cast<milliseconds>(finish - start_point).count();
    }

    void printResult(WINDOW *win) {
        std::string result;
        if (MyNamespace::f_time >= 0 && MyNamespace::g_time >= 0) {
            result = "Result = " + std::to_string(std::min(MyNamespace::f_res, MyNamespace::g_res));
        } else if (MyNamespace::f_time >= 0) {
            if (MyNamespace::f_res == 0) result = "Result = 0";
            else {
                result = "Result can't be computed in the case of g was cancelled; f = " +
                         std::to_string(MyNamespace::f_res);
            }
        } else if (MyNamespace::g_time >= 0) {
            if (MyNamespace::g_res == 0) result = "Result = 0";
            else {
                result = "Result can't be computed in the case of f was cancelled; g = " +
                        std::to_string(MyNamespace::g_res);
            }
        } else {
            result = "Result can't be computed in the case of f and g were cancelled";
        }
        result.insert(0, "\n");
        wprintw(win, result.c_str());
        wrefresh(win);
        getch();
    }
}


int main() {
    boost::process::child f, g;
    boost::process::ipstream f_out, g_out;
    boost::process::opstream f_in, g_in;
    State state = State::DEFAULT;
    std::condition_variable cndvr;
    std::mutex mtx, mtx2;

    initscr();
    printw("Press 'q' or 'Esc' to cancel\n");
    keypad(stdscr, true);
    int case_n = getch() - '0';
    noecho();
    nodelay(stdscr, true);
    auto handler_key = std::async([&]() {
        int key;
        bool flag = false;
        do {
            if (state == State::RESULTED) return;
            key = getch();

            switch (key) {
                case 'q':
                    flag = true;
                    break;
                case 27:
                    flag = true;
                    break;
                default:
                    break;
            }
        } while (!flag);
        if (state == State::RESULTED) return;
        state = State::RESULTED;
        f.terminate();
        g.terminate();
        cndvr.notify_one();
    });

    MyNamespace::startTimer();
    f = boost::process::child(MyNamespace::path_f,
                              boost::process::std_out > f_out, boost::process::std_in < f_in);
    g = boost::process::child(MyNamespace::path_g,
                              boost::process::std_out > g_out, boost::process::std_in < g_in);
    f_in << case_n << std::endl;
    g_in << case_n << std::endl;

    std::unique_lock<std::mutex> lck(mtx);
    auto f_run = std::async([&]() {
        if (f_out >> MyNamespace::f_res) {
            MyNamespace::f_time = MyNamespace::getTimer();
        }
        if (state == State::RESULTED) return;
        cndvr.notify_one();
    });
    auto g_run = std::async([&]() {
        if (g_out >> MyNamespace::g_res) {
            MyNamespace::g_time = MyNamespace::getTimer();
        }
        if (state == State::RESULTED) return;
        cndvr.notify_one();
    });
    using namespace std::chrono_literals;
    while ((MyNamespace::f_time == -1 || MyNamespace::g_time == -1) && state != State::RESULTED) {
        cndvr.wait(lck);
        if (MyNamespace::f_time != -1 && MyNamespace::f_res == 0) {
            state = State::RESULTED;
            g.terminate();
        } else if (MyNamespace::g_time != -1 && MyNamespace::g_res == 0) {
            state = State::RESULTED;
            f.terminate();
        } else if (MyNamespace::f_time != -1 && MyNamespace::g_time != -1) {
            state = State::RESULTED;
        }
    }
    MyNamespace::printResult(stdscr);
    nodelay(stdscr, false);
    wprintw(stdscr, "\nPress any key to end");
    getch();
    endwin();
    return 0;
}
