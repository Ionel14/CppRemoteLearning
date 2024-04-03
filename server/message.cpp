#include "message.h"

namespace smart_home
{
    Message::Message(){}

    Message::Message(const std::string &text, const std::string &sender, const std::string &date): 
    text_{text}, sender_{sender}, date_{date} {}

} // namespace smart_home