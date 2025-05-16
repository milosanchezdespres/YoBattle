#pragma once

#include "Utils.h"
#include "Seri.h"

namespace ECS
{
	class Factory
	{
		protected:
			Seri* __default;

		public:
			Factory() { __default = new Seri(); }

			auto* factor(json json_data)
			{
				if (json_data["type"] == "Seri") { return (new Seri())->load(json_data); }
				
				return OnExtraFactor(json_data);
			}

			virtual Seri* OnExtraFactor(json json_data) { return __default; }
	};
}