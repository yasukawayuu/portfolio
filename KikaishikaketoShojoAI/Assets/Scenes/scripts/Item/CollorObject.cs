using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollorObject : MonoBehaviour
{
    public Material[] color;
    private MeshRenderer meshRenderer;
    private Material material;
    private int colorMaxFrame;
    private int colorFrame;
    private bool colorFlag;
    private Color addcolor;

    void Start()
    {
        meshRenderer = GetComponent<MeshRenderer>();
        material = meshRenderer.material;

        colorFrame = 0;
        colorMaxFrame = 120;
        colorFlag = false;
        addcolor = new Color(0.004f, 0, 0.01f, 0);
    }

    void Update()
    {
        ChangeColor();
    }

    void ChangeColor()
    {// 干渉できるオブジェクトということを強調する
        material.color += addcolor;


        if (colorFlag == false) addcolor = new Color(0.004f, 0, 0.01f, 0);
        else addcolor = new Color(-0.004f, 0, -0.01f, 0);

        if (colorFrame == colorMaxFrame)
        {
            if (colorFlag == false) colorFlag = true;
            else colorFlag = false;

            colorFrame = 0;
        }

        colorFrame++;
    }
}
