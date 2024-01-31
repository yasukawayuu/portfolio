using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GoalController : MonoBehaviour
{

    public string NextScene;
    bool isPlayer = false;
    bool next = false;

    [SerializeField]
    GameObject black;

    Color color;

    [SerializeField]
    GameObject bgm;
    public AudioClip stage;
    AudioSource audioSource;
    private void Start()
    {
        color = black.gameObject.GetComponent<Image>().color;
        color.a = 0.0f;
        black.gameObject.GetComponent<Image>().color = color;
        audioSource = bgm.GetComponent<AudioSource>();
    }
    private void LateUpdate()
    {
        //ÉSÅ[Éãéûââèo
        if(isPlayer == true || next ==true)
        {
            audioSource.Stop();
            color.a += 0.01f;

            black.gameObject.GetComponent<Image>().color = color;
            if (color.a >= 1.0f)
            {
                SceneManager.LoadScene(NextScene);
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.name == "Player")
        {
            isPlayer = true;
            Time.timeScale = 0;
        }
    }

    public void NextStage()
    {
        next = true;
    }
}
