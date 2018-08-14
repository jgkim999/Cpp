// tbb_concurrent_hash_map.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include "../third_party/tbb44_20160128oss/include/tbb/concurrent_hash_map.h"

using Chmap = tbb::concurrent_hash_map<int, int>;
using ChmapValue = Chmap::value_type;
using ChmapAccessor = Chmap::accessor;
using ChmapConstAccessor = Chmap::const_accessor;

Chmap test;

void test1()
{
    {
        ChmapAccessor acc;
        if (test.insert(acc, ChmapValue(1, 1)))
            std::cout << "insert success 1" << std::endl;
        else
            std::cout << "insert fail 1" << std::endl;
    }
    {
        ChmapAccessor acc;
        while (!test.insert(acc, ChmapValue(1, 2)))
        {
            std::cout << "insert fail 1" << std::endl;
            test.erase(acc);
        }
        std::cout << "insert success 1" << std::endl;
    }
    std::cout << "elements [";
    for (auto iter : test)
        std::cout << "(" << iter.first << "," << iter.second << ")";
    std::cout << "]" << std::endl;
}

void test2()
{
    std::thread t1([]() {
        for (int i = 0; i < 1000; ++i)
        {
            ChmapConstAccessor acc;
            while (!test.insert(acc, ChmapValue(1, 2)))
            {
                std::cout << "t1 insert fail 1" << std::endl;
                test.erase(acc);
            }
            std::cout << "t1 insert success 1" << std::endl;
        }
    });
    std::thread t2([]() {
        for (int i = 0; i < 1000; ++i)
        {
            ChmapConstAccessor acc;
            while (!test.insert(acc, ChmapValue(1, 2)))
            {
                std::cout << "t2 insert fail 1" << std::endl;
                test.erase(acc);
            }
            std::cout << "t2 insert success 1" << std::endl;
        }
    });
    t1.join();
    t2.join();
}

void test3()
{
    std::atomic<int> success_count = 0;
    std::atomic<int> fail_count = 0;
    std::atomic<int> find_success_count = 0;
    std::atomic<int> find_fail_count = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i)
    {
        if (i % 2)
        {
            threads.push_back(
                std::thread([&]() {
                for (int i = 0; i < 100; ++i)
                {
                    ChmapConstAccessor acc;
                    while (!test.insert(acc, ChmapValue(1, 2)))
                    {
                        ++fail_count;
                        test.erase(acc);
                    }
                    ++success_count;
                }
            }));
        }
        else
        {
            threads.push_back(
                std::thread([&]() {
                for (int i = 0; i < 100; ++i)
                {
                    ChmapConstAccessor acc;
                    if (test.find(acc, 1))
                    {
                        ++find_success_count;
                        test.erase(acc);
                    }
                    else
                    {
                        ++find_fail_count;
                    }
                }
            }));
        }
    }
    for (auto& elmt : threads)
        elmt.join();
    std::cout << "success:" << success_count << " fail:" << fail_count << std::endl;
    std::cout << "find success:" << find_success_count << " find fail:" << find_fail_count << std::endl;
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}

