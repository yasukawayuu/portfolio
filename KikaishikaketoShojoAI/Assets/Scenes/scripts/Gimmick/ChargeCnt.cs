using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChargeCnt : MonoBehaviour
{
    public AudioClip se;
    AudioSource audioSource;
    [SerializeField]
    Material changeMaterial;
    // Start is called before the first frame update
    void Start()
    {
        audioSource = GetComponent<AudioSource>();

    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void ChangeColor()
    {
        GetComponent<Renderer>().material = changeMaterial;
        audioSource.PlayOneShot(se);
    }
}
