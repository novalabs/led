#pragma once

#include <Core/MW/CoreNode.hpp>
#include <Core/MW/Publisher.hpp>

#include <common_msgs/Led.hpp>
#include <led/PublisherConfiguration.hpp>

#include <array>

namespace led {
	class Publisher:
		public Core::MW::CoreNode
	{
public:
		Publisher(
				const char*                    name,
				Core::MW::Thread::PriorityEnum priority = Core::MW::Thread::PriorityEnum::NORMAL
		);
		virtual
		~Publisher();

public:
		PublisherConfiguration configuration;

private:
		Core::MW::Publisher<common_msgs::Led> _publisher;

private:
		uint32_t _toggle;

private:
		bool
		onPrepareMW();

		bool
		onLoop();
	};
}
