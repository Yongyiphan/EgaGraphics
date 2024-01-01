#pragma once
#include <epch.h>
#include <functional>
#include "Interface.h"


namespace Core {
				using EventName = std::string;
				using EventID = size_t;

				struct IEvent {
								virtual const std::string& getName() const = 0;
								virtual ~IEvent() {}
				};

				template <typename ... Args>
				class Event : public IEvent {
				public:
								using _callback = std::function<void(Args...)>;
								explicit Event(const std::string& name, const _callback& cb) : _name(name), _cbFunc(cb) {}
								~Event() {}
								virtual const std::string& getName() const override { return _name; }

								void trigger(Args... args) { _cbFunc(args...); }
				private:
								EventName _name;
								_callback const _cbFunc;


				};

				class EventDispatcher : public ISingleton<EventDispatcher> {
				public:
								EventDispatcher() {}
								~EventDispatcher();

								void RegisterEvent(IEvent* newEvent);

								template<typename... Args>
								void DispatchEvent(const std::string& name, Args... args) {
												auto iter = m_EventList.find(name);
												if (iter == m_EventList.end()) {
																return;
												}
												for (auto _e : iter->second) {
																if (Event<Args...>* event = dynamic_cast<Event<Args...>*>(_e))
																				event->trigger(args...);
												}

								}

				private:
								std::map<std::string, std::vector<IEvent*>> m_EventList;
				};



}
