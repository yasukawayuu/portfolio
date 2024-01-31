using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerAnimTalk : MonoBehaviour
{
    Animator anim;

    bool walk = true;
    public AudioClip se;
    AudioSource audioSource;
    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (walk == true)
        {
            if (audioSource.isPlaying == false)
            {
                audioSource.PlayOneShot(se);
            }
            anim.SetBool("run", true);
        }
        else
        {
            audioSource.Stop();
            anim.SetBool("run", false);
        }

        if (Time.timeScale == 0)
        {
            audioSource.Stop();
        }
    }

    public void StartWalk()
    {
        walk = true;
    }

    public void StopWalk()
    {
        walk = false;
    }
}
