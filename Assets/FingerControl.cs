using UnityEngine;
using System.Collections;
using Leap;

public class FingerControl : MonoBehaviour {
	public GameObject[] FingerBones = new GameObject[4];

	private Finger m_Finger;
	private bool isDeviceOn;

	// Use this for initialization
	void Start () {
		isDeviceOn = false;
	}
	
	// Update is called once per frame
	void Update () {
		if (isDeviceOn) {

			for(int i = 0; i < 4; i++){
				Bone.BoneType tType = (Bone.BoneType)i;
				Bone tBone = m_Finger.Bone(tType);

				setBone(tBone, FingerBones[i]);
			}
		}
	}

	public void SetFinger(Finger src){
		isDeviceOn = true;
		m_Finger = src;
	}
	
	private void setBone(Bone src, GameObject FingerBone){
		Vector3 t_vec;
		t_vec.x = src.Center.x / 10;
		t_vec.y = src.Center.y / 10;
		t_vec.z = -src.Center.z / 10;
		
		FingerBone.transform.position = t_vec;

		Vector3 tLength = FingerBone.transform.localScale;
		tLength.z = src.Length / 10 / 2;
		FingerBone.transform.localScale = tLength;

		t_vec.x = src.Direction.x;
		t_vec.y = src.Direction.y;
		t_vec.z = -src.Direction.z;

		//Debug.Log (t_vec);
		if(t_vec.magnitude > 0.1)
			FingerBone.transform.rotation = Quaternion.LookRotation(t_vec);
	}
}
