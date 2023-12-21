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

class IBaseObject {
private:
				std::string m_Name{};
public:
				IBaseObject() : m_Name() {}
				IBaseObject(const std::string& p_Name) : m_Name(p_Name) {}
				inline void SetName(const std::string& p_name) { m_Name = p_name; }
				inline std::string GetName() { return m_Name; }
				virtual ~IBaseObject() {}
};
