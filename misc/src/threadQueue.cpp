#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <queue>
#include <array>
#include <chrono>

//--------------------------------------------------------------
// cpp ref example ==>>
namespace
{
    std::mutex m;
    std::condition_variable cv;
    std::string data;
    bool ready = false;
    bool processed = false;

    void worker_thread()
    {
        // wait until main() sends data
        std::unique_lock lk(m);
        cv.wait(lk, [] { return ready; });

        // after the wait, we own the lock
        std::cout << "Worker thread is processing data\n";
        data += " after processing";

        // send data back to main()
        processed = true;
        std::cout << "Worker thread signals data processing completed\n";

        // manual unlocking is done before notifying, to avoid waking up
        // the waiting thread only to block again (see notify_one for details)
        lk.unlock();
        cv.notify_one();
    }

}

void cv_main()
{
    std::thread worker(worker_thread);

    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();

    // wait for the worker
    {
        std::unique_lock lk(m);
        cv.wait(lk, [] { return processed; });
    }
    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();
}
// <<==  cpp ref example 
//--------------------------------------------------------------

// MY

namespace 
{
    struct sTask
    {
        int32_t payLoad;
    };


    class cThreadQueue
    {
    public:

        void pusn(sTask&& t)
        {
            std::lock_guard lk(mMxTasks);
            mTasks.push(t);
            mCvTasks.notify_one();
        }

        sTask pop()
        {
            std::unique_lock lk(mMxTasks);
            
            // 1
            while (mTasks.empty())
            {
                mCvTasks.wait(lk);
            }
            
            // 2
            //mCvTasks.wait(lk, [&] {return !mTasks.empty(); });

            sTask t{ mTasks.front() };
            mTasks.pop();
            return t;
            //return std::move(t);
        }

        cThreadQueue() = default;
        cThreadQueue(const cThreadQueue&) = delete;
        cThreadQueue(cThreadQueue&&) = delete;

        cThreadQueue& operator=(const cThreadQueue&) = delete;
        cThreadQueue& operator=(cThreadQueue&&) = delete;

    private:
        std::queue<sTask> mTasks;
        std::mutex mMxTasks;
        std::condition_variable mCvTasks;
    };
}

void tq_main()
{

    //simply test of push/pop
    //const std::array values{  1,2,3,4,5,6,7,8,9,10,  };
    //cThreadQueue tq;
    //for (auto v : values)
    //{
    //    sTask t{ v };

    //    tq.pusn(std::move(t));
    //}
    //for (auto v : values)
    //{
    //    auto t = tq.pop();

    //    printf("t = %d \n", t.payLoad);
    //}


    using namespace std::chrono_literals;


    cThreadQueue tq;

    std::thread dataSender([&tq]
        {
            for (int32_t i = 0; i < 1000; ++i)
            {
                sTask t{ i };
                tq.pusn(std::move(t));
                std::this_thread::sleep_for(5ms);
            }
        });



    std::mutex mtx;

    constexpr auto THREAD_COUNT = 10;
    std::vector<std::thread> exequtors;
    exequtors.reserve(THREAD_COUNT);
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        exequtors.push_back(std::thread([i, &tq, &mtx]
            {
                while (true)
                {

                    auto t = tq.pop();
                    {
                        std::lock_guard lk(mtx);
                        std::cout << "ID = " << std::this_thread::get_id()
                            << "\t i = " << i
                            << "\t task =" << t.payLoad
                            << "\n";
                    }
                    std::this_thread::sleep_for(100ms);
                }
            }));
    }



    dataSender.join();


    //NOTE: executors never been stop
    for (int i = 0; i < exequtors.size(); ++i)
    {
        exequtors[i].join();
    }

}