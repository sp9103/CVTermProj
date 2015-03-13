using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class BodyControl : MonoBehaviour {
	
	[DllImport("Kinect4Unity")]
	private static extern void TEST();
	[DllImport("Kinect4Unity")]
	private static extern void KinectInitialize();
	[DllImport("Kinect4Unity")]
	private static extern void KinectDeinitialize();
	[DllImport("Kinect4Unity")]
	private static extern void KinectRun();
	[DllImport("Kinect4Unity")]
	private static extern int GetUpperBody(float [] a1Array, float [] facepos, float [] faceDir);

	private GameObject[] Bone;
	public GameObject bonePrefab;

	// Use this for initialization
	void Start () {
		KinectInitialize ();

		//Create Bone
		Bone = new GameObject[12];
		for (int i = 0; i < 12; i++) {
			//Bone[i] = (GameObject)Resources.Load("Assets/Prefabs/Bone.prefab", typeof(GameObject));
			Bone[i] = Instantiate(bonePrefab);
			Bone[i].transform.position = new Vector3(0,0,0);
			Bone[i].transform.parent = this.transform;
			Bone[i].transform.localScale = new Vector3(6,6,6);
		}
	}
	
	// Update is called once per frame
	void Update () {
		float[] a1Array = new float[3*13];
		float[] facepos = new float[3];
		float[] faceDir = new float[4];

		if (GetUpperBody (a1Array, facepos, faceDir) != -1) {
			//set body position
			SetBody(a1Array);
		}
	}

	void OnDestroy(){
		KinectDeinitialize ();
	}

	private void SetJoint(Vector3 src1, Vector3 src2, GameObject bone){
		Vector3 center = (src1 + src2) / 2;
		Vector3 dir = (src1 - src2).normalized;
		float len = (src1 - src2).magnitude / 2;

		//position
		bone.transform.position = center;

		//Length
		Vector3 tLength = bone.transform.localScale;
		tLength.z = len;
		bone.transform.localScale = tLength;

		//Rotation
		if(dir.magnitude > 0.1)
			bone.transform.rotation  = Quaternion.LookRotation(dir);
	}

	private void SetBody(float[] body){
		Vector3[] tbodyVec = new Vector3[13];

		//Convert float array to vec array
		for (int i = 0; i < 13; i++) {
			tbodyVec[i].x = body[i*3 + 0];
			tbodyVec[i].y = body[i*3 + 1];
			tbodyVec[i].z = body[i*3 + 2];
		}

		//Debug.Log(tbodyVec[3]);

		SetJoint (tbodyVec [3], tbodyVec [2], Bone [0]);
		SetJoint (tbodyVec [2], tbodyVec [12], Bone [1]);
		SetJoint (tbodyVec [12], tbodyVec [1], Bone [2]);
		SetJoint (tbodyVec [0], tbodyVec [12], Bone [3]);

		//Right
		SetJoint (tbodyVec [12], tbodyVec [8], Bone [4]);
		SetJoint (tbodyVec [8], tbodyVec [9], Bone [5]);
		SetJoint (tbodyVec [9], tbodyVec [10], Bone [6]);
		SetJoint (tbodyVec [10], tbodyVec [11], Bone [7]);

		//Left
		SetJoint (tbodyVec [12], tbodyVec [4], Bone [8]);
		SetJoint (tbodyVec [4], tbodyVec [5], Bone [9]);
		SetJoint (tbodyVec [5], tbodyVec [6], Bone [10]);
		SetJoint (tbodyVec [6], tbodyVec [7], Bone [11]);
	}
}
