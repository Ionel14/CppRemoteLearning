#include "message.h"

namespace smartHome {
    
    Message::Message(const std::string& text, const std::string& senderName) : text(text), senderName(senderName) {
        // Get current date and time
        std::time_t now = std::time(0);
        std::tm* currentTime = std::localtime(&now);
        char buffer[80];
        std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", currentTime);
        currentDate = buffer;
    }

    // Default constructor required for serialization
    Message::Message() {}

    // Getters
    std::string Message::getText() const {
        return text;
    }

    std::string Message::getSenderName() const {
        return senderName;
    }

    std::string Message::getCurrentDate() const {
        return currentDate;
    }
}
