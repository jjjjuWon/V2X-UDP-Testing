#include <iostream>
#include <thread>
#include <chrono>
#include "send.hpp"

void sendThread()
{
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket == -1)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return;
    }

    struct sockaddr_in receiverAddr;
    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 실제 IP 주소로 수정
    receiverAddr.sin_port = htons(12345);

    int sentCount = 0;
    while (true)
    {
        sendSignedData(udpSocket, receiverAddr);
        sentCount++;
        if (sentCount % 500 == 0)
        {
            std::cout << "Sent " << sentCount << " packets" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 500)); // Adjust the delay as needed
    }

    close(udpSocket);
}

int main()
{
    std::thread sendThreadObj(sendThread);
    sendThreadObj.detach();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::hours(1)); // 예시로 1시간 대기
    }

    return 0;
}
