using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class GimmickButton : MonoBehaviour
{
    [SerializeField]
    private float bottomY = 0.6f;
    [SerializeField]
    private float speed = 0.5f;

    public bool active;

    [SerializeField]
    [Tooltip("—£‚·‚Æ–ß‚é")]
    private bool button = true; //‰Ÿ‚µ‚Ä‚à—£‚ê‚é‚Æ–ß‚é

    private float def_posY;

    Color color;

    public AudioClip se;
    AudioSource audioSource;

    bool sound = false;
    float currentTime = 0.0f;
    public float span = 2.0f;
    private void Start()
    {
        def_posY = transform.position.y;

        color = GetComponent<Renderer>().material.color;

        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {
        if (Time.timeScale > 0)
        {
            if (active == true)
            {
                if (transform.position.y > bottomY)
                {
                    transform.position -= Vector3.up * speed * Time.deltaTime;
                }
                else
                {
                    transform.position = new Vector3(transform.position.x, bottomY, transform.position.z);
                }
            }
            else
            {
                if (transform.position.y < def_posY)
                {
                    transform.position += Vector3.up * speed * Time.deltaTime;
                }
            }

            if (sound == true)
            {
                currentTime += Time.deltaTime;
            }
        }
    }

    void OnCollisionEnter(Collision collision)
    {
        active = true;
        GetComponent<Renderer>().material.color = Color.yellow;
        if(sound == false)
        {
            audioSource.PlayOneShot(se);
            sound = true;
        }
    }

    void OnCollisionExit(Collision collision)
    {
        if(button == true)
        {
            active = false;

            GetComponent<Renderer>().material.color = color;


            if (currentTime > span)
            {
                sound = false;
                currentTime = 0f;
            }
        }
    }


    void OnCollisionStay(Collision collision)
    {
        active = true;
        GetComponent<Renderer>().material.color = Color.yellow;
    }

}
