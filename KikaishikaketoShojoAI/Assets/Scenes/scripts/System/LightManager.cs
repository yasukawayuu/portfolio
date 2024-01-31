using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightManager : MonoBehaviour
{
    public int moveA = 0;
    [SerializeField]
    int[] moveNumA;
    [SerializeField]
    GameObject[] pointA;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
    }

    private void OnTriggerEnter(Collider other)
    {
        for (int i = 0; i < pointA.Length; i++)
        {
            if (other.gameObject == pointA[i].gameObject)
            {
                moveA = moveNumA[i];
            }
        }
    }


    //private void OnTriggerStay(Collider other)
    //{
    //    Debug.Log(name + " FFFFFFFFFFFF.");
    //    for (int i = 0; i < pointA.Length; i++)
    //    {
    //        if (other == pointA[i])
    //        {
    //            moveA = moveNumA[i];
    //            break;
    //        }
    //    }
    //}
}
