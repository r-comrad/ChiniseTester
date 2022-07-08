#ifndef ERRORS_HPP
#define ERRORS_HPP

//------------------------------------------------------------
//					ERROR MESSEGES DECLARATION
//------------------------------------------------------------

#include <iostream>

#include "flags.hpp"
#include "type.hpp"
#include "string.hpp"
#include "path.hpp"
#include <fstream>

#ifdef BILL_WINDOWS
// #include <windows.h>
#endif // !BILL_WINDOWS

namespace dom
{
    class Message
    {
    public:
        static Message globalMessages;

        template<typename... Args>
        void startLogBlock(Args... args) noexcept
        {
            for(sint_8 i = 0; i < mLogBlockCount; ++i) (*mLogStream) << '\t';
            ++mLogBlockCount;

            (void)std::initializer_list<bool>
            {
                static_cast<bool>((*mLogStream) << args << ' ')...
            };

            (*mLogStream) << '\n';
        }

        template<typename... Args>
        void endLogBlock(Args... args) noexcept
        {
            for(sint_8 i = 0; i < mLogBlockCount; ++i) (*mLogStream) << '\t';
            --mLogBlockCount;

            (void)std::initializer_list<bool>
            {
                static_cast<bool>((*mLogStream) << args << ' ')...
            };
            
            (*mLogStream) << '\n';
        }

        template<typename... Args>
        void writeLog(Args... args) noexcept
        {
            for(sint_8 i = 0; i < mLogBlockCount; ++i) (*mLogStream) << '\t';

            (void)std::initializer_list<bool>
            {
                static_cast<bool>((*mLogStream) << args << ' ')...
            };

            (*mLogStream) << '\n';
        }

        template<typename... Args>
        void writeError(Args... args) noexcept
        {
            #ifdef ERRORS_TO_LOG_OUTPU
                for(sint_8 i = 0; i < mLogBlockCount; ++i) (*mLogStream) << '\t';
            #endif

            (*mErrorStream) << "ERROR" << ' ';

            (void)std::initializer_list<bool>
            {
                static_cast<bool>((*mErrorStream) << args << ' ')...
            };

            (*mErrorStream) << '\n';
        }

        void writeLogEndl() noexcept;

        #ifdef BILL_WINDOWS
        /*
        \brief Gets error of WinAPI.
        \return String with error messege.
        */
        std::string GetLastWinAPIError() noexcept;
        #endif // !BILL_WINDOWS

    private:

        Message() noexcept;

        std::ostream* mLogStream;
        std::ostream* mErrorStream;

        sint_8 mLogBlockCount;
    };
}

/*
ERROR FORMAT: <file or class name>, <function>, <approximate error number>, <error message>
*/

#ifdef _DBG_
    #define START_LOG_BLOCK(...)    dom::Message::globalMessages.startLogBlock(__VA_ARGS__)
    #define END_LOG_BLOCK(...)      dom::Message::globalMessages.endLogBlock(__VA_ARGS__)
    #define WRITE_LOG(...)          dom::Message::globalMessages.writeLog(__VA_ARGS__)
    #define WRITE_LOG_ENDL          dom::Message::globalMessages.writeLogEndl
    #define WRITE_ERROR(...)        dom::Message::globalMessages.writeError(__VA_ARGS__)
#else
    #define START_LOG_BLOCK(...)    void(0)
    #define END_LOG_BLOCK(...)      void(0)
    #define WRITE_LOG(...)          void(0)
    #define WRITE_LOG_ENDL          void(0) 
    #define WRITE_ERROR(...)        void(0)    
#endif // DEBUG

#endif // !ERRORS_HPP