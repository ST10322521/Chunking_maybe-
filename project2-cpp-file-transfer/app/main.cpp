#include "file_transfer.h"

#include <iostream>

int main(int argc, char* argv[]) {
    // argc counts arguments, while argv stores each argument as text.
    // Print the available commands when no command was supplied.
    if (argc < 2) {
        std::cout << "Usage:\n"
                  << "  file_transfer_app send-file <file> <transferId> [apiUrl]\n"
                  << "  file_transfer_app rebuild <transferId> <output>\n"
                  << "  file_transfer_app send-stream <streamId> <text> [apiUrl]\n"
                  << "  file_transfer_app server [port]\n";
        return 0;
    }

    // argv[1] is the selected command, such as "send-file" or "server".
    const std::string command = argv[1];

    // argv[4] can override the default C# API URL for sending commands.
    // The default assumes the C# API is running on localhost port 5000.
    const std::string apiUrl = argc > 4 ? argv[4] : "http://localhost:5000";
    // Send a local file from C++ to the C# API.
    if (command == "send-file" && argc >= 4)
        return FileTransfer::SendFile(argv[2], argv[3], apiUrl) ? 0 : 1;
    // Rebuild chunks previously received by this C++ application.
    if (command == "rebuild" && argc >= 4)
        return FileTransfer::RebuildFile(argv[2], argv[3]) ? 0 : 1;
    // Send continuous text data from C++ to the C# API.
    if (command == "send-stream" && argc >= 4)
        return FileTransfer::SendStreamData(argv[2], argv[3], apiUrl) ? 0 : 1;
    // Start the C++ HTTP server for C# -> C++ transfers.
    if (command == "server") {
        // Use port 8080 unless the caller supplies a different port.
        FileTransfer::StartServer(argc >= 3 ? std::stoi(argv[2]) : 8080);
        return 0;
    }

    // Report invalid input instead of silently failing.
    std::cerr << "Invalid command or arguments.\n";
    return 1;
}
