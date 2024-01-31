using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.PostProcessing;

public class PostProcessVolumeController : MonoBehaviour
{
    public  GameObject player;
    private PlayerController playerController;
    private Volume processVolume;

    void Start()
    {
        playerController = player.GetComponent<PlayerController>();
        processVolume = this.GetComponent<Volume>();
    }

    void Update()
    {
        if (playerController.isHidden == true)
        {
            if(processVolume.weight<1.0f) processVolume.weight += 0.02f;
        }
        else
        {
            if (processVolume.weight > 0.0f) processVolume.weight -= 0.01f;
        }
    }
}
