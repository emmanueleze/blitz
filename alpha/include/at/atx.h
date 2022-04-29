#ifndef AT_ATX_H_
#define AT_ATX_H_


#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <thread>


#include "atx_db.h"
//#include "at/CLI11.hpp"

extern int lg_stat;
extern unsigned int passwd_tries;


#define PASWRG 1
#define PASRHT 0
#define ACCESS_GRANTED 8
#define ACCESS_DENIED 4

namespace atx {

class User;

std::ostream& operator<<(std::ostream &os, User& user);
std::istream& operator>>(std::istream &is, User &user);


void timeout();

class User {
  
  friend std::ostream& operator<<(std::ostream &os, User& user);
  friend std::istream& operator>>(std::istream &is, User &user);
  

public:
  User();
  explicit User(std::string fname, std::string lname, std::string uname, 
    std::string email, std::string passwd);

  std::string username() const { return _username; }
  std::string password() const { return _password; }
  void username(std::string&);
  void password(std::string&);

private:
  std::string _firstname;
  std::string _lastname;
  std::string _username;
  std::string _email;
  std::string _password;
};




int main_menu();
int user_authentication(const User& user);

int login_user(User& user);
User* create_user();





int Main(int, char *argv[]);

} // namespace atx

#endif