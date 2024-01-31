using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GimmickButtonReset : MonoBehaviour
{
    [SerializeField]
    private float bottomY = 0.6f;
    [SerializeField]
    private float speed = 0.5f;

    public bool active;

    [SerializeField]
    [Tooltip("—£‚·‚Æ–ß‚é")]

    private float def_posY;

    Color color;

    [SerializeField]
    GimmickButton[] buttons;

    private void Start()
    {
        def_posY = transform.position.y;

        color = GetComponent<Renderer>().material.color;
    }

    void Update()
    {
        if (Time.timeScale > 0)
        {
            if (active == true)
            {
                ResetButton();
            }
        }
    }

    void OnCollisionEnter(Collision collision)
    {
        active = true;
        GetComponent<Renderer>().material.color = Color.yellow;
        ResetButton();
    }

    void OnCollisionStay(Collision collision)
    {
        active = true;
        GetComponent<Renderer>().material.color = Color.yellow;
        ResetButton();
    }

    void ResetButton()
    {
        for(int i=0; i < buttons.Length; i++)
        {
            buttons[i].active = false;
        }

        active = false;
    }
}
