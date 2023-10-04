#include "OpenGL/Texture2D.h"
#include "Utils/Rectangle.h"


namespace Engine
{
    class FrameAnimation
    {
        public:
        FrameAnimation() { };
        FrameAnimation(Ref<Texture2D> ptexture, const Rectangle<int>* pframes, int pframeCount);
        ~FrameAnimation() { };

        int currentFrame = 0;
        const Rectangle<int>* currentFramePtr = nullptr;
        bool loop = false;

        void SetFps(uint32_t fps);
        void Update(float delta);
        void Play();
        const Rectangle<int>* GetCurrentFrame() const;
        Ref<Texture2D> GetTexture() const;

        private:
        Ref<Texture2D> m_Texture;
        const Rectangle<int>* m_Frames;
        uint32_t m_FrameCount;

        bool m_ShouldUpdate = false;

        uint32_t m_Fps = 12;
        double m_FrameTime = 1.0 / m_Fps;

        // timer since the animation started
        double m_AccumulatedTime = 0;

        // when shoud we show the next frame
        double m_NextFrameTime = 0;

    };
}