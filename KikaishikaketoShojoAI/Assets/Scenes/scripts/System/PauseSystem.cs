using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class PauseSystem : MonoBehaviour
{
    private bool pause = false;
    Color color;
    [SerializeField]
    GameObject black;

    Color plcolor;
    [SerializeField]
    GameObject play;

    Color excolor;
    [SerializeField]
    GameObject exit;

    Color qucolor;
    [SerializeField]
    GameObject quit;

    public int select = 0;

    bool nextSwitch = true;


    [SerializeField]
    GameObject op;
    public AudioClip open;
    AudioSource audioSourceOpen;

    [SerializeField]
    GameObject sel;
    public AudioClip button;
    AudioSource audioSourceSelect;
    
    [SerializeField]
    GameObject mo;
    public AudioClip seMove;
    AudioSource audioSourceMove;
    // Start is called before the first frame update
    void Start()
    {
        color = black.GetComponent<Image>().color;
        color.a = 0.0f;
        black.gameObject.GetComponent<Image>().color = color;

        plcolor = black.GetComponent<Image>().color;
        plcolor.a = 0.0f;
        play.gameObject.GetComponent<Image>().color = plcolor;

        excolor = black.GetComponent<Image>().color;
        excolor.a = 0.0f;
        exit.gameObject.GetComponent<Image>().color = excolor;

        qucolor = black.GetComponent<Image>().color;
        qucolor.a = 0.0f;
        quit.gameObject.GetComponent<Image>().color = qucolor;

        audioSourceOpen = op.GetComponent<AudioSource>();
        audioSourceSelect = sel.GetComponent<AudioSource>();
        audioSourceMove = mo.GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.deltaTime != 0 || pause == true)
        {
            if (Input.GetKeyDown(KeyCode.Escape) || Input.GetKeyDown("joystick button 7"))
            {
                if (pause == false)
                {
                    color.a = 0.3f;
                    plcolor.a = 0.3f;
                    excolor.a = 0.3f;
                    qucolor.a = 0.3f;
                    Time.timeScale = 0;
                    pause = true;
                    audioSourceOpen.PlayOneShot(open);
                }
                else
                {
                    color.a = 0.0f;
                    plcolor.a = 0.0f;
                    excolor.a = 0.0f;
                    qucolor.a = 0.0f;
                    pause = false;
                    Time.timeScale = 1;
                    audioSourceOpen.PlayOneShot(open);
                }
            }



            if (pause == true)
            {
                if (Input.GetAxis("Vertical") > 0.1f)
                {
                    if (nextSwitch == true)
                    {
                        audioSourceMove.PlayOneShot(seMove);
                        select -= 1;
                        if (select < 1)
                        {
                            select = 1;
                        }
                    }
                    nextSwitch = false;
                }
                else if (Input.GetAxis("Vertical") < -0.1f)
                {
                    if (nextSwitch == true)
                    {
                        audioSourceMove.PlayOneShot(seMove);
                        select += 1;
                        if (select > 3)
                        {
                            select = 3;
                        }
                    }
                    nextSwitch = false;
                }
                else
                {
                    nextSwitch = true;
                }

                switch (select)
                {
                    case 1:
                        plcolor.a = 1.0f;
                        excolor.a = 0.3f;
                        qucolor.a = 0.3f;
                        break;
                    case 2:
                        plcolor.a = 0.3f;
                        excolor.a = 1.0f;
                        qucolor.a = 0.3f;
                        break;
                    case 3:
                        plcolor.a = 0.3f;
                        excolor.a = 0.3f;
                        qucolor.a = 1.0f;
                        break;
                    default:
                        break;
                }


                if (Input.GetKeyDown(KeyCode.Z) || Input.GetKeyDown("joystick button 2") || Input.GetKeyDown("joystick button 0"))
                {
                    audioSourceSelect.PlayOneShot(button);
                    switch (select)
                    {
                        case 1:
                            color.a = 0.0f;
                            plcolor.a = 0.0f;
                            excolor.a = 0.0f;
                            qucolor.a = 0.0f;
                            pause = false;
                            Time.timeScale = 1;
                            break;
                        case 2:
                            SceneManager.LoadScene("title");
                            break;
                        case 3:
                            Application.Quit();//ゲームプレイ終了
                            break;
                        default:
                            break;
                    }
                }
            }



            black.gameObject.GetComponent<Image>().color = color;
            play.gameObject.GetComponent<Image>().color = plcolor;
            exit.gameObject.GetComponent<Image>().color = excolor;
            quit.gameObject.GetComponent<Image>().color = qucolor;
        }
    }
}
