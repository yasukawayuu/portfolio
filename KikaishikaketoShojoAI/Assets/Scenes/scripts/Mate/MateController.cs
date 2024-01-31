using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MateController : MonoBehaviour
{
    public float moveSpeed = 3f;
    public float moveDistance = 300f;
    public float stopDistance = 2f;

    public GameObject player;
    private Transform playerTransform;
    private Vector3 targetPos;

    private Rigidbody rb;

    void Start()
    {
        playerTransform = player.GetComponent<Transform>();
        targetPos = playerTransform.position;
        rb = this.GetComponent<Rigidbody>();
    }

    void Update()
    {
        if (Time.timeScale > 0)
        {
            AutoMovement();
        }
    }

    void AutoMovement()
    {
        if (player != null)
        {
            //プレイヤーの方を向く
            Vector3 targetPos = playerTransform.position;
            targetPos.y = transform.position.y;
            transform.LookAt(targetPos);
            
            //プレイヤーの方へ向かう
            float distance = Vector3.Distance(transform.position, playerTransform.position);
            if (distance < moveDistance && distance > stopDistance)
            {
                Quaternion move_rotation = Quaternion.LookRotation(playerTransform.position - transform.position, Vector3.up);
                transform.rotation = Quaternion.Lerp(transform.rotation, move_rotation, 0.1f);
                rb.velocity = transform.forward * moveSpeed;
            }
            else
            {
                rb.velocity = transform.forward*0;
            }
        }
    }
}
