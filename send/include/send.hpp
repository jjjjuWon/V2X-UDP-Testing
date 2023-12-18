#pragma once

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

extern struct sockaddr_in receiverAddr; // receiverAddr의 선언

void sendSignedData(int socket, const struct sockaddr_in &receiverAddr);

const char *createSignedData(const char *data, size_t dataSize);
