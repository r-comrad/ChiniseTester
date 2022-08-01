#ifndef BASE_PROCESS_HPP
#define BASE_PROCESS_HPP

//--------------------------------------------------------------------------------

#include <optional>

#include "domain/string.hpp"
#include "domain/pair.hpp"
#include "database/submission_info.hpp"

//--------------------------------------------------------------------------------

namespace proc
{
    class BaseProcess
    {
        static const uint64_t MAX_TIME_LIMIT = 5000;
        static const uint64_t MAX_MEMORY_LIMIT = 5000;

    public:
        /*
        \brief Base process constructor that initialize time and memory 
            usage limits for child process.
            (all child process have max time and memory usage limits
            that defined in MAX_TIME_LIMIT and MAX_MEMORY_LIMIT)
        */
        BaseProcess() noexcept;
        virtual ~BaseProcess() = default;

        BaseProcess(const BaseProcess& other) noexcept = default;
        BaseProcess& operator=(const BaseProcess& other) noexcept = default;

        BaseProcess(BaseProcess&& other) noexcept = default;
        BaseProcess& operator=(BaseProcess&& other) noexcept = default;

        virtual void setComand(dom::CharArrayTable&& aParameters) 
            noexcept = 0;
        
        /*
        \brief Create a child process with the specified parameters.
        */
        virtual void create() noexcept = 0;

        /*
        \brief Sets time and memory usage limits.
        \param aTimeMemLimits Child process maximum time usage and 
            process maximum memory usage.
        */
        void setLimits(const data::Limits& aTimeMemLimits) noexcept;

        /*
        \brief Executing the child process without time and memory 
            usage evaluation.
        \return Returns true if the process is completed successfully.
        */
        virtual bool run() noexcept = 0;

        /*
        \brief Executing the child process with time and memory 
            usage evaluation.
        \return Returns the time and memory used by the process if 
            the process is completed successfully.
        */

        virtual std::optional<dom::Pair<uint64_t>> runWithLimits() 
            noexcept = 0;

        virtual void writeData(const std::string& aMessage) noexcept = 0;
        virtual void readData(std::string& aMessage) noexcept = 0;

    protected:
        uint64_t mTimeLimit;
        uint64_t mMemoryLimit;

        virtual void IORedirection() noexcept = 0;
    };

}

//--------------------------------------------------------------------------------

#endif // !BASE_PROCESS_HPP