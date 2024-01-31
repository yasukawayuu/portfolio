using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SearchItem : MonoBehaviour
{
    [SerializeField]
    GameObject Image;
    ItemManager itemManager;

    [SerializeField]
    GameObject seObj;

    public AudioClip se;
    AudioSource audioSource;

    void Start()
    {
        itemManager = Image.GetComponent<ItemManager>();

        audioSource = seObj.GetComponent<AudioSource>();
    }

    // Update is called once per framse
    private void Update()
    {
       
    }

    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.CompareTag("KeyItem"))
        {
            if (Input.GetKey("y") || Input.GetKey("joystick button 0"))
            {  
                string ItemName = other.gameObject.name;
                itemManager.AddItem(ItemName);
                Destroy(other.gameObject);
                Debug.Log("”½‰ž");
                audioSource.PlayOneShot(se);
                itemManager.HaveItem();
            }
        }
    }
}
