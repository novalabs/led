/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <led/Publisher.hpp>

#include <Core/MW/Middleware.hpp>
#include <Core/MW/common.hpp>

namespace led {
   Publisher::Publisher(
      const char*                    name,
      Core::MW::Thread::PriorityEnum priority
   ) :
      CoreNode::CoreNode(name, priority),
      _toggle(0)
   {
      _workingAreaSize = 512;
   }

   Publisher::~Publisher()
   {
      teardown();
   }

   bool
   Publisher::onPrepareMW()
   {
      this->advertise(_publisher, configuration.topic);

      return true;
   }

   inline bool
   Publisher::onLoop()
   {
      common_msgs::Led* msgp;

      if (_publisher.alloc(msgp)) {
         msgp->led   = configuration.led;
         msgp->value = _toggle;
         _toggle    ^= 1;

         if (!_publisher.publish(*msgp)) {
            return false;
         }
      }

      Core::MW::Thread::sleep(Core::MW::Time::ms(500));

      return true;
   } // Publisher::onLoop
}
