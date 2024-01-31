using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Resporn : MonoBehaviour
{

    [SerializeField]
    GameObject black;
    Color color;


    [SerializeField]
    StartController sc;

    public bool dead = false;
    public bool start = false;
    // Start is called before the first frame update
    void Start()
    {
        color = black.gameObject.GetComponent<Image>().color;
        color.a = 0.0f;
        black.gameObject.GetComponent<Image>().color = color;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        if(dead == true)
        {
            color.a += 0.01f;

            black.gameObject.GetComponent<Image>().color = color;
            
            if (color.a >= 1.0f)
            {
                dead = false;
                start = true;
            }
        }

        black.gameObject.GetComponent<Image>().color = color;
    }


    public void PlayerDead()
    {
        dead = true;
        start = false;
    }
    
    public void ReStart()
    {
        color.a = 0.0f;
        black.gameObject.GetComponent<Image>().color = color;
        start = false;
        sc.StartFadeIn();
    }
}
