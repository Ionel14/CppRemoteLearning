#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace smart_home
{
    
class Message
{
public:
    Message();
    Message(const std::string& text, const std::string& sender, const std::string& date);
    
    std::string text_;
    std::string sender_;
    std::string date_;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar & text_;
        ar & sender_;
        ar & date_;
    }
};

} // namespace smart_home



#endif