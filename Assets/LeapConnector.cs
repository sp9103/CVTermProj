using UnityEngine;
using System.Collections;
using Leap;

public class LeapConnector : MonoBehaviour {
	private Controller controller;
	private LeapListener listener;

	public GameObject RightHandModel, LeftHandModel;

	// Use this for initialization
	void Start () {
		Debug.Log ("Leap motion Init start");
		controller = new Controller ();
		listener = new LeapListener ();

		controller.AddListener (listener);
	}
	
	// Update is called once per frame
	void Update () {
		Frame tFrame = listener.GetLeapFrame ();

		if (!tFrame.Hands.IsEmpty && tFrame.IsValid){
			for(int i = 0; i < ( tFrame.Hands.Count > 2 ? 2 : tFrame.Hands.Count); i++){ 
				Hand tHand = tFrame.Hands[i];

				HandControl tScript;
				if(tHand.IsLeft){
					tScript = LeftHandModel.GetComponent<HandControl>();
					tScript.SetHand(tHand);
				}
				else{
					tScript = RightHandModel.GetComponent<HandControl>();
					tScript.SetHand(tHand);
				}
			}
		}
	}

	void OnDestroy(){
		controller.RemoveListener (listener);
		controller.Dispose ();
	}
}
