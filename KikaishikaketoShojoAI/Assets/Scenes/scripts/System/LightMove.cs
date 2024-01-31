using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightMove : MonoBehaviour
{
    [SerializeField]
    GameObject[] waypoint;

    [SerializeField]
    LightManager lm;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log(name + " AAAAAAAAAAAAAA.");
        transform.position = waypoint[lm.moveA].transform.position;
    }
}
