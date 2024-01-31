using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class StartController : MonoBehaviour
{
    [SerializeField]
    GameObject black;
    Color color;

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

                color.a -= 0.01f;

                black.gameObject.GetComponent<Image>().color = color;
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
        start = true;
    }
}
