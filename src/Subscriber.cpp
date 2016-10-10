/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <core/led/Subscriber.hpp>
#include <Module.hpp>

#include <core/mw/Middleware.hpp>
#include <core/common.hpp>
#include <core/hw/GPIO.hpp>

namespace core {
namespace led {
Subscriber::Subscriber(
   const char*                name,
   core::os::Thread::Priority priority
) :
   CoreNode::CoreNode(name, priority),
   CoreConfigurable<SubscriberConfiguration>::CoreConfigurable(name)
{
   _workingAreaSize = 512;
}

Subscriber::~Subscriber()
{
   teardown();
}

bool
Subscriber::onConfigure()
{
   return isConfigured();    // Make sure we have a valid configuration...
}

bool
Subscriber::onPrepareMW()
{
   _subscriber.set_callback(Subscriber::ledCallback_);
   this->subscribe(_subscriber, configuration().topic);

   return true;
}

inline bool
Subscriber::onLoop()
{
   if (!this->spin(ModuleConfiguration::SUBSCRIBER_SPIN_TIME)) {
      Module::led.toggle();
   }

   return true;
}

bool
Subscriber::ledCallback_(
   const core::common_msgs::Led& msg,
   void*                         context
)
{
   Subscriber* tmp = static_cast<Subscriber*>(context);

   return tmp->ledCallback(msg);
}

bool
Subscriber::ledCallback(
   const core::common_msgs::Led& msg
)
{
   Module::led.write(msg.value);

   return true;
}
}
}
