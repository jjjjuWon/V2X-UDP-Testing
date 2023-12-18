#include <cstring>
#include <mutex>
#include <iomanip>

#include "receive.hpp"

std::atomic_int receivedCount(0);
std::atomic_int successCount(0);
std::mutex countMutex;

// verifySignature 함수를 정의하여 서명 검증 로직을 추가
bool verifySignature(std::string &data)
{
    // 여기서 서명 데이터 검증 로직을 구현
    // 예시: 간단한 서명 검증을 통해 서명이 유효한지 확인하는 로직을 작성
    // 실제로는 사용 중인 암호화 라이브러리와 알고리즘에 따라 구현되어야 한다.
    // return true; // 서명이 유효한 경우
    // return false; // 서명이 유효하지 않은 경우

    bool isSignatureValid = true; // 임시로 true로 설정

    if (isSignatureValid)
    {
        successCount++; // 서명이 유효한 경우 successCount 증가
        {
            std::lock_guard<std::mutex> lock(countMutex);
        }
        return true; // 임시로 true 반환
    }
    else
    {
        return false; // 임시로 false 반환
    }
}

// processValidData 함수를 정의하여 유효한 데이터 처리 로직을 추가
void processValidData(std::string &data)
{
    // 유효한 데이터 처리 로직을 작성
    // 예시: 데이터를 출력하거나 다른 작업을 수행한다.
    std::cout << "Received valid data: " << data << std::endl; // 유효한 데이터 출력
}

// handleInvalidData 함수를 정의하여 유효하지 않은 데이터 처리 로직을 추가
void handleInvalidData()
{
    // 유효하지 않은 데이터 처리 로직을 작성
    // 예시: 에러 메시지를 출력하거나 다른 오류 처리 작업을 수행한다.
    std::cerr << "Received invalid data" << std::endl;
}

void receiveAndVerifyData(int socket)
{
    std::string buffer(1024, '\0');
    struct sockaddr_in senderAddr;
    socklen_t senderAddrLen = sizeof(senderAddr);

    ssize_t dataSize = recvfrom(socket, &buffer[0], buffer.size(), 0, (struct sockaddr *)&senderAddr, &senderAddrLen);

    if (dataSize > 0)
    {
        {
            std::lock_guard<std::mutex> lock(countMutex);
            receivedCount++;
        }
        std::cout << "Received data. Total received: " << receivedCount.load() << " times" << std::endl;

        std::string data(buffer, 0, dataSize); // 수신한 데이터만을 가지는 부분 문자열 생성

        // 서명 데이터 검증 및 처리 로직
        // verifySignature 함수와 관련된 로직 추가
        // 가정: verifySignature 함수는 서명 검증을 위한 함수로, 데이터와 서명을 인자로 받아 검증 결과를 반환
        if (verifySignature(data))
        {
            processValidData(data);
        }
        else
        {
            handleInvalidData();
        }
    }
}
