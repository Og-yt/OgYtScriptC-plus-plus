#ifndef CONCURRENCYMODELCODE_HPP
#define CONCURRENCYMODELCODE_HPP

#include <windows.h>
#include <wtypesbase.h>
#include "../../../../ErrorLogic.hpp"
#include "../../../../ErrorMessages/Messages.hpp"

inline bool ConcurrencyModel(DWORD value,
                                COINIT &concurrency_model,
                                LINE line_num,
                                MESSAGE result_text,
                                BUFFER buffer)
{
    switch (value)
    {
        case COINIT_APARTMENTTHREADED:
        case COINIT_MULTITHREADED:
        case COINIT_DISABLE_OLE1DDE:
        case COINIT_SPEED_OVER_MEMORY:
        concurrency_model = static_cast<COINIT>(value);
        return true;

    default:
        TaskSchedulerError::handle_task_code_out_of_range(line_num, result_text, buffer);
        return false;
    }
}

#endif // CONCURRENCYMODELCODE_HPP