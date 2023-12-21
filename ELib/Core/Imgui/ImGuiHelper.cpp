#include <epch.h>
#include "ImGuiHelper.h"


namespace Core {

				void RenderStat::Reset() {
								for (auto& [m_stattype, m_stat] : m_TrackList) {
												m_stat = 0;
								}
				}

				std::string RenderStat::RenderStatToString(StatType p_type) {
								static std::map<StatType, std::string> stat_string_list{
												{StatType::DrawCalls, "Draw Calls"},
												{StatType::ModelCalls, "Model Calls"},
								};

								return stat_string_list[p_type];
				}

				int& RenderStat::operator[](StatType p_type) {
								return m_TrackList[p_type];
				}
}
