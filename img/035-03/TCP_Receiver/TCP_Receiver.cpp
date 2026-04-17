// TCP_Receiver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>   // For timestamps
#include <iomanip>  // For formatting the time string
#include <direct.h> // For _mkdir on Windows


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
*/
    // Create the 'img' directory if it doesn't exist
    _mkdir("img");

    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        // Optional: identify which device connected
        std::cout << "\n[Incoming Message] " << std::endl;

        // 1. Receive the 4-byte header (The Image Size)
        uint32_t imageSize = 0;
        int headerBytes = recv(clientSocket, (char*)&imageSize, sizeof(imageSize), 0);
        //
        if (headerBytes == sizeof(imageSize) && imageSize > 0) {
            std::cout << "Receiving image: " << imageSize << " bytes..." << std::endl;

            // 2. Prepare a buffer for the image
            std::vector<char> imageBuffer(imageSize);
            int totalBytesRead = 0;

            // 3. Keep reading until the whole file is in memory
            while (totalBytesRead < imageSize) {
                int bytes = recv(clientSocket, &imageBuffer[totalBytesRead], imageSize - totalBytesRead, 0);
                if (bytes <= 0) break;
                totalBytesRead += bytes;
            }

            // --- TIMESTAMP LOGIC ---
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            std::stringstream ss;
            // Format: img/capture_YYYYMMDD_HHMMSS.jpg
            ss << "img/capture_" << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S") << ".jpg";
            std::string fileName = ss.str();


            // 4. SAVE TO FILE: Write the bytes to a .jpg file on your PC
            std::ofstream outFile(fileName, std::ios::binary);
            if (outFile.is_open()) {
                outFile.write(imageBuffer.data(), imageBuffer.size());
                outFile.close();
                std::cout << "ARCHIVED: " << fileName << std::endl;
            }

            //std::cout << "SUCCESS: 'captured_frame.jpg' saved to project folder!" << std::endl;
        }
        closesocket(clientSocket);
    }

//    closesocket(serverSocket);
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
