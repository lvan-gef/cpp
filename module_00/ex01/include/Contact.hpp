#ifndef Contact_h
#define Contact_h

#include <string>

class Contact {
public:
  Contact(void);

  void setFirstName(const std::string &firstName);
  void setLastName(const std::string &lastName);
  void setNickName(const std::string &nickName);
  void setPhoneNumber(const std::string &phoneNumber);
  void setSecret(const std::string &secret);

  void clearContact(void);

  std::string getFirstName(void);
  std::string getLastName(void);
  std::string getNickName(void);
  std::string getPhoneNumber(void);
  std::string getSecret(void);

  ~Contact(void);

private:
  std::string _firstName;
  std::string _lastName;
  std::string _nickName;
  std::string _phoneNumber;
  std::string _secret;
};
#endif
