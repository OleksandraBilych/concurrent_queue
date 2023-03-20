#include "ConcurrentQueue.hpp"

#include <iostream>
#include <string>
#include <future>
#include <chrono>

using namespace std;
using sysclock_t = std::chrono::system_clock;

std::string currentDate()
{
    std::time_t now = sysclock_t::to_time_t(sysclock_t::now());

    char buf[32] = { 0 };
    std::strftime(buf, sizeof(buf), "%m/%d/%Y, %H:%M:%S", std::localtime(&now));
    
    return std::string(buf);
}

void reader( ConcurrentQueue<string>& queue )
{
    string sdata;
    try {
        cout << "Reader calling pop" << endl;
        queue.pop(sdata);
        cout << "Reader received data: " << sdata << endl;
    }
    catch (exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
}

void writer( ConcurrentQueue<string>& queue, const string& data )
{
    cout << "Writer calling push " << endl;
    queue.push(data);
    cout << "Writer pushed data" << endl;
}

int main()
{
    ConcurrentQueue<string> queueOfString;

    auto r = async(launch::async, reader, std::ref(queueOfString));
    auto w = async(std::launch::async, writer, std::ref(queueOfString), "New record at "+currentDate());

    r.wait();
    w.wait();  

    return 0;
}