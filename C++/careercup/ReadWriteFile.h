#include <Windows.h>
#include <stdio.h>

#define BUFFER_SIZE 4096
#define UNICODE 1

class ReadWriteFile {
   public:
    static int test() {
        HANDLE hFile = CreateFileW(
            L"C:\data\CHT\1e5f53b4\FabricTest\DocDb.test.Data\ScaleMin\80\Applications\SingleServiceMasterServerApplicationOneBox_App0\work\data\ServerService\98c22195-4fe0-4fb6-be75-27767d7a5bc7\133361667974022272\\logrootsegment_3MgUAPivMEI=_98c22195-4fe0-4fb6-be75-27767d7a5bc7.RootMetadata.durable",  // File name
            GENERIC_READ,                    // Access mode
            FILE_SHARE_READ,                 // Share mode
            NULL,                            // Security attributes
            OPEN_EXISTING,                   // Creation disposition
            FILE_FLAG_OVERLAPPED,            // Flags and attributes
            NULL                             // Template file handle
        );

        if (hFile == INVALID_HANDLE_VALUE) {
            perror("Failed to open the file");
            return 1;
        }

        HANDLE hCompletionPort = CreateIoCompletionPort(
            hFile,  // File handle to associate
            NULL,   // Existing completion port (NULL for new)
            0,      // Completion key
            1       // Number of concurrent threads
        );

        if (hCompletionPort == NULL) {
            perror("Failed to create IOCP");
            CloseHandle(hFile);
            return 1;
        }

        char buffer[BUFFER_SIZE];
        OVERLAPPED overlapped = {0};

        DWORD bytesRead;
        BOOL success = ReadFile(
            hFile,           // File handle
            buffer,          // Buffer to read into
            sizeof(buffer),  // Number of bytes to read
            &bytesRead,      // Number of bytes read
            &overlapped      // Overlapped structure for async I/O
        );

        if (!success && GetLastError() != ERROR_IO_PENDING) {
            perror("ReadFile failed");
            CloseHandle(hCompletionPort);
            CloseHandle(hFile);
            return 1;
        }

        DWORD completionKey;
        LPOVERLAPPED pOverlapped;
        DWORD numBytes;

        // Wait for completion or other events
        GetQueuedCompletionStatus(
            hCompletionPort,  // Completion port handle
            &numBytes,        // Number of bytes transferred
            &completionKey,   // Completion key
            &pOverlapped,     // Overlapped structure
            INFINITE          // Timeout (INFINITE for indefinite)
        );

        printf("Read %d bytes: %.*s\n", numBytes, numBytes, buffer);

        CloseHandle(hCompletionPort);
        CloseHandle(hFile);

        return 0;
    }
};