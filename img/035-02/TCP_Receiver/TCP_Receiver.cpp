// TCP_Receiver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

/*
Visual Studio Setup:

Right-click your Project -> Properties.

Go to Linker -> Input.

Add ws2_32.lib to Additional Dependencies.
*/


#pragma comment(lib, "ws2_32.lib")

int main()
{
    std::cout << "Hello World!\n";

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 3);

    std::cout << "Waiting for ESP32 on port 8080..." << std::endl;
    /*
    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        std::cout << "ESP32 Connected!" << std::endl;

        char buffer[1024] = { 0 };
        int bytesReceived;
        while ((bytesReceived = recv(clientSocket, buffer, 1024, 0)) > 0) {
            std::cout << "Received: " << std::string(buffer, bytesReceived);
        }
        std::cout << "ESP32 Disconnected." << std::endl;
        closesocket(clientSocket);
    }
*/
    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        // Optional: identify which device connected
        std::cout << "\n[Incoming Message] " << std::endl;

        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, 1024, 0);

        if (bytesReceived > 0) {
            // Null-terminate the string so C++ knows where the text ends
            buffer[bytesReceived] = '\0';
            std::cout << "ESP32 Says: " << buffer;
        }

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
