#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include "receive.hpp"

std::mutex mtx;
// TODO: send가 없을 시 잠시 동작을 중지하고 마지막 로그를 반복해서 출력하게 하기 위함
std::condition_variable cv;
bool sendReady = false;

void receiveThread()
{
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket == -1)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return;
    }

    struct sockaddr_in localAddr;
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    localAddr.sin_port = htons(12345);

    if (bind(udpSocket, (struct sockaddr *)&localAddr, sizeof(localAddr)) == -1)
    {
        std::cerr << "Bind failed" << std::endl;
        return;
    }

    int receivedCount = 0;
    int successCount = 0;
    while (true)
    {
        receiveAndVerifyData(udpSocket);

        receivedCount++;
        if (receivedCount % 500 == 0)
        {
            std::cout << "Received " << receivedCount << " packets. Successful: " << successCount << std::endl;
        }
    }

    close(udpSocket);
}

int main()
{
    std::thread receiveThreadObj(receiveThread);
    receiveThreadObj.detach();

    while (true)
    {
        // 메인 스레드는 아무 작업도 수행하지 않고 대기
        std::this_thread::sleep_for(std::chrono::hours(1)); // 예시로 1시간 대기
    }

    return 0;
}
