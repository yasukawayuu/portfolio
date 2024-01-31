using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pos : MonoBehaviour
{
    [SerializeField]
    GameObject obj;

    Vector3 move;
    // Start is called before the first frame update
    void Start()
    {
        move = transform.position - obj.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        move = transform.position - obj.transform.position;
        transform.position = move;
    }
}
