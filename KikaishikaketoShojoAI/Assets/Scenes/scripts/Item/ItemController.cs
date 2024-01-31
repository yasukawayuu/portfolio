using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemController : MonoBehaviour
{
    private Vector3 initPos; // �������W 

    void Start()
    {
        // �������W���擾
        initPos = gameObject.transform.position;
    }

    // Item�̍��W�����Z�b�g
    public void ResetItem()
    {
        AttachObject ao = gameObject.GetComponent<AttachObject>();
        ao.ResetItemState();
        gameObject.transform.position = initPos;
    }
}
