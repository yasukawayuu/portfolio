using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ItemSwitch : MonoBehaviour
{
    [SerializeField]
    GameObject Image;
    [SerializeField]
    private Canvas ItemCanvas;

    ItemManager itemManager;
    // Start is called before the first frame update
    void Start()
    {
        ItemCanvas.enabled = false;
        itemManager = Image.GetComponent<ItemManager>();
    }

    // Update is called once per frame
    void Update()
    {
        if ( Time.deltaTime != 0 || ItemCanvas.enabled == true )
        {
            if(itemManager.GethaveItem() == true)
            {
                if (Input.GetKeyUp("e") || Input.GetKeyUp("joystick button 3"))
                {
                    if (ItemCanvas.enabled == false)
                    {
                        Time.timeScale = 0.0f;
                        ItemCanvas.enabled = true;
                    }
                    else
                    {
                        Time.timeScale = 1.0f;
                        ItemCanvas.enabled = false;
                    }
                }
            }
        }
        
    }
}
