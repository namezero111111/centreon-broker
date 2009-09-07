/*
**  Copyright 2009 MERETHIS
**  This file is part of CentreonBroker.
**
**  CentreonBroker is free software: you can redistribute it and/or modify it
**  under the terms of the GNU General Public License as published by the Free
**  Software Foundation, either version 2 of the License, or (at your option)
**  any later version.
**
**  CentreonBroker is distributed in the hope that it will be useful, but
**  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
**  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
**  for more details.
**
**  You should have received a copy of the GNU General Public License along
**  with CentreonBroker.  If not, see <http://www.gnu.org/licenses/>.
**
**  For more information : contact@centreon.com
*/

#ifndef SENDER_H_
# define SENDER_H_

# include <boost/thread.hpp>
# include <list>
# include "waitable_list.hpp"

namespace                  CentreonBroker
{
  // Forward declarations
  class                    DBuffer;
  namespace                IO
  { class                  Stream; }

  /**
   *  \class Sender sender.h "sender.h"
   *  \brief Thread sending data to some outputs.
   *
   *  When used in cbmod, the Sender object will handle all output objects and
   *  send them the data generated by Nagios.
   */
  class                    Sender
  {
   private:
    WaitableList<DBuffer>  data_;
    volatile bool          exit_;
    std::list<IO::Stream*> outputs_;
    boost::thread*         thread_;
    void                   InternalCopy(const Sender& sender);

   public:
                           Sender();
                           Sender(const Sender& sender);
                           ~Sender();
    Sender&                operator=(const Sender& sender);
    void                   operator()();
    void                   AddData(DBuffer* dbuffer);
    void                   AddOutput(IO::Stream* output);
    void                   Run();
    void                   Stop();
  };
}

#endif /* !SENDER_H_ */
