using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PointMove : MonoBehaviour
{
    [SerializeField]
    GameObject[] point;
    
    public int move = 0;

    public AudioClip seMove;
    AudioSource audioSourceMove;
    // Start is called before the first frame update
    void Start()
    {
        audioSourceMove = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetAxis("Horizontal") > 0.1f)
        {
            if(move != 1)
            {
                audioSourceMove.PlayOneShot(seMove);
            }
            move = 1;
        }
        else if(Input.GetAxis("Horizontal") < -0.1f)
        {
            if (move != 2)
            {
                audioSourceMove.PlayOneShot(seMove);
            }
            move = 2;
        }


        transform.position = point[move].gameObject.transform.position;
    }

    public void StartGame()
    {
        move = 3;
    }
}
