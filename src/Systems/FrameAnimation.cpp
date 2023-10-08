#include <Engine.h>

namespace Engine
{
    FrameAnimation::FrameAnimation(Ref<Texture2D> ptexture, const Rectangle<int>* pframes, int pframeCount, int fps)
        : m_Texture(ptexture), m_Frames(pframes), m_FrameCount(pframeCount)
    {
        currentFramePtr = m_Frames;
        SetFps(fps);
    }

    void FrameAnimation::SetFps(uint32_t fps)
    {
        m_Fps = fps;
        m_FrameTime = 1.0 / fps;        
    };

    const Rectangle<int>*  FrameAnimation::GetCurrentFrame() const
    {
        return currentFramePtr;
    }

    Ref<Texture2D> FrameAnimation::GetTexture() const 
    {
        return m_Texture;
    }

    void FrameAnimation::Play(bool ploop)
    {
        m_ShouldUpdate = true;
        currentFrame = 0;
        currentFramePtr = m_Frames;
        loop = ploop;

        m_AccumulatedTime = 0;
        m_NextFrameTime = m_FrameTime;
    }

    bool FrameAnimation::IsPlaying() const
    {
        return m_ShouldUpdate;
    }

    void FrameAnimation::Update(float delta)
    {
        if (m_ShouldUpdate)
        {
            m_AccumulatedTime += delta;

            if(m_AccumulatedTime >= m_NextFrameTime)
            {
                m_NextFrameTime = m_AccumulatedTime + m_FrameTime;
            
                currentFrame++;
                currentFramePtr++;

                if(currentFrame > m_FrameCount - 1)
                {
                    if(loop)
                    {
                        currentFrame = 0;
                        currentFramePtr = m_Frames;
                    } else
                    {
                        // animation finished
                        m_ShouldUpdate = false;
                        currentFrame = 0;
                        currentFramePtr = m_Frames;
                    }
                }

            }
            
        }
    }

}