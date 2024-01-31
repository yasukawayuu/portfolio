using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class an : MonoBehaviour
{
    Animator anim;                          // キャラにアタッチされるアニメーターへの参照
    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.P))
        {
            anim.SetBool("run", true);
        }

        if (Input.GetKeyDown(KeyCode.O))
        {
            anim.SetBool("run", false);
        }

        if (Input.GetKeyDown(KeyCode.I))
        {
            anim.SetBool("jump", true);
        }

        if (Input.GetKeyDown(KeyCode.U))
        {
            anim.SetBool("jump", false);
        }
    }
}
