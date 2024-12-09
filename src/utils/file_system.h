#ifndef FILE_SYTEM_H
#define FILE_SYSTEM_H

#include <stdlib.h>
#include <stdbool.h>


#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>   // For ShellExecuteA
    #include <io.h>        // For _access and _findfirst
	#include <direct.h>  // For _mkdir on Windows
	#define mkdir _mkdir
#else
	#include <sys/stat.h> // For mkdir on POSIX
	#include <sys/types.h>
#endif

#include "console_logger.h"

// Get the project working directory path
char* FS_working_directory_get_path(void);
// Set the project working directory path
void FS_working_directory_set_path(const char* dir_path);

// Get the executable file <file.exe> directory path
char* FS_executable_get_path(void);

// Create a directory at specified <dir_path>
bool FS_directory_create(const char* dir_path);

// Returns a buffer of text inside a file specified at <file_path>
char* FS_file_get_buffer(const char* file_path);

// Open File Explorer at specified <path>
void FS_file_explorer_open(const char* path);

// Convert <str> to lower_case
char* FS_to_lower_case(const char* str);
// Convert <str> to UPPER_CASE
char* FS_to_upper_case(const char* str);

// Get the executable file <file.exe> path
static char* _executable_get_file() {
    char* buffer = malloc(MAX_PATH);
    if (!buffer) {
        console_print(C_ERROR, "Memory allocation failed");
        return NULL;
    }

    DWORD length = GetModuleFileNameA(NULL, buffer, MAX_PATH);
    if (length == 0) {
        console_print(C_ERROR, "Failed to get executable file path");
        free(buffer);
        return NULL;
    }

    console_print(C_INFO, "Executable file at path: %s", buffer);
    return buffer;  // Remember to free this buffer when done
}


#endif // !FILE_SYTEM_H
