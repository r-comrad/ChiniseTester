#include "errors.hpp"

#ifdef BILL_WINDOWS
std_string
GetLastErrorAsString()
{
    setlocale(LC_ALL, "Russian");

    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    //Copy the error message into a std::string.
    //std::wstring message(messageBuffer, size);
    std::string message;
    for (int i = 0; i < size; ++i)
    {
        message.push_back(messageBuffer[i]);
    }

    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);

    return message;
}
#endif // !BILL_WINDOWS