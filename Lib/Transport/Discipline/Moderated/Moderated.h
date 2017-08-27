#pragma once

#include "../DisciplineBase.h"

namespace Boggart
{
	namespace Transport
	{
		class Moderated : public DisciplineBase
		{
		public:
			Moderated(std::string id);
			~Moderated() override;

		private:
			bool _OnOpen() override;

			bool _OnClose() override;

			void OnPing(PingPtr ping) override;

			void OnPong(PongPtr pong) override;
		};
	}
}