using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LookPos : MonoBehaviour
{

    [SerializeField]
    GameObject player;
    private Vector3 pos;
    // Start is called before the first frame update
    void Start()
    {
        pos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        pos.x = player.transform.position.x;
        pos.z = player.transform.position.z;
        transform.position = pos;
    }
}
