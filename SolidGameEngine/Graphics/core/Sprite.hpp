#ifndef __SOLID_GRAPHICS_SPRITE_HPP__
#define __SOLID_GRAPHICS_SPRITE_HPP__
#include "Transform.hpp"
#include "Renderable.hpp"

namespace Solid
{
	namespace Graphics
	{
		class Sprite : public Transform , public Renderable
		{
			public:
				Sprite() : Transform() , Renderable() {}
				Sprite(Sprite& from) : Transform(from) , Renderable(from) {}
				Sprite(Transform& transform,GLuint vao) : Transform(transform) , Renderable(vao) {}
				Sprite(Transform& transform,Renderable& renderable) : Transform(transform) , Renderable(renderable) {}
		};
	}
}

#endif
