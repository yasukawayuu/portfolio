using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DrawSearchArea : MonoBehaviour
{
    [SerializeField] private bool drawActive = true;
    // Start is called before the first frame update
    void Start()
    {
        if(drawActive == true)
        {
            this.gameObject.SetActive(true);    //�\��
        }
        else
        {
            this.gameObject.SetActive(false);   //��\��
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
