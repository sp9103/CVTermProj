using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class NewBehaviourScript : MonoBehaviour {

	[DllImport("CVTermProj")]
	public static extern void TEST();
	[DllImport("CVTermProj")]
	public static extern void KinectInitialize();
	[DllImport("CVTermProj")]
	public static extern void KinectDeinitialize();
	[DllImport("CVTermProj")]
	public static extern int KinectRun();
	
	// Use this for initialization
	void Start () {
		TEST ();
		KinectInitialize ();
	}
	
	// Update is called once per frame
	void Update () {
		KinectRun ();
	}

	void OnDestroy(){
		Debug.Log ("Deinitialize");
		KinectDeinitialize ();
	}
}
