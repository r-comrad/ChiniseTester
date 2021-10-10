#pragma GCC diagnostic ignored "-Wwrite-strings"
#define INT_MAX 2147483647

#include "Run.h"


#include <cstdint> 
#include <future>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <thread>

#include <windows.h>
#include <stdio.h>
#include <atlbase.h>
#include <atlalloc.h>
#include <shlwapi.h>

#include <windows.h>
#include <userenv.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <atlconv.h>

#include <fstream>


#include "domain.h"

Run::Run() :
    mStartupInfo({ 0 })
{
    //mProcessInfo = 0;
    ZeroMemory(&mProcessInfo, sizeof(PROCESS_INFORMATION));
}

void Run::IORedirection(std::wstring& aInputPath, std::wstring& aOutputPath)
{
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    if (aInputPath == L"")
    {
        mInputHandle = CreateFile(aInputPath.c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            &sa,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    }

    if (aOutputPath == L"")
    {
        mOutputHandle = CreateFile(aOutputPath.c_str(),
            FILE_WRITE_DATA,
            FILE_SHARE_WRITE,
            &sa,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    }

    BOOL ret = FALSE;
    DWORD flags = 0;// CREATE_NO_WINDOW;

    ZeroMemory(&mStartupInfo, sizeof(STARTUPINFO));
    mStartupInfo.cb = sizeof(STARTUPINFO);
    mStartupInfo.dwFlags |= STARTF_USESTDHANDLES;
    mStartupInfo.hStdInput = mInputHandle;
    mStartupInfo.hStdError = mOutputHandle;
    mStartupInfo.hStdOutput = mOutputHandle;
}

void Run::createProcess
(
    std::wstring aName, 
    std::wstring aParameters,
    std::wstring aInputFilePath, 
    std::wstring aOutputFilePath
) 
{
    IORedirection(aInputFilePath, aOutputFilePath);

    wchar_t* name = const_cast<wchar_t*>(aName.c_str());
    if (aName == L"") name = NULL;

    wchar_t* cmd = const_cast<wchar_t*>(aParameters.c_str());

    PROCESS_INFORMATION pi;
    auto feature = std::async(std::launch::async, &Core::getMaxMemoryUsage, this, std::ref(mProcessInfo), 1000000);

    if (
        name,
        cmd,
        NULL, 
        NULL, 
        TRUE, 
        CREATE_UNICODE_ENVIRONMENT | CREATE_SUSPENDED | CREATE_NO_WINDOW, 
        NULL, 
        NULL, 
        &mStartupInfo, 
        &mProcessInfo
        ) == FALSE)
    {
#ifdef DBG
        std::cout << "ERROR #2: can't start process" << std::endl;
#endif // DEBUG      
    }

    int  reservedTime = 200;


    ResumeThread(mProcessInfo.hThread);
    long long startTime = getMillisecondsNow();
    WaitForSingleObject(mProcessInfo.hProcess, INFINITE);
    if (getExitCode(mProcessInfo.hProcess) == STILL_ACTIVE) //TODO: get 
    {
        killProcess(mProcessInfo); //TODO: kill
    }

    long long endTime = getMillisecondsNow();
    uint_64 timeUsage = endTime - startTime;

    uint_64 memoryUsage = 0;
    memoryUsage = feature.get();

    std::cout << "time usage: " << endTime - startTime << std::endl;
    std::cout << "memory usage: " << memoryUsage << std::endl;

    CloseHandle(mInputHandle);
    CloseHandle(mOutputHandle);
}

void runProcess()
{

}

void Run::runProcess(std::wstring aName, std::wstring aInputFilePath, std::wstring aOutputFilePath, std::wstring aParameters) {
    IORedirection(aInputFilePath, aOutputFilePath);
    wchar_t* cmd = const_cast<wchar_t*>(aName.c_str());
    if (aName == L"") cmd = NULL;
    wchar_t* cmd2 = const_cast<wchar_t*>(aParameters.c_str());
    //wchar_t* cmd2 = const_cast<wchar_t*>(aName.c_str() + wchar_t(L"55 C/abc/ff"));

    PROCESS_INFORMATION pi;

    //if (CreateProcess(NULL, cmd,
    //    NULL, NULL, TRUE, CREATE_UNICODE_ENVIRONMENT | CREATE_SUSPENDED | CREATE_NO_WINDOW, NULL, NULL, &mStartupInfo, &mProcessInfo) == FALSE)
    //{
    if (CreateProcess(cmd, cmd2,
        NULL, NULL, TRUE, CREATE_UNICODE_ENVIRONMENT | CREATE_NO_WINDOW, NULL, NULL, &mStartupInfo, &mProcessInfo) == FALSE)
    {
#ifdef DBG
        std::cout << "ERROR #2: can't start process" << std::endl;
#endif // DEBUG      
    }

    int  reservedTime = 200;
    //ResumeThread(mProcessInfo.hThread);

    WaitForSingleObject(mProcessInfo.hProcess, INFINITE);
    //if (getExitCode(mProcessInfo.hProcess) == STILL_ACTIVE) //TODO: get 
    //{
    //    killProcess(mProcessInfo); //TODO: kill
    //}

    CloseHandle(mInputHandle);
    CloseHandle(mOutputHandle);
}

