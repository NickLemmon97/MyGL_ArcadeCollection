#include "FrameworkPCH.h"
#include "Utilities.h"
#include <sstream>
#include <fstream>

DECLARE_LOG_CATEGORY(LogUtils);

std::string Utilities::LoadCompleteFile(std::string& filename)
{
    std::stringstream filecontents;
    std::ifstream file;

    try {
        file.open(filename, std::ios::in);

        if (!file.fail())
        {
            filecontents << file.rdbuf();
            file.close();
        }
    }
    catch (std::exception e)
    {
        DEBUG_LOG_MESSAGE(LogUtils, LogVerbosity::Error, "Failed load complete file");
        LOG_MESSAGE(LogUtils, LogVerbosity::Error, e.what());
    }

    return std::move(filecontents.str());
}

/*
*   Loads a file from a given name and prefixes the Data folder path
*/
std::string Utilities::LoadCompleteFileFromData(std::string& filename)
{
    DEBUG_LOG_MESSAGE(LogUtils, LogVerbosity::Warning, "Open file from data path relative to Application Execution");
    std::string full_path = "Data/";
    full_path.append(filename);
    return LoadCompleteFile(full_path);
}
