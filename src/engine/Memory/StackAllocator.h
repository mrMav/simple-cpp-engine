#pragma once

#include "Types.h"

namespace Engine
{
	typedef u8* StackFrame;

	/// <summary>
	/// Basic stack allocator
	/// </summary>
	class StackAllocator
	{
		// Game Engine Architecture Third Edition
		// Game Programming Gems
	public:

		explicit StackAllocator(u32 bytes)
			: m_Bytes(bytes)
		{
			m_MemoryBlock = new u8[bytes];

			assert(m_MemoryBlock != 0);

			m_Top = m_MemoryBlock + bytes;
			m_Frame = m_MemoryBlock;
		};

		~StackAllocator()
		{
			delete[] m_MemoryBlock;
		}

		template <typename T>
		T* Alloc(u32 bytes)
		{
			u8* mem;

			if (m_Frame + bytes > m_Top)
			{
				// not enough memory;
				return 0;
			}

			// advance frame
			mem = m_Frame;

			// give memory
			m_Frame += bytes;

			return (T*)mem;
		};

		StackFrame GetFrame()
		{
			return m_Frame;
		}

		void ReleaseFrame(StackFrame frame)
		{
			// check if frame is being released in correct order
			assert(frame <= m_Frame);

			// release
			m_Frame = frame;
		}

		void Clear()
		{
			// delete everything
			m_Frame = m_MemoryBlock;
		}

	private:

		// size of the stack
		u32 m_Bytes;

		// base limit of the stack
		u8* m_MemoryBlock;

		// top limit of the stack
		u8* m_Top;

		// current top of the stack
		u8* m_Frame;

	};
}