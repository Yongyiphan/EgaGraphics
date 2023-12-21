#pragma once

namespace Core {

				class RenderStat : public ISingleton<RenderStat> {

				public:
								enum class StatType {
												ModelCalls,
												DrawCalls,
								};
								static std::string RenderStatToString(StatType);

								void Reset();
								inline std::map<StatType, int>& GetTrackList() { return m_TrackList; }
								int& operator[](StatType m_Stat);

				private:
								std::map<StatType, int> m_TrackList;
				};
}
