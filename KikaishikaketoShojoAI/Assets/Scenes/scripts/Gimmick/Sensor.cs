using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sensor : MonoBehaviour
{

    [SerializeField]
    [Tooltip("スイッチに接続")]
    GimmickButton[] buttons;

    [SerializeField]
    private bool sensor_active = true;

    [SerializeField]
    public bool active = false;

    [SerializeField]
    private bool all = false;

    public AudioClip se;
    AudioSource audioSource;
    // Start is called before the first frame update
    void Start()
    {
        sensor_active = true;
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.timeScale > 0)
        {
            int acnt = 0;
            if (all == true)
            {
                for (int i = 0; i < buttons.Length; i++)
                {
                    if (buttons[i].active == true)
                    {
                        acnt += 1;
                    }
                }

                if (acnt == buttons.Length)
                {
                    sensor_active = false;
                    active = false;
                }
                else
                {
                    sensor_active = true;
                }
            }
            else
            {
                for (int i = 0; i < buttons.Length; i++)
                {
                    if (buttons[i].active == true)
                    {
                        acnt += 1;
                    }
                }

                if (acnt % 2 == 0)
                {
                    sensor_active = true;
                }
                else
                {
                    sensor_active = false;
                    active = false;
                }
            }
            var renderer = gameObject.GetComponent<Renderer>();
            if (sensor_active == true)
            {
                // 表示
                renderer.enabled = true;
            }
            else
            {
                if (renderer.enabled == true)
                {
                    audioSource.PlayOneShot(se);
                }
                // 非表示
                renderer.enabled = false;
            }
        }
        
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {
            if (sensor_active == true)
            {
                active = true;
            }
        }
    }
}
