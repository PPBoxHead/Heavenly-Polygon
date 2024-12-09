#include "file_system.h"


// Get the project working directory path
char* FS_working_directory_get_path(void) {
    char* buffer = _getcwd(NULL, 0);
    console_print(C_INFO, "Fetching current working directory");
    if (buffer == NULL) {
        console_print(C_ERROR, "Failed to fetch current working directory");
    }
    return buffer;
}
// Set the project working directory path
void FS_working_directory_set_path(const char* dir_path) {
    console_print(C_INFO, "Setting working directory to path: %s", dir_path);
    if (_chdir(dir_path) != 0) {
        console_print(C_ERROR, "Failed to set working directory to path: %s", dir_path);
        exit(EXIT_FAILURE);
    }
    if (_chdir(dir_path) == 0) {
        console_print(C_INFO, "Working directory set to path: %s", dir_path);
    }
}

// Get the executable file <file.exe> directory path
char* FS_executable_get_path(void) {
    char* exe_file = _executable_get_file();
    if (!exe_file) {
        return NULL;
    }

    char* last_slash = strrchr(exe_file, '\\');
    if (last_slash) {
        *last_slash = '\0';  // Truncate the string at the last slash
    }

    console_print(C_INFO, "Executable directory at path: %s", exe_file);
    return exe_file;  // Remember to free this buffer when done
}

// Create a directory at specified <dir_path>
bool FS_directory_create(const char* dir_path) {
    if (mkdir(dir_path
#if !defined(_WIN32) && !defined(_WIN64)
        , 0755 // Permissions for POSIX
#endif
    ) == 0) {
        return true; // Success
    } else {
        fprintf(stderr, "Failed to create directory at path: %s\n", dir_path);
        return false; // Failure
    }
}

// Returns a buffer of text inside a file specified at <file_path>
char* FS_file_get_buffer(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        console_print(C_ERROR, "Failed to open file at path: %s", file_path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    if (length < 0) {
        console_print(C_ERROR, "Failed to determine file length: %s", file_path);
        fclose(file);
        return NULL;
    }
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        console_print(C_ERROR, "Failed to allocate memory for file buffer: %s", file_path);
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, length, file);
    if (read_size != length) {
        console_print(C_ERROR, "Failed to read the entire file: %s", file_path);
        free(buffer);
        fclose(file);
        return NULL;
    }
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

// Open File Explorer at specified <path>
void FS_file_explorer_open(const char* path) {
    const char* directory = (path && *path) ? path : ".";
    ShellExecuteA(NULL, "open", directory, NULL, NULL, SW_SHOWDEFAULT);
}

// Convert <str> to lower_case
char* FS_to_lower_case(const char* str) {
    char* lower_str = strdup(str);
    if (lower_str) {
        for (char* p = lower_str; *p; ++p) {
            *p = (char)tolower(*p);
        }
    }
    return lower_str;
}
// Convert <str> to UPPER_CASE
char* FS_to_upper_case(const char* str) {
    char* upper_str = strdup(str);
    if (upper_str) {
        for (char* p = upper_str; *p; ++p) {
            *p = (char)toupper(*p);
        }
    }
    return upper_str;
}
