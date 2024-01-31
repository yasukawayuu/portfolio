using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class LogoStart : MonoBehaviour
{
    [SerializeField]
    GameObject black;

    [SerializeField]
    GameObject logo;


    Color color;
    Color logocolor;

    [SerializeField]
    GameObject bgm;
    public AudioClip stage;
    AudioSource audioSource;
    bool start = true;
    private void Start()
    {
        StartFadeIn();
        audioSource = bgm.GetComponent<AudioSource>();
    }
    
    private void LateUpdate()
    {
        if (start == true)
        {
            if (color.a >= 0.0f)
            {
                Time.timeScale = 0;
                if (logocolor.a >= 0.0f)
                {

                    logocolor.a -= 0.005f;
                    logo.gameObject.GetComponent<Image>().color = logocolor;
                    black.gameObject.GetComponent<Image>().color = color;
                }
                else
                {
                    color.a -= 0.01f;

                    black.gameObject.GetComponent<Image>().color = color;
                    logo.gameObject.GetComponent<Image>().color = logocolor;
                    black.gameObject.GetComponent<Image>().color = color;
                }
            }
            else
            {
                Time.timeScale = 1;
                start = false;
            }
        }
        else
        {
            if(audioSource.isPlaying == false)
            {
                audioSource.Play();
            }
        }
    }

    public void StartFadeIn()
    {
        color = black.gameObject.GetComponent<Image>().color;
        color.a = 1.0f;
        black.gameObject.GetComponent<Image>().color = color;
        logocolor = logo.gameObject.GetComponent<Image>().color;
        logocolor.a = 1.0f;
        logo.gameObject.GetComponent<Image>().color = logocolor;
        start = true;
    }
}
