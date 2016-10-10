/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <core/mw/CoreNode.hpp>
#include <core/mw/Subscriber.hpp>

#include <core/common_msgs/Led.hpp>
#include <core/led/SubscriberConfiguration.hpp>

namespace core {
namespace led {
class Subscriber:
   public core::mw::CoreNode,
   public core::mw::CoreConfigurable<SubscriberConfiguration>
{
public:
   Subscriber(
      const char*                name,
      core::os::Thread::Priority priority = core::os::Thread::PriorityEnum::NORMAL
   );
   virtual
   ~Subscriber();

// Publishers and subscribers

private:
   core::mw::Subscriber<common_msgs::Led, 5> _subscriber;

// Node data and functions

private:
   static bool
   ledCallback_(
      const common_msgs::Led& msg,
      void*                   context
   );

   bool
   ledCallback(
      const common_msgs::Led& msg
   );


// CoreNode events to override

private:
   bool
   onConfigure();

   bool
   onPrepareMW();

   bool
   onLoop();
};
}
}
