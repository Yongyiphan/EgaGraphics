#include <epch.h>
#include "Model.h"



namespace GL_Graphics {

				BufferData CreatePointModel() {
								std::vector<glm::vec3> pos_vtx{ glm::vec3(0.f, 0.f, 1.f) };
								std::vector<glm::vec3> clr_vtx{ glm::vec3(0.5f, 0.5f, 0.f) };

								BufferData BD;
								BD.ConstructBufferElement<glm::vec3>("pos", pos_vtx);
								BD.ConstructBufferElement<glm::vec3>("clr", clr_vtx);
								BD.ConstructIndexBuffer(std::vector<index_type>{ 0 });
								return BD;
				}

				BufferData CreateLineModel() {
								std::vector<glm::vec3> pos_vtx{
												glm::vec3(0.f, 0.f, 1.f),
												glm::vec3(1.f, 0.f, 1.f)
								};
								std::vector<glm::vec3> clr_vtx{
												glm::vec3(0.5f, 0.5f, 0.f),
												glm::vec3(0.5f, 0.5f, 0.f)
								};

								BufferData BD;
								BD.ConstructBufferElement<glm::vec3>("pos", pos_vtx);
								BD.ConstructBufferElement<glm::vec3>("clr", clr_vtx);
								BD.ConstructIndexBuffer(std::vector<index_type>{ 0, 1 });
								return BD;
				}
				BufferData CreateQuadModel(bool hollow) {
								/*
								//VERY IMPORTANT FOR CONSISTENCY//
									idx	   coor			tex
								0   2 | -x+y   +x+y | 01   11
									c          c           c
								1   3 | -x-y   +x-y | 00   10
								*/

								std::vector<glm::vec3> pos_vtx, clr_vtx;
								std::vector<glm::vec2> tex_vtx;
								std::vector<index_type> idx_vtx;
								pos_vtx.reserve(4);
								clr_vtx.reserve(4);
								tex_vtx.reserve(4);

								pos_vtx = {
												glm::vec3{-1.0f,  1.0f, 1.f},  // [0] - tl
												glm::vec3{-1.0f, -1.0f, 1.f},  // [1] - bl
												glm::vec3{ 1.0f,  1.0f, 1.f},  // [2] - tr
												glm::vec3{ 1.0f, -1.0f, 1.f}   // [3] - br
								};

								glm::vec3 defaultclr(1.f, 1.f, 1.f);
								clr_vtx = {
										defaultclr,	defaultclr,
										defaultclr,	defaultclr
								};

								for (auto pos : pos_vtx) {
												glm::vec2 uv;
												uv.x = (pos.x + 1.0f) / 2.0f;
												uv.y = (pos.y + 1.0f) / 2.0f;
												tex_vtx.push_back(uv);
								}


								BufferData BD{};
								if (hollow) {
												idx_vtx = { 0, 2, 3, 1, 0 };
												BD.SetPrimitive(GL_LINE_STRIP);
								}
								else {
												idx_vtx = { 0, 1, 2, 3 };
												BD.SetPrimitive(GL_TRIANGLE_STRIP);
								}

								BD.ConstructBufferElement<glm::vec3>("pos", pos_vtx);
								BD.ConstructBufferElement<glm::vec3>("clr", clr_vtx);
								BD.ConstructBufferElement<glm::vec2>("tex", tex_vtx);
								BD.ConstructIndexBuffer(idx_vtx);
								BD.Resize();
								return BD;
				}

				BufferData CreateCircleModel(size_t points, bool hollow) {
								std::vector<glm::vec3> pos_vtx{};
								std::vector<glm::vec3> clr_vtx{};
								std::vector<glm::vec2> tex_vtx{};
								std::vector<index_type> idx_vtx{};
								// Points may get too large, reserve space first
								pos_vtx.reserve(points + 1);
								clr_vtx.reserve(points + 1);
								tex_vtx.reserve(points + 1);

								// Angle of the tip of the triangle towards center
								float interval = 360.f / static_cast<float>(points);
								interval = glm::radians(interval);

								// Center circle
								// v[0]
								glm::vec3 clr{ 0.f, 1.f, 1.f };
								auto NormUV = [](const glm::vec2& uv) -> glm::vec2 {
												glm::vec2 newuv{};
												newuv.x = (uv.x + 1.0f) / 2.0f;
												newuv.y = (uv.y + 1.0f) / 2.0f;
												return newuv;
												};

								float angle{ 0.f };
								BufferData BD;
								if (hollow) {
												for (unsigned int i{}; i < points; i++) {
																glm::vec2 uv(std::cosf(angle), std::sinf(angle));
																pos_vtx.push_back(glm::vec3(uv.x, uv.y, 0.f));
																tex_vtx.push_back(NormUV(uv));
																clr_vtx.push_back(clr);
																idx_vtx.push_back(static_cast<index_type>(i));
																angle += interval;
												}
												idx_vtx.push_back(0);
												BD.SetPrimitive(GL_LINE_STRIP);
								}
								else {
												pos_vtx.push_back({ 0.f, 0.f, 0.f });
												tex_vtx.push_back(NormUV({ 0.f, 0.f }));
												clr_vtx.push_back(clr);
												idx_vtx.reserve(points * 3);
												for (int i{ 1 }; i < points + 1; i++) {
																glm::vec2 uv(std::cosf(angle), std::sinf(angle));
																pos_vtx.push_back(glm::vec3(uv.x, uv.y, 0.f));
																uv.x = (uv.x + 1.0f) / 2.0f;
																uv.y = (uv.y + 1.0f) / 2.0f;
																tex_vtx.push_back(uv);
																clr_vtx.push_back(clr);
																idx_vtx.push_back(0);
																idx_vtx.push_back(static_cast<index_type>(i));
																// Loops back last v point to v[1]
																idx_vtx.push_back((i == points) ? 1 : (static_cast<index_type>(i + 1)));

																angle += interval;
												}
												BD.SetPrimitive(GL_TRIANGLE_FAN);
								}


								BD.ConstructBufferElement<glm::vec3>("pos", pos_vtx);
								BD.ConstructBufferElement<glm::vec3>("clr", clr_vtx);
								BD.ConstructBufferElement<glm::vec2>("tex", tex_vtx);
								BD.ConstructIndexBuffer(idx_vtx);
								return BD;
				}


				BufferData CreateTextModel(ECS::TransformComponent* transc_ptr, ECS::TextComponent* textc_ptr) {

								BufferData BD;
								return BD;
				}
}