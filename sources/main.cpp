
#define _CRT_SECURE_NO_WARNINGS

#include <string>


#include <iostream>

#include "core.h"

//
//int pipeA[2];
//int pipeB[2];
//
//pipe(pipeA);
//pipe(pipeB);
//
//int pd = fork();
//
//if (!pd)
//{
//dup2(pipeA[0], STDIN_FILENO);
//
//char* nn = new char[4];
//nn[0] = 0;
//nn[1] = 0;
//nn[2] = 0;
//nn[3] = 0;
//std::cin >> nn[0] >> nn[1];
//std::cout << nn[0] << nn[1] << std::endl;
//
//dup2(pipeB[1], STDOUT_FILENO);
//std::cout << 8;
//}
//else
//{
//char n[] = "5 2\0";
//write(pipeA[1], &n, sizeof(n));
//char* nn = new char[2];
//nn[0] = 0;
//nn[1] = 0;
//read(pipeB[0], nn, 1);
//std::cout << char(*nn);
//}

int main(int argc, char* argv[])
{
//    int pipeA[2];
//    int pipeB[2];
//
//    pipe(pipeA);
//    pipe(pipeB);
//
//    int pd = fork();
//
//    if (!pd)
//    {
////        int n = 0;
////        read(pipeA[0], &n, sizeof(n));
////        n += 5;
////        write(pipeB[1], &n, sizeof(n));
//
////           dup2(pipeA[0], STDIN_FILENO);
////        dup2(pipeB[1], STDOUT_FILENO);
//
//        dup2(pipeA[0], STDIN_FILENO);
//
////        char* nn = new char[4];
////        nn[0] = 0;
////        nn[1] = 0;
////        nn[2] = 0;
////        nn[3] = 0;
////        std::cin >> nn[0] >> nn[1];
////        std::cout << nn[0] << nn[1] << std::endl;
//
//        dup2(pipeB[1], STDOUT_FILENO);
//
//
//        execlp(
//                "python3",
//                "python3",
//                "/home/sasiska/CLionProjects/ChineseTester/media/2/1.py",
//                NULL
//        );
////        std::cout << 8;
//    }
//    else
//    {
//        //int n = 5;
//        char n[] = "5 2\n\0";
//        int sss = sizeof(n);
//        write(pipeA[1], &n, sizeof(n));
//        char* nn = new char[2];
//                nn[0] = 0;
//                nn[1] = 0;
//        read(pipeB[0], nn, 1);
//        std::cout << char(*nn);
//    }
//
//
//    return 0;

    //std::wcout << std::endl;
    //std::wcout << MAIN_PATH;
    //std::wcout << std::endl;
    //std::wcout << RESOURCES;
    //return 0;
    int num = 3;
    if (argc > 1)
    {
        num = std::stoi(getString(argv[1]));
    }

#ifdef LOG_TO_FILE_OUTPUT
    freopen((LOGS_PATH + std::to_string(num)).c_str(), "w", stdout);
#endif

    WD_LOG("ID: " << num);
    WD_END_LOG;
    Core core(DATABASE_PATH);
    core.run(num);
    return 0;
}