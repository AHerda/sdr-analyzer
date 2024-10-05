#include "utils.hpp"

#include <libairspy/airspy.h>

#include <iostream>

void error(int errCode, const std::string& message) {
    std::cerr << "ERROR:" << std::endl
        << "\t" << message << std::endl;

    switch (errCode)
    {
    case airspy_error::AIRSPY_SUCCESS:
        return;

    case airspy_error::AIRSPY_TRUE:
        return;

    case airspy_error::AIRSPY_ERROR_INVALID_PARAM:
        std::cerr << "\tInvalid parameter" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_NOT_FOUND:
        std::cerr << "\tNot found" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_BUSY:
        std::cerr << "\tBusy" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_NO_MEM:
        std::cerr << "\tNo memory" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_UNSUPPORTED:
        std::cerr << "\tUnsupported" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_LIBUSB:
        std::cerr << "\tLibUSB" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_THREAD:
        std::cerr << "\tThread" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_STREAMING_THREAD_ERR:
        std::cerr << "\tStreaming thread error" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_STREAMING_STOPPED:
        std::cerr << "\tStreaming stopped" << std::endl;
        break;

    case airspy_error::AIRSPY_ERROR_OTHER:
        std::cerr << "\tOther" << std::endl;
        break;

    default:
        std::cerr << "\tUnknown error" << std::endl;
        break;
    }

    throw std::runtime_error(message);
}
