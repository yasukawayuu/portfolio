using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ExitGame : MonoBehaviour
{
    private bool isPlayer = false;

    Color color;

    [SerializeField]
    GameObject black;

    // Start is called before the first frame update
    void Start()
    {
        color = black.GetComponent<Image>().color;
        color.a = 0.0f;
        black.gameObject.GetComponent<Image>().color = color;
    }

    // Update is called once per frame
    void Update()
    {
        if (isPlayer == true)
        {
            // 表示
            color.a = 1.0f;

            if ((Input.GetKeyDown(KeyCode.X) ||
                Input.GetKeyDown("joystick button 0") ||
                Input.GetKeyDown("joystick button 2")))
            {
                Application.Quit();//ゲームプレイ終了
            }
        }
        else
        {
            // 非表示
            color.a = 0.0f;
        }
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
