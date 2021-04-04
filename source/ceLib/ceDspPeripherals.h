#pragma once

#include <mutex>

#include "ringbuffer.h"

#include "../dsp56300/source/dsp56kEmu/peripherals.h"

namespace std
{
	class mutex;
}

namespace dsp56k
{
	class DSP;
	class Essi;
}

namespace ceLib
{
	class DspPeripherals final : public dsp56k::PeripheralsDefault
	{
	public:
		void initialize(dsp56k::DSP& _dsp);
		void process(std::mutex& _dspLock, float** _inputs, float** _outputs, size_t _sampleFrames);
		void writeData(const int32_t* _data, size_t _count);

	private:
		bool isValidAddress( dsp56k::TWord _addr ) const override;
		dsp56k::TWord read(dsp56k::TWord _addr) override;
		void write(dsp56k::TWord _addr, dsp56k::TWord _value) override;
		void exec() override;

		dsp56k::DSP* m_dsp = nullptr;

		RingBuffer<uint32_t, 1024> m_hi8data;

		RingBuffer<uint32_t, 8192> m_audioInput;
		RingBuffer<uint32_t, 8192> m_audioOutput;

		uint32_t m_frameSync = 0;
	};
}
