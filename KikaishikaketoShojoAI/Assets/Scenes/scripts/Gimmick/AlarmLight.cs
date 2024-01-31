using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class AlarmLight : MonoBehaviour
{
    [SerializeField]
    Alarm alarm;
    [SerializeField]
    private bool fadein = false;


    Color color;

    void Start()
    {
        color = gameObject.GetComponent<Image>().color;
        color.a = 0.0f;
        gameObject.GetComponent<Image>().color = color;
    }

    void Update()
    {
        if (Time.timeScale > 0)
        {
            if (alarm.active == true)
            {
                if (fadein == true)
                {
                    color.a += 0.005f;
                    if (color.a > 0.3f)
                    {
                        color.a = 0.3f;
                        fadein = false;
                    }
                }
                else
                {
                    color.a -= 0.005f;
                    if (color.a < 0.05f)
                    {
                        color.a = 0.05f;
                        fadein = true;
                    }
                }
            }
            else
            {
                color.a = 0.0f;
            }
            gameObject.GetComponent<Image>().color = color;
        }
        
    }

}
