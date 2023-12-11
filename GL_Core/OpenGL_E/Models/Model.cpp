#include <epch.h>
#include "Model.h"



namespace GL_Graphics {

				BufferData CreatePointModel() {
								std::vector<glm::vec3> pos_vtx{ glm::vec3(0.f, 0.f, 1.f) };
								std::vector<glm::vec3> clr_vtx{ glm::vec3(0.5f, 0.5f, 0.f) };

								BufferData BD;
								BD.ConstructBufferElement<glm::vec3>("pos", pos_vtx);
								BD.ConstructBufferElement<glm::vec3>("clr", clr_vtx);
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
								std::vector<unsigned int> idx_vtx;
								pos_vtx.reserve(4);
								clr_vtx.reserve(4);
								tex_vtx.reserve(4);

								pos_vtx = {
												glm::vec3{-1.0f,  1.0f, 0.f},  // [0] - tl
												glm::vec3{-1.0f, -1.0f, 0.f},  // [1] - bl
												glm::vec3{ 1.0f,  1.0f, 0.f},  // [2] - tr
												glm::vec3{ 1.0f, -1.0f, 0.f}   // [3] - br
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


								if (hollow) {
												idx_vtx = { 0, 2, 3, 1, 0 };
								}
								else {
												idx_vtx = { 0, 1, 2, 3 };
								}

								BufferData BD;
								BD.ConstructBufferElement<glm::vec3>("pos", pos_vtx);
								BD.ConstructBufferElement<glm::vec3>("clr", clr_vtx);
								BD.ConstructBufferElement<glm::vec2>("tex", tex_vtx);
								BD.Resize();
								return BD;
				}
				BufferData CreateCircleModel(size_t points, bool hollow) {
								BufferData BD;
								return BD;
				}
}