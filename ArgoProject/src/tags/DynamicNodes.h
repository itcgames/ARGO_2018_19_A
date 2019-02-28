#ifndef _TAG_DYNAMIC_NODES_H
#define _TAG_DYNAMIC_NODES_H

namespace app::tag
{
	struct DynamicNodes
	{
	public: // Public Usings/typedefs/enums
		struct Node
		{
			math::Vector2f position;
			std::list<std::shared_ptr<cmnd::BaseCommand>> loopCommands, oneTimeCommands;
		};
	public: // Constructors/Destructor/Assignments
		DynamicNodes() = default;
		~DynamicNodes() = default;

		DynamicNodes(DynamicNodes const &) = default;
		DynamicNodes & operator=(DynamicNodes const &) = default;

		DynamicNodes(DynamicNodes &&) = default;
		DynamicNodes & operator=(DynamicNodes &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::deque<Node> nodes;
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

#endif // !_TAG_DYNAMIC_NODES_H
