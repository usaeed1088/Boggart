#pragma once
 
#include <Message/MessageBase.h>

namespace Boggart
{
	namespace IPC
	{
		class MessageBase : public Message::MessageBase
		{
		protected:
			MessageBase(std::string type);
			MessageBase(const std::vector<unsigned char>& data);

		public:
			virtual ~MessageBase() override;

		private:
			std::vector<unsigned char> OnEncode() override;
			bool OnDecode(const std::vector<unsigned char>& data) override;

		protected:
			virtual std::vector<unsigned char> _OnEncode() = 0;
			virtual bool _OnDecode(const std::vector<unsigned char>& data) = 0;
		};
	}
}