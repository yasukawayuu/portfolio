using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RespawnMaker : MonoBehaviour
{
    GameObject player;                 // player���擾
    PlayerController playerController; // playercontroller�̎擾

    public Vector3 pos; // ���X�|�[�����W
    private int frame;  // ���X�|�[���t���[��

    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");        // player���擾
        playerController = player.GetComponent<PlayerController>(); // playercontroller�̎擾
        frame = 0;
    }
    void Update()
    {
        // Player����A�N�e�B�u�̎�
        if (player.activeInHierarchy == false)
        {
            frame++;
            // 30�t���[����Ƀ��X�|�[������
            if (frame % 30 == 0)
            {
                RespawnPlayer();
            }
        }

    }

    // Player�ƐڐG�����Ƃ��Ƀ��X�|�[������
    private void OnCollisionEnter(Collision other)
    {
        if(other.gameObject.CompareTag("Player") && player.activeInHierarchy == true)
        {
            playerController.SetRespawnPos(pos);
            playerController.SetRespawnItem();
            player.SetActive(false);
            player.transform.position = pos;
        }
    }

    // Player�����X�|�[��������
    private void RespawnPlayer()
    {
        player.SetActive(true);
    }
}
