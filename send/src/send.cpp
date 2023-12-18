#include "send.hpp"

static const int signatureSize = 100; // 임시로 서명 크기 정의

const char *createSignedData(std::string &data)
{
    // 여기서 서명 데이터 생성 로직을 구현
    // 예시: 간단한 서명 생성을 통해 데이터와 서명을 생성하여 반환하는 로직을 작성
    // 실제로는 사용 중인 암호화 라이브러리와 알고리즘에 따라 구현
    // std::string signature = "..."; // 생성된 서명
    // return signature;
    return "example_signature)"; // 임시로 서명 문자열 반환
}

void sendSignedData(int socket, const struct sockaddr_in &receiverAddr)
{
    // 서명 데이터 생성 및 송신 로직
    // 가정: createSignedData 함수는 서명 데이터를 생성하는 함수로, 데이터와 서명을 생성하여 반환

    std::string data = "Sent Data(";
    std::string signature = createSignedData(data); // 서명 생성

    // 서명과 데이터를 합쳐서 전송
    std::string combinedData = data + signature;

    sendto(socket, combinedData.c_str(), combinedData.size(), 0, (struct sockaddr *)&receiverAddr, sizeof(receiverAddr));
}
