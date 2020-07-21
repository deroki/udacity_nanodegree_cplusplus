#include <iostream>
#include <random>
#include "TrafficLight.h"
#include <random>
#include <future>

/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // TODO FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
    std::unique_lock<std::mutex> uLock(_mtx);
    _cond.wait(uLock, [this]{return !_queue.empty();});
    T lastElement = std::move(_queue.back());
    _queue.pop_back();
    return lastElement;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> lGuard(_mtx);
    _queue.push_back(std::move(msg));
    _cond.notify_one();
}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // TODO FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        TrafficLightPhase tfp = _msgQueue.receive();
        if (tfp == green) return ;
    }

}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // TODO FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // TODO FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(4,6);
    auto start = std::chrono::system_clock::now();
    int random_time = distribution(generator);

    while(true)
    {   
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        auto end = std::chrono::system_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        if (elapsed_time > random_time){

            _currentPhase = _currentPhase == red ? green : red;
            //TODO: add send to msg queue
            auto ftr = std::async(std::launch::async, 
                                    &MessageQueue<TrafficLightPhase>::send,
                                    &_msgQueue,
                                    std::move(_currentPhase));
            ftr.wait();
            start = std::chrono::system_clock::now();
            int random_time = distribution(generator);
        }


    }

    
}

