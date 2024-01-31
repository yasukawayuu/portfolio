using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Alarm : MonoBehaviour
{
    [SerializeField]
    [Tooltip("ÉZÉìÉTÅ[Ç…ê⁄ë±")]
    Sensor[] sensors;
    [SerializeField]
    PlayerController player;

    public bool active = false;

    public AudioClip se;
    AudioSource audioSource;

    bool sound = false;

    // Start is called before the first frame update
    void Start()
    {
        audioSource = GetComponent<AudioSource>();
        //audioSource.loop = !audioSource.loop;
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.timeScale > 0)
        {
            for (int i = 0; i < sensors.Length; i++)
            {
                if (sensors[i].active == true)
                {
                    active = true;
                    break;
                }

                if (i == sensors.Length - 1)
                {
                    active = false;
                }
            }
            //if (player.isHidden == true)
            //{
            //    active = false;
            //}

            if (active == true)
            {

                if (sound == false)
                {
                    audioSource.Play();
                    sound = true;
                }

            }
            else
            {
                audioSource.Stop();
                sound = false;
            }
        }
        else
        {
            audioSource.Stop();
        }
    }

    public void ResetAlarm()
    {
        for (int i = 0; i < sensors.Length; i++)
        {
            sensors[i].active = false;
        }
        active = false;
    }
}
