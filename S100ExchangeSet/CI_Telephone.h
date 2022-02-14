#pragma once
#include "Voice.h"

namespace Dataset
{
	class CI_Telephone
	{
	public:
		CI_Telephone();
		virtual ~CI_Telephone();

	private:
		Voice voice;

	public:
		void SetVoice(Voice value);
		Voice GetVoice();
	};
}