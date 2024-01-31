using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RespawnMaker : MonoBehaviour
{
    GameObject player;                 // playerを取得
    PlayerController playerController; // playercontrollerの取得

    public Vector3 pos; // リスポーン座標
    private int frame;  // リスポーンフレーム

    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");        // playerを取得
        playerController = player.GetComponent<PlayerController>(); // playercontrollerの取得
        frame = 0;
    }
    void Update()
    {
        // Playerが非アクティブの時
        if (player.activeInHierarchy == false)
        {
            frame++;
            // 30フレーム後にリスポーンする
            if (frame % 30 == 0)
            {
                RespawnPlayer();
            }
        }

    }

    // Playerと接触したときにリスポーンする
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

    // Playerをリスポーンさせる
    private void RespawnPlayer()
    {
        player.SetActive(true);
    }
}
