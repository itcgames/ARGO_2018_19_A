#ifndef _PARAMETERS_CAMERA_H
#define _PARAMETERS_CAMERA_H

namespace app::par
{
	struct CameraParameters
	{
	public: // Constructors/Destructor/Assignments
		CameraParameters() = default;
		~CameraParameters() = default;

		CameraParameters(CameraParameters const &) = default;
		CameraParameters & operator=(CameraParameters const &) = default;

		CameraParameters(CameraParameters &&) = default;
		CameraParameters & operator=(CameraParameters &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::optional<app::Entity> targetEntity = std::nullopt;
		math::Vector2f clampPos = { 0.0f,0.0f };
		math::Vector2f clampSize = { 0.0f,0.0f };
		bool clamp = false;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_PARAMETERS_CAMERA_H
