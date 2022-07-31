#ifndef __SOLID_PLATFORM_EVENT_HPP__
#define __SOLID_PLATFORM_EVENT_HPP__

namespace Solid
{
	namespace Platform
	{
		class EventData {};
		class CreateEventData : public EventData {};
		
		class Event
		{
			public:
				enum EventType
				{
					CREATE,
					DRAW,
					RESIZE,
					DESTROY
				};
				
			private:
				EventType m_event_type;
				EventData* m_data;
		};
	}
}

#endif
