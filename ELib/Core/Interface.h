#pragma once


template <typename T>
class ISingleton {

protected:
				ISingleton() = default;
				ISingleton(const ISingleton&) = delete;
				ISingleton(ISingleton&&) = delete;
				ISingleton& operator=(const ISingleton&) = delete;
				ISingleton& operator=(const ISingleton&&) = delete;
				virtual ~ISingleton() = default;
public:
				static T& GetInstance();
};

template <typename T>
T& ISingleton<T>::GetInstance() {
				static T instance{};
				return instance;
}
