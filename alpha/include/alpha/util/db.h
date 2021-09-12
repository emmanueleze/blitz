#ifndef BLITZ_ALPHA_INCLUDE_ALPHA_UTIL_DB_H_
#define BLITZ_ALPHA_INCLUDE_ALPHA_UTIL_DB_H_

#include <sqlite3.h>

namespace blitz{
  namespace db{

    /* class Database;
    class DBHandler;
    class CallBack; */
  }
}

/**
  sqlite3* _DB;
  int status;
  char* err_msg;

  string query = "SELECT * FROM PERSON;";
  message("STATE OF THE TABLE BEFORE INSERT.");

  sqlite3_exec(_DB, query.c_str(), callback, NULL, NULL);

  if((status = sqlite3_open("sample.db", &_DB)) ){
    message("error: open DB.", cerr);
    return -1;
  }else{
    message("opened database successfully.");
  }

  std::string sql_create = "CREATE TABLE PERSON("
                      "ID INT PRIMARY KEY     NOT NULL, "
                      "NAME           TEXT    NOT NULL, "
                      "SURNAME          TEXT     NOT NULL, "
                      "AGE            INT     NOT NULL, "
                      "ADDRESS        CHAR(50), "
                      "SALARY         REAL );";

  if((status = sqlite3_exec(_DB, sql_create.c_str(), callback, 0, &err_msg)) != SQLITE_OK){
    message("error: create table.", cerr);
    sqlite3_free(err_msg);
  }else
    message("table created successfully.");

  string sql_ins("INSERT INTO PERSON VALUES(1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0);"
               "INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);"
               "INSERT INTO PERSON VALUES(3, 'PAUL', 'JOBS', 24, 'SEATTLE', 9900.0);");
  
  status = sqlite3_exec(_DB, sql_ins.c_str(), NULL, 0, &err_msg);
  if (status != SQLITE_OK) {
    message("error: INSERT", cerr);
    sqlite3_free(err_msg);
  }else
    message("records created successfully!");

  message("STATE OF TABLE AFTER INSERT");
  
  sqlite3_exec(_DB, query.c_str(), callback, NULL, NULL);
  
  string sql_del = "DELETE FROM PERSON WHERE ID = 2;";

  if((status = sqlite3_exec(_DB, sql_del.c_str(), NULL, 0, &err_msg)) != SQLITE_OK){
    message("error: DELETE", cerr);
    sqlite3_free(err_msg);
  }else
    message("records deleted successfully.");
  message("STATE OF TABLE AFTER DELETE OF ELEMENT");
  sqlite3_exec(_DB, query.c_str(), callback, NULL, NULL);
  sqlite3_close(_DB);

  */

#endif