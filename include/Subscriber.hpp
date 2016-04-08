#pragma once

#include <Core/MW/CoreNode.hpp>
#include <Core/MW/Subscriber.hpp>
#include <Core/HW/GPIO.hpp>

#include <common_msgs/Led.hpp>
#include <led/SubscriberConfiguration.hpp>

namespace led {
	class Subscriber:
		public Core::MW::CoreNode
	{
public:
		Subscriber(
				const char*                    name,
				Core::MW::Thread::PriorityEnum priority = Core::MW::Thread::PriorityEnum::NORMAL
		);
		virtual
		~Subscriber();

public:
		SubscriberConfiguration configuration;

private:
		bool
		onPrepareMW();

		bool
		onLoop();


private:
		static bool
		ledCallback_(
				const common_msgs::Led& msg,
				Core::MW::Node*         node
		);

		bool
		ledCallback(
				const common_msgs::Led& msg
		);


private:
		Core::MW::Subscriber<common_msgs::Led, 5> _subscriber;
	};
}
