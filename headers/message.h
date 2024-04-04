#ifndef SMARTHOME_MESSAGE_H_
#define SMARTHOME_MESSAGE_H_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace smarthome {

class Message { 
public: 
  Message() {}
  Message(std::string message, std::string name, std::string date) : message(message), name(name), date(date) {}

  std::string getMessage() {
    return message;
  }

  std::string getName() {
    return name;
  }

  std::string getDate() {
    return date;
  }
  
private: 
  friend class boost::serialization::access;

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version) {
    ar & message;
    ar & name;
    ar & date;
  }

  std::string message;
  std::string name;
  std::string date;
};

} // namespace smarthome
#endif  // SMARTHOME_MESSAGE_H_