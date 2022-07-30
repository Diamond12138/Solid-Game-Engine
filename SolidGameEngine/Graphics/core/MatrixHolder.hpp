#ifndef __SOLID_GRAPHICS_MATRIX_HOLDER_HPP__
#define __SOLID_GRAPHICS_MATRIX_HOLDER_HPP__
#include <glm/glm.hpp>

namespace Solid
{
	namespace Graphics
	{
		template<typename m_MatrixType>
		class MatrixHolder
		{
			private:
				m_MatrixType m_matrix;
				
			public:
				MatrixHolder() : m_matrix(m_MatrixType()) {}
				MatrixHolder(m_MatrixType matrix) : m_matrix(matrix) {}
				MatrixHolder(MatrixHolder<m_MatrixType>& from) : m_matrix(from.m_matrix) {}
				
			public:
				MatrixHolder<m_MatrixType>& setMatrix(m_MatrixType matrix)
				{
					m_matrix = matrix;
					return *this;
				}
				m_MatrixType getMatrix()
				{
					return m_matrix;
				}
				
			public:
				virtual MatrixHolder<m_MatrixType>& loadIdentity()
				{
					m_matrix = m_MatrixType();
					return *this;
				}
				virtual MatrixHolder<m_MatrixType>& updateMatrix()
				{
					return *this;
				}
				
			public:
				virtual MatrixHolder<m_MatrixType>& operator=(const MatrixHolder& from)
				{
					m_matrix = from.m_matrix;
					return *this;
				}
				
			public:
				typedef m_MatrixType MatrixType;
		};
		
		typedef MatrixHolder<glm::mat2> MatrixHolder2;
		typedef MatrixHolder<glm::mat3> MatrixHolder3;
		typedef MatrixHolder<glm::mat4> MatrixHolder4;
		typedef MatrixHolder<glm::dmat2> MatrixHolder2d;
		typedef MatrixHolder<glm::dmat3> MatrixHolder3d;
		typedef MatrixHolder<glm::dmat4> MatrixHolder4d;
	}
}

#endif
