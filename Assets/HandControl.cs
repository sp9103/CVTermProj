using UnityEngine;
using System.Collections;
using Leap;

public class HandControl : MonoBehaviour {
	public GameObject Thumb, Index, Middle, Ring, Pinky;
	public GameObject Palm;

	private Hand m_Hand;
	private bool isDeviceOn;

	// Use this for initialization
	void Start () {
		isDeviceOn = false;
	}
	
	// Update is called once per frame
	void Update () {
		if (isDeviceOn) {
			//Elbow.transform.position = ConvLeapToUnityVec(m_Hand.Arm.ElbowPosition);
			//Wrist.transform.position = ConvLeapToUnityVec(m_Hand.WristPosition);
			Palm.transform.position = ConvLeapToUnityVec(m_Hand.PalmPosition);

			for(int i = 0; i < m_Hand.Fingers.Count; i++){
				Finger tFinger = m_Hand.Fingers[i];

				FingerControl tScrpit;
				switch(tFinger.Type()){
				case Finger.FingerType.TYPE_THUMB:
					tScrpit = Thumb.GetComponent<FingerControl>();
					tScrpit.SetFinger(tFinger);
					break;
				case Finger.FingerType.TYPE_INDEX:
					tScrpit = Index.GetComponent<FingerControl>();
					tScrpit.SetFinger(tFinger);
					break;
				case Finger.FingerType.TYPE_MIDDLE:
					tScrpit = Middle.GetComponent<FingerControl>();
					tScrpit.SetFinger(tFinger);
					break;
				case Finger.FingerType.TYPE_RING:
					tScrpit = Ring.GetComponent<FingerControl>();
					tScrpit.SetFinger(tFinger);
					break;
				case Finger.FingerType.TYPE_PINKY:
					tScrpit = Pinky.GetComponent<FingerControl>();
					tScrpit.SetFinger(tFinger);
					break;
				}
			}
		}
	}

	public void SetHand(Hand src){
		isDeviceOn = true;
		m_Hand = src;
	}

	private Vector3 ConvLeapToUnityVec(Vector src){
		Vector3 t_vec;
		t_vec.x = src.x / 10;
		t_vec.y = src.y / 10;
		t_vec.z = -src.z / 10;

		return t_vec;
	}
}
