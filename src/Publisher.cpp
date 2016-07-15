/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <core/led/Publisher.hpp>

#include <core/mw/Middleware.hpp>
#include <core/common.hpp>

namespace core {
namespace led {
Publisher::Publisher(
   const char*                name,
   core::os::Thread::Priority priority
) :
   CoreNode::CoreNode(name, priority),
   CoreConfigurable(name),
   _toggle(0)
{
   _workingAreaSize = 512;
}

Publisher::~Publisher()
{
   teardown();
}

bool
Publisher::onConfigure()
{
   return isConfigured();    // Make sure we have a valid configuration...
}

bool
Publisher::onPrepareMW()
{
   this->advertise(_publisher, configuration().topic);

   return true;
}

inline bool
Publisher::onLoop()
{
   common_msgs::Led* msgp;

   if (_publisher.alloc(msgp)) {
      msgp->led   = configuration().led;
      msgp->value = _toggle;
      _toggle    ^= 1;

      if (!_publisher.publish(*msgp)) {
         return false;
      }
   }

   core::os::Thread::sleep(core::os::Time::ms(500));

   return true;
}    // Publisher::onLoop
}
}
