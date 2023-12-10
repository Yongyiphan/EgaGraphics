#pragma once
#include <epch.h>


namespace GL_Graphics {


				struct IBufferLayout {
								virtual size_t GetElementCount() = 0;
								virtual size_t GetTotalSize() = 0;
				};

				template <typename T>
				class BufferLayoutElement : public IBufferLayout {
								size_t m_DataSize{ 0 };
								size_t m_SubElementCount{ 0 };
								std::vector<T> m_Data{};
								void GetSpecs();
								std::string m_Name;
				public:
								BufferLayoutElement() { GetSpecs(); }
								BufferLayoutElement(const std::string& p_name) :m_Name(p_name) { GetSpecs(); }
								BufferLayoutElement(const std::string& p_name, std::vector<T> rhs) :m_Data(rhs), m_Name(p_name) { GetSpecs(); }

								inline virtual size_t GetElementCount() override {
												return m_Data.size();
								}

								inline virtual size_t GetTotalSize() override {
												return m_Data.size() * m_DataSize;
								}

								inline std::vector<T>& GetData() { return m_Data; }
								inline std::string GetName() { return m_Name; }

				};

				class BufferData {
								//std::map<std::string, IBufferLayout*> m_Data;
								std::vector<std::shared_ptr<IBufferLayout>>m_Data;
				public:
								BufferData() {}

								template <typename T>
								std::shared_ptr<BufferLayoutElement<T>> GetBufferElement(const std::string& p_name) {
												for (auto& element : m_Data) {
																if (auto converted = std::dynamic_pointer_cast<BufferLayoutElement<T>>(element)) {
																				if (converted->GetName() == p_name) {
																								return converted;
																				}
																}
												}
												return nullptr;
								}

								template <typename T, typename... Args>
								std::shared_ptr<BufferLayoutElement<T>> ConstructBufferElement(const std::string& p_name, Args&&... args) {
												for (auto& existingEle : m_Data) {
																if (auto converted = std::dynamic_pointer_cast<BufferLayoutElement<T>>(existingEle)) {
																				if (converted->GetName() == p_name) {
																								return converted;
																				}
																}
												}
												auto new_element = std::make_shared<BufferLayoutElement<T>>(p_name, std::forward<Args>(args)...);
												m_Data.push_back(new_element);
												return new_element;
								}

				};


				class GLBuffer {
				};
}
