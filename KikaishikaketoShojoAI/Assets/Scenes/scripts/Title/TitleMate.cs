using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class TitleMate : MonoBehaviour
{
    [SerializeField]
    GameObject waypoint;            // ���񂷂�n�_�̔z��

    NavMeshAgent navMeshAgent;         // NaviMeshAgent���擾

    [Tooltip("�L�����N�^�[�̏���X�s�[�h")]
    public float walkspeed = 5f;
    void Start()
    {
        // NaviMeshAgent���擾
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
