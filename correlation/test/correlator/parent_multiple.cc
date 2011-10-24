/*
** Copyright 2011 Merethis
**
** This file is part of Centreon Broker.
**
** Centreon Broker is free software: you can redistribute it and/or
** modify it under the terms of the GNU General Public License version 2
** as published by the Free Software Foundation.
**
** Centreon Broker is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Centreon Broker. If not, see
** <http://www.gnu.org/licenses/>.
*/

#include <QMap>
#include <QPair>
#include "com/centreon/broker/config/applier/init.hh"
#include "com/centreon/broker/correlation/correlator.hh"
#include "com/centreon/broker/correlation/issue.hh"
#include "com/centreon/broker/correlation/issue_parent.hh"
#include "com/centreon/broker/correlation/node.hh"
#include "com/centreon/broker/neb/service_status.hh"
#include "test/correlator/common.hh"

using namespace com::centreon::broker;
using namespace com::centreon::broker::correlation;

/**
 *  Check that parenting work.
 *
 *  @return 0 on success.
 */
int main() {
  // Initialization.
  config::applier::init();

  // Create state.
  QMap<QPair<unsigned int, unsigned int>, node> state;
  node& n1(state[qMakePair(42u, 24u)]);
  n1.host_id = 42;
  n1.service_id = 24;
  n1.state = 0;
  node& n2(state[qMakePair(56u, 13u)]);
  n2.host_id = 56;
  n2.service_id = 13u;
  n2.state = 0;
  node& n3(state[qMakePair(90u, 42u)]);
  n3.host_id = 90;
  n3.service_id = 42u;
  n3.state = 0;
  node& n4(state[qMakePair(213u, 8u)]);
  n4.host_id = 213;
  n4.service_id = 8u;
  n4.state = 0;
  n1.add_parent(&n2);
  n1.add_parent(&n3);
  n1.add_parent(&n4);

  // Create correlator and apply state.
  correlator c;
  c.set_state(state);

  // Send node status.
  {
    QSharedPointer<neb::service_status> ss(new neb::service_status);
    ss->host_id = 56;
    ss->service_id = 13;
    ss->state_type = 1;
    ss->current_state = 2;
    c.write(ss);
  }
  {
    QSharedPointer<neb::service_status> ss(new neb::service_status);
    ss->host_id = 90;
    ss->service_id = 42;
    ss->state_type = 1;
    ss->current_state = 2;
    c.write(ss);
  }
  {
    QSharedPointer<neb::service_status> ss(new neb::service_status);
    ss->host_id = 42;
    ss->service_id = 24;
    ss->state_type = 1;
    ss->current_state = 2;
    c.write(ss);
  }
  {
    QSharedPointer<neb::service_status> ss(new neb::service_status);
    ss->host_id = 213;
    ss->service_id = 8;
    ss->state_type = 1;
    ss->current_state = 2;
    c.write(ss);
  }
  {
    QSharedPointer<neb::service_status> ss(new neb::service_status);
    ss->host_id = 56;
    ss->service_id = 13;
    ss->state_type = 1;
    ss->current_state = 0;
    c.write(ss);
  }
  {
    QSharedPointer<neb::service_status> ss(new neb::service_status);
    ss->host_id = 42;
    ss->service_id = 24;
    ss->state_type = 1;
    ss->current_state = 0;
    c.write(ss);
  }
  {
    QSharedPointer<neb::service_status> ss(new neb::service_status);
    ss->host_id = 90;
    ss->service_id = 42;
    ss->state_type = 1;
    ss->current_state = 0;
    c.write(ss);
  }
  {
    QSharedPointer<neb::service_status> ss(new neb::service_status);
    ss->host_id = 213;
    ss->service_id = 8;
    ss->state_type = 1;
    ss->current_state = 0;
    c.write(ss);
  }

  // Check correlation content.
  QList<QSharedPointer<io::data> > content;
  add_issue(content, 0, 0, 56, 13, 1);
  add_issue(content, 0, 0, 90, 42, 1);
  add_issue(content, 0, 0, 42, 24, 1);
  add_issue(content, 0, 0, 213, 8, 1);
  add_issue_parent(content, 42, 24, 1, 0, 56, 13, 1, 1);
  add_issue_parent(content, 42, 24, 1, 0, 90, 42, 1, 1);
  add_issue_parent(content, 42, 24, 1, 0, 213, 8, 1, 1);
  add_issue_parent(content, 42, 24, 1, 1, 56, 13, 1, 1);
  add_issue_parent(content, 42, 24, 1, 1, 90, 42, 1, 1);
  add_issue_parent(content, 42, 24, 1, 1, 213, 8, 1, 1);
  add_issue(content, 0, 1, 56, 13, 1);
  add_issue(content, 0, 1, 42, 24, 1);
  add_issue(content, 0, 1, 90, 42, 1);
  add_issue(content, 0, 1, 213, 8, 1);
  return (!check_content(c, content));
}