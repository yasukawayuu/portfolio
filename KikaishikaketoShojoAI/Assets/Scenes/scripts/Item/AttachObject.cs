using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttachObject : MonoBehaviour
{
    [SerializeField] private PlayerController player;
    
    public AudioClip se;
    AudioSource audioSource;

    private Vector3 oldPos;
    
    [SerializeField] bool isPlayer = false;

    private bool have = false;
    void Start()
    {
        audioSource = GetComponent<AudioSource>();
        oldPos = transform.position;
    }

    void Update()
    {
        if (Time.timeScale > 0)
        {
            if (isPlayer == true)
            {
                if (Input.GetKeyDown(KeyCode.X) || Input.GetKeyDown("joystick button 0"))
                {
                    if (have == false)
                    {
                        player.ItemGet(this.gameObject);
                        have = true;
                    }
                    else
                    {
                        player.ReleseItem(this.gameObject);

                        transform.parent = null;
                        have = false;
                    }
                }

                if(have == true)
                {

                    Vector3 velocity = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
                    if (velocity.magnitude != 0)
                    {
                        if (audioSource.isPlaying == false)
                        {
                            audioSource.PlayOneShot(se);
                        }
                    }
                    else
                    {
                        audioSource.Stop();
                    }
                }
                else
                {
                    audioSource.Stop();
                }
            }
        }
    }
    

    public void ResetItemState()
    {
    }
    
    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.CompareTag("Target"))
        {
            isPlayer = true;
        }
    }
    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.CompareTag("Target"))
        {
            isPlayer = false;
        }
    }
}
