#ifndef AT_ATX_DB_H_
#define AT_ATX_DB_H_

#include <sqlite3.h>

#define DB_FILE "/home/blitzwolf/workstation/blitz/alpha/users.db"

namespace atx {

class userdb {
public:
  userdb() = delete;
  userdb(std::string filename, int mode=0);
  ~userdb();
private:
  std::string _filename;
  sqlite3 *_db;
};






} // namespace atx

#endif


/*

  Create Table

CREATE TABLE userdata (
	first_name TEXT NOT NULL,
	last_name TEXT NOT NULL,
	email TEXT NOT NULL UNIQUE,
  username TEXT NOT NULL UNIQUE,
	password TEXT NOT NULL UNIQUE
);

*/