using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayGame : MonoBehaviour
{

    private bool isPlayer = false;

    [SerializeField]
    GoalController goal;
    Color color;

    [SerializeField]
    GameObject black;


    [SerializeField]
    GameObject pl;

    // Start is called before the first frame update
    void Start()
    {
        color = black.GetComponent<Image>().color;
        color.a = 0.0f;
    }

    // Update is called once per frame
    void Update()
    {
        if (isPlayer == true)
        {
            // •\Ž¦
            color.a = 1.0f;

            if ((Input.GetKeyDown(KeyCode.X) ||
                Input.GetKeyDown("joystick button 0") ||
                Input.GetKeyDown("joystick button 2")))
            {
                goal.NextStage();
            }
        }
        else
        {
            // ”ñ•\Ž¦
            color.a = 0.0f;
        }


        black.gameObject.GetComponent<Image>().color = color;
    }


    void OnTriggerStay(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {
            isPlayer = true;
        }
    }
    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {
            isPlayer = false;
        }
    }

}
