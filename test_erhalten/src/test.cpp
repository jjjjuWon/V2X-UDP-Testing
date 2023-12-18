#include <iostream>
#include <thread>
#include <atomic>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "send.hpp"
#include "receive.hpp"

std::atomic_bool shouldSendData(true);
std::atomic_bool shouldReceiveData(true);

void sendThread(int udpSocket)
{
    while (true)
    {
        if (shouldSendData)
        {
            sendSignedData(udpSocket);
            std::cout << "Sent data" << std::endl;
        }
        // 조절 가능한 딜레이 추가
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void receiveThread(int udpSocket)
{
    while (true)
    {
        if (shouldReceiveData)
        {
            receiveAndVerifyData(udpSocket);
        }
        // 조절 가능한 딜레이 추가
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main()
{
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket == -1)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    struct sockaddr_in localAddr;
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = INADDR_ANY;
    localAddr.sin_port = htons(12345); // 포트 번호 수정

    if (bind(udpSocket, (struct sockaddr *)&localAddr, sizeof(localAddr)) == -1)
    {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }

    // 스레드 생성 및 시작
    std::thread sendThreadObj(sendThread, udpSocket);
    std::thread receiveThreadObj(receiveThread, udpSocket);

    // 스레드 종료 대기
    sendThreadObj.join();
    receiveThreadObj.join();

    close(udpSocket);
    return 0;
}
