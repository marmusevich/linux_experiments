#pragma once

#include <cstdint>
#include <type_traits>

#include <string>


namespace NNet
{
	using tPayloadSize = uint32_t;
	using tUid = uint64_t;

/*
	//----------------------------
	enum class EMessageType : uint8_t
	{
		STRING,
		INT32,
	};

	template <EMessageType ETYPE>
	struct MessageTraits;

	template <>
	struct MessageTraits<EMessageType::STRING>
	{
		using tBodyType = std::string;
	};

	template <>
	struct MessageTraits<EMessageType::INT32>
	{
		using tBodyType = uint32_t;
	};

	//----------------------------





	template <typename ETYPE>
	struct Message
	{
		struct Header
		{
			tIid uid;
			tPayloadSize payloadSize;
			ETYPE type;
		};


		Header<ETYPE> header;

		//MessageTraits<ETYPE>::tBodyType body;
	};

	*/
}



