/*
** Copyright 2009-2011 MERETHIS
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
**
** For more information: contact@centreon.com
*/

#ifndef EVENTS_HOST_DEPENDENCY_HH_
# define EVENTS_HOST_DEPENDENCY_HH_

# include "events/dependency.hh"

namespace            events {
  /**
   *  @class host_dependency host_dependency.hh "events/host_dependency.hh"
   *  @brief Host dependency relationship.
   *
   *  Defines a dependency between two hosts.
   */
  class              host_dependency : public dependency {
   public:
                     host_dependency();
                     host_dependency(host_dependency const& hd);
                     ~host_dependency();
    host_dependency& operator=(host_dependency const& hd);
    int              get_type() const;
  };
}

#endif /* !EVENTS_HOST_DEPENDENCY_HH_ */