/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <led/Subscriber.hpp>
#include <Module.hpp>

#include <Core/MW/Middleware.hpp>
#include <Core/MW/common.hpp>
#include <Core/HW/GPIO.hpp>

namespace led {
   Subscriber::Subscriber(
      const char*                    name,
      Core::MW::Thread::PriorityEnum priority
   ) :
      CoreNode::CoreNode(name, priority)
   {
      _workingAreaSize = 512;
   }

   Subscriber::~Subscriber()
   {
      teardown();
   }

   bool
   Subscriber::onPrepareMW()
   {
      _subscriber.set_callback(Subscriber::ledCallback_);
      this->subscribe(_subscriber, configuration.topic);

      return true;
   }

   inline bool
   Subscriber::onLoop()
   {
      if (!this->spin(Configuration::SUBSCRIBER_SPIN_TIME)) {
         Module::led.toggle();
      }

      return true;
   }

   bool
   Subscriber::ledCallback_(
      const common_msgs::Led& msg,
      Core::MW::Node*         node
   )
   {
      Subscriber* tmp = static_cast<Subscriber*>(node);

      return tmp->ledCallback(msg);
   }

   bool
   Subscriber::ledCallback(
      const common_msgs::Led& msg
   )
   {
      Module::led.write(msg.value);

      return true;
   }
}
