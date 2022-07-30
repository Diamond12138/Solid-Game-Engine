//It has been abandoned

#ifndef __SOLID_GRAPHICS_RENDERER_HPP__
#define __SOLID_GRAPHICS_RENDERER_HPP__
#include <map>
#include <string>
#include "Program.hpp"
#include "Renderable.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Renderer
		{
			private:
				std::map<std::string,Program&> m_programs;
				
			public:
				Renderer() : m_programs(std::map<std::string,Program&>()) {}
				Renderer(Renderer& from) : m_programs(from.m_programs) {}
				Renderer(std::map<std::string,Program&> programs) : m_programs(programs) {}
				
			public:
				Renderer& setPrograms(std::map<std::string,Program&> programs)
				{
					m_programs = programs;
					return *this;
				}
				std::map<std::string,Program&> getPrograms()
				{
					return m_programs;
				}
				
				Renderer& addProgram(std::string name,Program& program)
								{
									m_programs.insert({name,program});
									return *this;
								}
				Program& getProgram(std::string name)
				{
					return m_programs.at(name);
				}
				
				Renderer& deleteAllPrograms()
				{
					for(auto& i : m_programs)
					{
						i.second.deleteGLObject();
					}
					return *this;
				}
				
			public:
				Renderer& render(Renderable& renderable)
				{
					renderable.beRendered(*this);
					return *this;
				}
		};
	}
}

#endif
