#include "at/atx.h"

#include <unistd.h>

int lg_stat;
unsigned int passwd_tries;

atx::User _user("Emmanuel", "Godwin", "blitz", "emmanuel@titan.org",
                "0xefefef");
int login_opt = 1;

using namespace std;



atx::User::User() {}

atx::User::User(std::string fname, std::string lname, std::string uname,
                std::string email, std::string passwd)
    : _firstname(fname), _lastname(lname), _username(uname), _email(email),
      _password(passwd) {}

ostream &atx::operator<<(ostream &os, atx::User &user) {
  return os << user._firstname << " " << user._lastname << " " << user._email
            << " " << user._username << endl;
}

istream &atx::operator>>(istream &is, atx::User &user) {
  cout << "Firstname: ";
  is >> user._firstname;
  cout << "Lastname: ";
  is >> user._lastname;
  cout << "Email: ";
  is >> user._email;
  cout << "Password: ";
  is >> user._password;

  return is;
}

void atx::User::username(std::string &usrname) {
  _username = std::move(usrname);
}

void atx::User::password(std::string &passwd) { _password = std::move(passwd); }

void atx::timeout() {
  cout << "\x1B[2J\x1B[H";
  cout << "Try again in 10 seconds\n";
  this_thread::sleep_for(std::chrono::duration(std::chrono::seconds(10)));
}

int atx::user_authentication(const User &user) {
  if ((user.username() == "blitz") && user.password() == "0xefefef") {
    cout << "\x1B[2J\x1B[H";
    cout << "Access Granted." << endl;
    cout << "Welcome " << user.username() << endl;
    return PASRHT;
  }

  else {
    cout << "\x1B[2J\x1B[H";
    cout << "Access Denied.\n";
    return PASWRG;
  }
}

int atx::login_user(User &user) {

  std::string uname;
  std::string pwd;

  cout << "Username: ";
  cin >> uname;
  user.username(uname);
  cout << "Password: ";
  cin >> pwd;
  user.password(pwd);

  while ((lg_stat = atx::user_authentication(user)) != PASRHT) {
    // cout << "\x1B[2J\x1B[H";
    ++passwd_tries;
    cout << "Username: ";
    cin >> uname;
    user.username(uname);
    cout << "Password: ";
    cin >> pwd;
    user.password(pwd);

    if (passwd_tries == 3)
      atx::timeout();
    if (lg_stat == PASRHT)
      break;
  }

  return 0;
}

int atx::main_menu() {

  cout << "Welcome to the ATX Group Mainframe." << endl;
  printf("1] Login => (Default)\n2] Sign Up\n");
  cin >> login_opt;

  while (true) {
    switch (login_opt) {
    case 1:
      cout << "\x1B[2J\x1B[H";
      login_user(_user);
      break;
    case 2:
      create_user();
      break;
    case 0x0D:
      login_user(_user);
    default:
      printf("Enter \'1\' or \'2\' to proceed.\n");
      this_thread::sleep_for(chrono::duration(chrono::milliseconds(500)));
      main_menu();
      break;
    }
    break;
  }
  return 0;
}

// implement program options and call validators/auth.
int atx::Main(int argc, char *argv[]) {

  // CLI::App app{"App description"};

  /* std::string filename = "default";
  app.add_option("-f,--file", filename, "A help string");

  CLI11_PARSE(app, argc, argv); */

  main_menu();

  return 0;
}

atx::User *atx::create_user() {

  cout << "\x1B[2J\x1B[H";
  printf("Please fill out this form.\n");

  atx::User *_usr = new User();
  cin >> *_usr;

  return _usr;
}

atx::userdb::userdb(std::string filename, int mode)
    : _filename(filename), _db(nullptr) {
  sqlite3_initialize();
  sqlite3_open_v2(_filename.c_str(), &_db,
                  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
}

atx::userdb::~userdb() {

  sqlite3_close(_db);
  sqlite3_shutdown();
}