#include "FrameworkPCH.h"
#include "Utilities.h"

DECLARE_LOG_CATEGORY(LogUtils);

/*
* Loads a file and returns the contents - Referenced from old framework
*/
char* Utilities::LoadCompleteFile(const char* filename, long* length /*= nullptr*/)
{
    char* filecontents = nullptr;

    FILE* filehandle;
    errno_t error = fopen_s(&filehandle, filename, "rb");

    if (filehandle)
    {
        LOG_MESSAGE(LogUtils, LogVerbosity::Success, "File Opened");
        fseek(filehandle, 0, SEEK_END);
        long size = ftell(filehandle);
        rewind(filehandle);

        filecontents = new char[size + 1];
        fread(filecontents, size, 1, filehandle);
        filecontents[size] = 0;

        if (length)
            *length = size;

        fclose(filehandle);

        return filecontents;
    }
    LOG_MESSAGE(LogUtils, LogVerbosity::Error, "File failed to open file");
    return nullptr;
}

/*
*   Loads a file from a given name and prefixes the Data folder path
*/
char* Utilities::LoadCompleteFileFromData(const char* filename, long* length/*= nullptr*/)
{
#ifdef DEBUG
    std::string full_path = "../Source/Data/";
#else
    std::string full_path = "Data/";
#endif
    full_path.append(filename);
    return LoadCompleteFile(full_path.c_str(), length);
}
