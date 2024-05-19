

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <sys/types.h>
	#include <netdb.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <stdarg.h>
	#include <string.h>
//typedef void* receiveBufer_t;
	typedef int SOCKET;
	const int NO_ERROR = 0;
	const int INVALID_SOCKET = -1;
	const int WSAECONNRESET = ECONNRESET;
	const int WSAEWOULDBLOCK = EAGAIN;
	const int SOCKET_ERROR = -1;

#include "memory"

#include "vector"
#include "array"
#include "unordered_map"
#include "string"
#include "list"
#include "queue"
#include "deque"
#include "unordered_set"
#include "cassert"
#include "map"
#include "random"

using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::queue;
using std::list;
using std::deque;
using std::unordered_map;
using std::string;
using std::unordered_set;
using std::map;

class Piece;
class GameObject;
enum class PieceType;

#include "RoboMath.hpp"
#include "RandGen.hpp"

#include "StringUtils.hpp"
#include "SocketAddress.hpp"
#include "SocketAddressFactory.hpp"
#include "UDPSocket.hpp"
#include "TCPSocket.hpp"
#include "SocketUtil.hpp"

#include "MemoryBitStream.hpp"

#include "InputAction.hpp"
#include "Command.hpp"
#include "CommandList.hpp"
#include "TurnData.hpp"

// #include <SDL.h>
// #include "Texture.h"
// #include "TextureManager.h"
// #include "SpriteComponent.h"
// #include "RenderManager.h"
// #include "GraphicsDriver.h"
#include "InputManager.hpp"

#include "Timing.hpp"

#include "GameObject.hpp"
#include "GameObjectRegistry.hpp"
#include "WeightedTimedMovingAverage.hpp"
#include "NetworkManager.hpp"

#include "Piece.hpp"
#include "Board.hpp"
// #include "Yarn.h"
// #include "StringUtils.h"
#include "ScoreBoardManager.hpp"

#include "Engine.hpp"

// #include "WindowManager.h"
// #include "HUD.h"
