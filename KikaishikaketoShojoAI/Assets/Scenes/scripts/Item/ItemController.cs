using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemController : MonoBehaviour
{
    private Vector3 initPos; // 初期座標 

    void Start()
    {
        // 初期座標を取得
        initPos = gameObject.transform.position;
    }

    // Itemの座標をリセット
    public void ResetItem()
    {
        AttachObject ao = gameObject.GetComponent<AttachObject>();
        ao.ResetItemState();
        gameObject.transform.position = initPos;
    }
}
