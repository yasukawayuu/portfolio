using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Fin : MonoBehaviour
{
    public string NextScene;
    
    [SerializeField]
    GameObject image;
    [SerializeField]
    Text text;

    Color imageColor;
    int end = 0;


    float currentTime = 0.0f;
    public float span = 5.0f;

    public AudioClip bgm;
    AudioSource audioSource;

    private void Start()
    {
        imageColor = image.gameObject.GetComponent<Image>().color;

        text.enabled = false;

        end = 0;
        audioSource = GetComponent<AudioSource>();
        audioSource.Play();


    }
    private void Update()
    {

        switch (end) {
            case 1:
                if (imageColor.a <= 0.0f)
                {
                    end = 2;
                    text.enabled = true;
                    audioSource.Stop();
                }
                else
                {
                    imageColor.a -= 0.15f * Time.deltaTime;
                    audioSource.volume -= 0.16f * Time.deltaTime;
                }

                image.gameObject.GetComponent<Image>().color = imageColor;

                break;
            case 2:
                currentTime += Time.deltaTime;

                if (span < currentTime)
                {
                    SceneManager.LoadScene(NextScene);

                }
                break;
            default:
                break;

        }

    }

    public void RollEnd()
    {
        end = 1;
    }
}
