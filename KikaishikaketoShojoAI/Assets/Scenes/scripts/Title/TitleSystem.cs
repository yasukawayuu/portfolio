using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TitleSystem : MonoBehaviour
{
    private bool isPlayer = false;

    [SerializeField]
    GoalController goal;

    Color plColor;
    Color quColor;
    Color lgColor;

    [SerializeField]
    GameObject play;

    [SerializeField]
    GameObject quit;

    [SerializeField]
    GameObject logo;


    [SerializeField]
    PointMove pm;

    float currentTime = 0.0f;
    public float span = 1.0f;


    [SerializeField]
    GimmickButton button;



    // Start is called before the first frame update
    void Start()
    {
        plColor = play.GetComponent<Image>().color;
        quColor = quit.GetComponent<Image>().color;
        lgColor = logo.GetComponent<Image>().color;

        plColor.a = 0.0f;
        quColor.a = 0.0f;
        lgColor.a = 0.0f;
    }

    // Update is called once per frame
    void Update()
    {
        if (pm.move == 1)
        {
            plColor.a = 1.0f;
            quColor.a = 0.0f;
            lgColor.a = 0.0f;

            if ((Input.GetKeyDown(KeyCode.X) ||
                Input.GetKeyDown("joystick button 0") ||
                Input.GetKeyDown("joystick button 2")))
            {
                pm.StartGame();
                button.active = true;
            }
        }
        else if (pm.move == 2)
        {
            plColor.a = 0.0f;
            quColor.a = 1.0f;
            lgColor.a = 0.0f;

            if ((Input.GetKeyDown(KeyCode.X) ||
                Input.GetKeyDown("joystick button 0") ||
                Input.GetKeyDown("joystick button 2")))
            {
                Application.Quit();//ゲームプレイ終了
            }
        }
        else
        {
            plColor.a = 0.0f;
            quColor.a = 0.0f;
            lgColor.a = 1.0f;

            if(pm.move == 3)
            {
                currentTime += Time.deltaTime;

                if (currentTime > span)
                {
                    goal.NextStage();
                }
            }
        }


        play.gameObject.GetComponent<Image>().color = plColor;
        quit.gameObject.GetComponent<Image>().color = quColor;
        logo.gameObject.GetComponent<Image>().color = lgColor;
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
