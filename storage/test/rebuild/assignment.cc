/*
** Copyright 2012 Centreon
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** For more information : contact@centreon.com
*/

#include "com/centreon/broker/storage/rebuild.hh"

using namespace com::centreon::broker;

/**
 *  Check that rebuild's assignment operator.
 *
 *  @return 0 on success.
 */
int main() {
  // Base object.
  storage::rebuild r1;
  r1.end = true;
  r1.id = 42;
  r1.is_index = false;

  // Second object.
  storage::rebuild r2;
  r2.end = false;
  r2.id = 234573485;
  r2.is_index = true;

  // Assignment.
  r2 = r1;

  // Reset base object.
  r1.end = false;
  r1.id = 36;
  r1.is_index = true;

  // Check.
  return (r1.end
          || (r1.id != 36)
          || !r1.is_index
          || !r2.end
          || (r2.id != 42)
          || r2.is_index);
}
