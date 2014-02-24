/*
** Copyright 2013 Merethis
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

#include <sstream>
#include "com/centreon/broker/neb/internal.hh"
#include "com/centreon/broker/neb/statistics/hosts_flapping.hh"
#include "com/centreon/engine/globals.hh"

using namespace com::centreon::broker::neb;
using namespace com::centreon::broker::neb::statistics;

/**
 *  Default constructor.
 */
hosts_flapping::hosts_flapping()
  : plugin("hosts_flapping") {}

/**
 *  Copy constructor.
 *
 *  @param[in] right Object to copy.
 */
hosts_flapping::hosts_flapping(hosts_flapping const& right)
 : plugin(right) {

}

/**
 *  Destructor.
 */
hosts_flapping::~hosts_flapping() {}

/**
 *  Assignment operator.
 *
 *  @param[in] right Object to copy.
 *
 *  @return This object.
 */
hosts_flapping& hosts_flapping::operator=(hosts_flapping const& right) {
  plugin::operator=(right);
  return (*this);
}

/**
 *  Get statistics.
 *
 *  @param[out] output   The output return by the plugin.
 *  @param[out] perfdata The perf data return by the plugin.
 */
void hosts_flapping::run(
              std::string& output,
	      std::string& perfdata) {
  // Count hosts are flapping.
  unsigned int total(0);
  for (host* h(host_list); h; h = h->next)
    if (h->is_flapping)
      ++total;

  // Output.
  std::ostringstream oss;
  oss << "Engine " << instance_name.toStdString()
      << " has " << total << " flapping hosts";
  output = oss.str();

  // Perfdata.
  oss.str("");
  oss << "hosts_flapping=" << total;
  perfdata = oss.str();

  return ;
}