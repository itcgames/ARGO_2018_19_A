#ifndef _UTILITIES_RANDOM_H
#define _UTILITIES_RANDOM_H

namespace app::util
{
	class Random
	{
	private: // Constructors/Destructor/Assignments
		Random() = default;
		~Random() = default;

		Random(Random const &) = default;
		Random & operator=(Random const &) = default;

		Random(Random &&) = default;
		Random & operator=(Random &&) = default;

	public: // Public Static Functions
		static std::int32_t gen(std::int32_t const & start, std::int32_t const & end);
		static float gen(float const & start, float const & end);
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
		static std::random_device s_randomDevice;
		static std::default_random_engine s_randomEngine;
		static std::uniform_int_distribution<std::int32_t> s_intDistribution;
		static std::uniform_real_distribution<float> s_realDistribution;
	private: // Private Member Variables
	};
}

#endif // !_UTILITIES_RANDOM_H
