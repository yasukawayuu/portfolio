using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class TitleMate : MonoBehaviour
{
    [SerializeField]
    GameObject waypoint;            // 巡回する地点の配列

    NavMeshAgent navMeshAgent;         // NaviMeshAgentを取得

    [Tooltip("キャラクターの巡回スピード")]
    public float walkspeed = 5f;
    void Start()
    {
        // NaviMeshAgentを取得
        navMeshAgent = GetComponent<NavMeshAgent>();

        navMeshAgent.speed = walkspeed;
    }
    void Update()
    {
        if (Time.timeScale > 0)
        {
            navMeshAgent.SetDestination(waypoint.transform.position);
        }
    }
}
