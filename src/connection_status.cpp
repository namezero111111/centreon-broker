/*
** connection_status.cpp for CentreonBroker in ./src
** 
** Made by Matthieu Kermagoret <mkermagoret@merethis.com>
** 
** Copyright Merethis
** See LICENSE file for details.
** 
** Started on  05/22/09 Matthieu Kermagoret
** Last update 06/16/09 Matthieu Kermagoret
*/

#include <cstring>
#include "connection_status.h"

using namespace CentreonBroker;

/**************************************
*                                     *
*          Private Methods            *
*                                     *
**************************************/

/**
 *  Copy all internal data of the ConnectionStatus object to the current
 *  instance.
 */
void ConnectionStatus::InternalCopy(const ConnectionStatus& cs) throw ()
{
  memcpy(this->ints_, cs.ints_, sizeof(this->ints_));
  memcpy(this->timets_, cs.timets_, sizeof(this->timets_));
  return ;
}

/**************************************
*                                     *
*           Public Methods            *
*                                     *
**************************************/

/**
 *  ConnectionStatus default constructor.
 */
ConnectionStatus::ConnectionStatus() throw ()
{
  memset(this->ints_, 0, sizeof(this->ints_));
  memset(this->timets_, 0, sizeof(this->timets_));
}

/**
 *  ConnectionStatus copy constructor.
 */
ConnectionStatus::ConnectionStatus(const ConnectionStatus& cs) throw ()
  : Event(cs)
{
  this->InternalCopy(cs);
}

/**
 *  ConnectionStatus destructor.
 */
ConnectionStatus::~ConnectionStatus() throw ()
{
}

/**
 *  ConnectionStatus operator= overload.
 */
ConnectionStatus& ConnectionStatus::operator=(const ConnectionStatus& cs)
  throw ()
{
  this->Event::operator=(cs);
  this->InternalCopy(cs);
  return (*this);
}

/**
 *  Get the bytes_processed member.
 */
int ConnectionStatus::GetBytesProcessed() const throw ()
{
  return (this->ints_[BYTES_PROCESSED]);
}

/**
 *  Get the data_end_time member.
 */
time_t ConnectionStatus::GetDataEndTime() const throw ()
{
  return (this->timets_[DATA_END_TIME]);
}

/**
 *  Get the disconnect_time member.
 */
time_t ConnectionStatus::GetDisconnectTime() const throw ()
{
  return (this->timets_[DISCONNECT_TIME]);
}

/**
 *  Get the entries_processed member.
 */
int ConnectionStatus::GetEntriesProcessed() const throw ()
{
  return (this->ints_[ENTRIES_PROCESSED]);
}

/**
 *  Get the last_checkin_time member.
 */
time_t ConnectionStatus::GetLastCheckinTime() const throw ()
{
  return (this->timets_[LAST_CHECKIN_TIME]);
}

/**
 *  Get the lines_processed member.
 */
int ConnectionStatus::GetLinesProcessed() const throw ()
{
  return (this->ints_[LINES_PROCESSED]);
}

/**
 *  Get the type member.
 */
int ConnectionStatus::GetType() const throw ()
{
  return (Event::CONNECTIONSTATUS);
}

/**
 *  Set the bytes_processed member.
 */
void ConnectionStatus::SetBytesProcessed(int bp) throw ()
{
  this->ints_[BYTES_PROCESSED] = bp;
  return ;
}

/**
 *  Set the data_end_time member.
 */
void ConnectionStatus::SetDataEndTime(time_t det) throw ()
{
  this->timets_[DATA_END_TIME] = det;
  return ;
}

/**
 *  Set the disconnect_time member.
 */
void ConnectionStatus::SetDisconnectTime(time_t dt) throw ()
{
  this->timets_[DISCONNECT_TIME] = dt;
  return ;
}

/**
 *  Set the entries_processed member.
 */
void ConnectionStatus::SetEntriesProcessed(int ep) throw ()
{
  this->ints_[ENTRIES_PROCESSED] = ep;
  return ;
}

/**
 *  Set the last_checkin_time member.
 */
void ConnectionStatus::SetLastCheckinTime(time_t lct) throw ()
{
  this->timets_[LAST_CHECKIN_TIME] = lct;
  return ;
}

/**
 *  Set the lines_processed member.
 */
void ConnectionStatus::SetLinesProcessed(int lp) throw ()
{
  this->ints_[LINES_PROCESSED] = lp;
  return ;
}
