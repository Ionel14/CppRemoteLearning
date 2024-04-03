#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>
#include <ctime>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sstream>

namespace smartHome {
    class Message {
    public:
        Message(const std::string& text, const std::string& senderName);

        // Default constructor required for serialization
        Message();

        // Getters
        std::string getText() const;

        std::string getSenderName() const;

        std::string getCurrentDate() const;

    private:
        std::string text;
        std::string senderName;
        std::string currentDate;

        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version) {
            ar & text;
            ar & senderName;
            ar & currentDate;
        }
    };
}

#endif /* MESSAGE_H */
