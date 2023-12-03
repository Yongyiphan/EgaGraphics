#pragma once
#include <epch.h>
#include "Interface.h"


namespace Core {

				template <typename ...Args>
				class EventDispatcher : public ISingleton<EventDispatcher<Args...>> {
				private:


				public:
								static void RegisterEvent(std::string_view)
				};
}
