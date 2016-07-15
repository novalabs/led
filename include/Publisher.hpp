/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <core/mw/CoreNode.hpp>
#include <core/mw/Publisher.hpp>

#include <core/common_msgs/Led.hpp>
#include <core/led/PublisherConfiguration.hpp>

namespace core {
namespace led {
class Publisher:
   public core::mw::CoreNode,
   public core::mw::CoreConfigurable<PublisherConfiguration>
{
public:
   Publisher(
      const char*                name,
      core::os::Thread::Priority priority = core::os::Thread::PriorityEnum::NORMAL
   );
   virtual
   ~Publisher();

// Publishers and subscribers

private:
   core::mw::Publisher<common_msgs::Led> _publisher;

// Node data and functions

private:
   uint32_t _toggle;

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
