using Leap;
using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Threading;

class LeapListener : Listener
{
	private object thisLock = new object();
	private Frame m_Frame;
	private bool createdNew;
	private Mutex m_mutex;

	private void SafeWriteLine (string line)
	{
		lock (thisLock) {
			Debug.Log (line);
		}
	}
	
	public override void OnConnect (Controller controller)
	{
		SafeWriteLine ("Connected");
	}
	
	public override void OnFrame (Controller controller)
	{
		Frame frame = controller.Frame ();

		m_Frame = frame;

		/*SafeWriteLine ("Frame id: " + frame.Id
		               + ", timestamp: " + frame.Timestamp
		               + ", hands: " + frame.Hands.Count
		               + ", fingers: " + frame.Fingers.Count
		               + ", tools: " + frame.Tools.Count
		               + ", gestures: " + frame.Gestures ().Count);*/

		/*for (int i = 0; i < frame.Hands.Count; i++) {
			Hand hand = frame.Hands[i];

			string handType = hand.IsLeft ? "Left hand" : "Right hand";
			SafeWriteLine(handType);			
			
			Arm arm = hand.Arm;
			//wrist pos & elbow pos
			Vector wristPos = arm.WristPosition;
			Vector elbowPos = arm.ElbowPosition;
		}*/
	}

	public Frame GetLeapFrame(){

		Frame tframe = m_Frame;

		return tframe;
	}
}
