using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResetItemManage : MonoBehaviour
{
    [SerializeField]
    GameObject Image;
    ItemManager itemManager;
    // Start is called before the first frame update
    void Start()
    {

        itemManager = Image.GetComponent<ItemManager>();
        itemManager.ResetHaveItem();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
