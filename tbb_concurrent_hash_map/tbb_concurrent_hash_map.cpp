// tbb_concurrent_hash_map.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <random>
#include "../third_party/tbb44_20160128oss/include/tbb/concurrent_hash_map.h"

class InsertEraseFind
{
private:
    using Data = tbb::concurrent_hash_map<int, int>;
    using DataValue = Data::value_type;
    using DataAccessor = Data::accessor;
    using DataConstAccessor = Data::const_accessor;
public:
    InsertEraseFind()
    {
        std::random_device rd;
        gen_ = std::mt19937(rd());
        dis_ = std::uniform_int_distribution<>(1, 100);
    }

    ~InsertEraseFind()
    {
    }

    void Run()
    {
        for (int i = 0; i < 30; ++i)
        {
            auto mod = i % 3;
            if (mod == 0)
                threads_.push_back(std::thread(&InsertEraseFind::Insert, this));
            else if (mod == 1)
                threads_.push_back(std::thread(&InsertEraseFind::Find, this));
            else
                threads_.push_back(std::thread(&InsertEraseFind::Erase, this));
        }
        for (auto& elmt : threads_)
            elmt.join();
        std::cout << "insert success:" << insert_success_count_ << " fail:" << insert_fail_count_ << std::endl;
        std::cout << "find success:" << find_success_count_ << " fail:" << find_fail_count_ << std::endl;
        std::cout << "erase success:" << erase_success_count_ << " fail:" << erase_fail_count_ << std::endl;

        std::cout << "[";
        for (auto& data : data_)
            std::cout << "{" << data.first << "," << data.second << "}";
        std::cout << "]" << std::endl;
    }

    void Erase()
    {
        for (int i = 0; i < loop_count_; ++i)
        {
            if (data_.erase(RandomInt()))
                ++erase_success_count_;
            else
                ++erase_fail_count_;
        }
    }

    void Find()
    {
        for (int i = 0; i < loop_count_; ++i)
        {
            DataConstAccessor acc;
            if (data_.find(acc, RandomInt()))
                ++find_success_count_;
            else
                ++find_fail_count_;
        }
    }

    void Insert()
    {
        for (int i = 0; i < loop_count_; ++i)
        {
            DataValue value(RandomInt(), RandomInt());
            DataAccessor acc;
            while (!data_.insert(acc, value))
            {
                ++insert_fail_count_;
                data_.erase(acc);
            }
            ++insert_success_count_;
        }
    }
private:
    int RandomInt()
    {
        return dis_(gen_);
    }
private:
    Data data_;
    std::mt19937 gen_;
    std::uniform_int_distribution<> dis_;

    std::atomic<int> insert_success_count_ = 0;
    std::atomic<int> insert_fail_count_ = 0;

    std::atomic<int> find_success_count_ = 0;
    std::atomic<int> find_fail_count_ = 0;

    std::atomic<int> erase_success_count_ = 0;
    std::atomic<int> erase_fail_count_ = 0;

    std::vector<std::thread> threads_;

    int loop_count_ = 100;
};

int main()
{
    InsertEraseFind test;
    test.Run();
    return 0;
}