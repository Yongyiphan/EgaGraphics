#include <epch.h>
#include "Event.h"

namespace Core {
				EventDispatcher::~EventDispatcher() {
								for (auto [e_name, e_list] : m_EventList) {
												for (auto _e : e_list) {
																delete _e;
												}

								}

				}

				void EventDispatcher::RegisterEvent(IEvent* newEvent) {
								if (newEvent) {
												m_EventList[newEvent->getName()].push_back(newEvent);
								}
				}

}
