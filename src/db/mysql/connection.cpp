/*
** connection.cpp for CentreonBroker in ./src/db/mysql
** 
** Made by Matthieu Kermagoret <mkermagoret@merethis.com>
** 
** Copyright Merethis
** See LICENSE file for details.
** 
** Started on  06/03/09 Matthieu Kermagoret
** Last update 06/11/09 Matthieu Kermagoret
*/

#include <cassert>
#include <mysql.h>
#include "db/db_exception.h"
#include "db/mysql/connection.h"
#include "db/mysql/truncate.h"

using namespace CentreonBroker::DB;

/**************************************
*                                     *
*          Private Methods            *
*                                     *
**************************************/

/**
 *  MySQLConnection copy constructor.
 */
MySQLConnection::MySQLConnection(const MySQLConnection& myconn) throw ()
  : Connection(Connection::MYSQL)
{
  (void)myconn;
  assert(false);
}

/**
 *  MySQLConnection operator= overload.
 */
MySQLConnection& MySQLConnection::operator=(const MySQLConnection& myconn)
  throw ()
{
  (void)myconn;
  assert(false);
  return (*this);
}

/**************************************
*                                     *
*          Public Methods             *
*                                     *
**************************************/

/**
 *  MySQLConnection default constructor.
 */
MySQLConnection::MySQLConnection() throw (DBException)
  : Connection(Connection::MYSQL), myconn_(NULL)
{
  if (mysql_thread_init())
    throw (DBException(0,
                       DBException::INITIALIZATION,
                       "Error while initializing MySQL library"));
}

/**
 *  MySQLConnection destructor.
 */
MySQLConnection::~MySQLConnection() throw ()
{
  if (this->myconn_)
    this->Disconnect();
  mysql_thread_end();
}

/**
 *  Toggle the auto-commit mode of the database.
 */
void MySQLConnection::AutoCommit(bool activate) throw (DBException)
{
  assert(this->myconn_);
  if (mysql_autocommit(this->myconn_, activate))
    throw (DBException(mysql_errno(this->myconn_),
                       DBException::INITIALIZATION,
                       mysql_error(this->myconn_)));
  return ;
}

/**
 *  Commit current transaction to the DB.
 */
void MySQLConnection::Commit() throw (DBException)
{
  assert(this->myconn_);
  if (mysql_commit(this->myconn_))
    throw (DBException(mysql_errno(this->myconn_),
                       DBException::COMMIT,
                       mysql_error(this->myconn_)));
  return ;
}

/**
 *  Connect to the MySQL server.
 */
void MySQLConnection::Connect(const std::string& host,
			      const std::string& user,
			      const std::string& password,
			      const std::string& db)
{
  // Initialize the MYSQL structure.
  this->myconn_ = mysql_init(NULL);
  if (!this->myconn_)
    throw (DBException(mysql_errno(this->myconn_),
                       DBException::INITIALIZATION,
                       mysql_error(this->myconn_)));
  // Connect to the DB server.
  if (!mysql_real_connect(this->myconn_,
			  host.c_str(),
			  user.c_str(),
			  password.c_str(),
			  db.c_str(),
			  0,
			  NULL,
			  CLIENT_FOUND_ROWS))
    throw (DBException(mysql_errno(this->myconn_),
                       DBException::INITIALIZATION,
                       mysql_error(this->myconn_)));
  return ;
}

/**
 *  Disconnect of the MySQL server.
 */
void MySQLConnection::Disconnect() throw ()
{
  assert(this->myconn_);
  mysql_close(this->myconn_);
  this->myconn_ = NULL;
  return ;
}

/**
 *  Return a TRUNCATE query matching the DBMS.
 */
Truncate* MySQLConnection::GetTruncateQuery()
{
  return (new MySQLTruncate(this->myconn_));
}
