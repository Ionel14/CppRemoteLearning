#ifndef NAGARROREMOTELEARNINGSERVER_MESSAGE_H
#define NAGARROREMOTELEARNINGSERVER_MESSAGE_H
#include <string>
#include <boost/date_time.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/access.hpp>

class Message {
public:
    std::string text;
    std::string sender;
    std::string date;

    Message() = default;

    Message(const std::string &text, const std::string &sender, const std::string &date) :
            text(text), sender(sender), date(date) {}

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & text;
        ar & sender;
        ar & date;
    }
};


#endif
