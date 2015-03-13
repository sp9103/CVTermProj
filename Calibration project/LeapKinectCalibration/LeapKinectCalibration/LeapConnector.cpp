#include "LeapConnector.h"

void LeapConnector::onInit(const Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void LeapConnector::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
	/*renderer.InitializeRenderer("Leap motion");
	renderer.WaitUntilThreadInit();*/
}

void LeapConnector::onDisconnect(const Controller& controller) {
	// Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;

	/*renderer.DeInitializeRenderer();
	renderer.WaitUntilThreadDead();*/
}

void LeapConnector::onExit(const Controller& controller) {
	std::cout << "Exited" << std::endl;
}

void LeapConnector::onFocusGained(const Controller& controller) {
	std::cout << "Focus Gained" << std::endl;
}

void LeapConnector::onFocusLost(const Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}

void LeapConnector::onDeviceChange(const Controller& controller) {
	std::cout << "Device Changed" << std::endl;
	const DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::cout << "id: " << devices[i].toString() << std::endl;
		std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
	}
}

void LeapConnector::onServiceConnect(const Controller& controller) {
	std::cout << "Service Connected" << std::endl;
}

void LeapConnector::onServiceDisconnect(const Controller& controller) {
	std::cout << "Service Disconnected" << std::endl;
}

void LeapConnector::onFrame(const Controller& controller) {
	// Get the most recent frame and report some basic information
	const Frame frame = controller.frame();
	std::cout << "Frame id: " << frame.id()
		<< ", timestamp: " << frame.timestamp()
		<< ", hands: " << frame.hands().count()
		<< ", fingers: " << frame.fingers().count()
		<< ", tools: " << frame.tools().count()
		<< ", gestures: " << frame.gestures().count() << std::endl;

	HandList hands = frame.hands();
	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
		// Get the first hand
		const Hand hand = *hl;
		//std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
		//std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
		//	<< ", palm position: " << hand.palmPosition() << std::endl;
		// Get the hand's normal vector and direction

		const Vector normal = hand.palmNormal();
		const Vector direction = hand.direction();
		// Calculate the hand's pitch, roll, and yaw angles
		/*std::cout << std::string(2, ' ') <<  "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
		<< "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
		<< "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;*/

		// Get the Arm bone
		Arm arm = hand.arm();
		/*std::cout << std::string(2, ' ') <<  "Arm direction: " << arm.direction()
		<< " wrist position: " << arm.wristPosition()
		<< " elbow position: " << arm.elbowPosition() << std::endl;*/

		// Get fingers
		const FingerList fingers = hand.fingers();
		int i = 0;
		for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
			const Finger finger = *fl;
			/*std::cout << std::string(4, ' ') <<  fingerNames[finger.type()]
			<< " finger, id: " << finger.id()
			<< ", length: " << finger.length()
			<< "mm, width: " << finger.width() << std::endl;*/

			// Get finger bones
			for (int b = 0; b < 4; ++b) {
				Bone::Type boneType = static_cast<Bone::Type>(b);
				Bone bone = finger.bone(boneType);
				/*std::cout << std::string(6, ' ') <<  boneNames[boneType]
				<< " bone, start: " << bone.prevJoint()
				<< ", end: " << bone.nextJoint()
				<< ", direction: " << bone.direction() << std::endl;*/
			}
		}
	}

	//// Get tools
	//const ToolList tools = frame.tools();
	//for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
	//	const Tool tool = *tl;
	//	std::cout << std::string(2, ' ') <<  "Tool, id: " << tool.id()
	//		<< ", position: " << tool.tipPosition()
	//		<< ", direction: " << tool.direction() << std::endl;
	//}

	if (!frame.hands().isEmpty()) {
		std::cout << std::endl;
	}
}