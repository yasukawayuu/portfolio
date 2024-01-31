using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
public class EnemyController : MonoBehaviour
{
    GameObject player;                 // Player���擾
    PlayerController playerController; // PlayerController���擾
    SearchPlayer1 searchPlayer1;       // SearchPlayer���擾
    
    [SerializeField]
    [Tooltip("���񂷂�n�_�̔z��")]
    GameObject[] waypoints;            // ���񂷂�n�_�̔z��
    private int currentWaypointIndex;  // ���݂̖ړI�n

    NavMeshAgent navMeshAgent;         // NaviMeshAgent���擾

    [Tooltip("�L�����N�^�[�̏���X�s�[�h")]
    public float walkspeed = 5f;
    [Tooltip("�L�����N�^�[�̒ǔ��X�s�[�h")]
    public float runspeed = 7f;

    [SerializeField]
    [Tooltip("��_�ɗ��܂�G�l�~�[")]
    private bool isStayEnemy;          // ��_�ɗ��܂�G�l�~�[���ǂ���

    [SerializeField]
    [Tooltip("��]����")]
    private bool isRotate;             // ��]���邩�ǂ���

    private Vector3 initialPos;        // �������W
    private float initialVelY;         // �����p�x
    public Vector3 angularVelocity;    // ��]���x

    void Start()
    {
        // Player���擾
        player = GameObject.Find("Player");
        // PlayerController���擾
        playerController = player.GetComponent<PlayerController>();

        // SearchPlayer���擾
        searchPlayer1 = GetComponent<SearchPlayer1>();

        // NaviMeshAgent���擾
        navMeshAgent = GetComponent<NavMeshAgent>();
        // �ŏ��̖ړI�n������
        if (isStayEnemy == false)
            navMeshAgent.SetDestination(waypoints[0].transform.position);

        // �������W���擾
        initialPos = transform.position;
        initialVelY = transform.rotation.y;
        }
    void Update()
    {
        if (Time.timeScale > 0)
        {
            if (isStayEnemy == true)
            {
                SetStayEnemyDestination();
            }
            else
            {
                SetEnemyDestination();
            }

            SetSpeed();
        }
    }

    // Enemy�̖ړI�n��ݒ�
    void SetEnemyDestination()
    {
        if (player==null || playerController.isHidden == true)
        {

            // ���񂷂�n�_�ֈړ�
            navMeshAgent.SetDestination(waypoints[currentWaypointIndex].transform.position);
        }
        else 
        {
            if(searchPlayer1.invaded==true)
            // Player�̕����ֈړ�
            navMeshAgent.destination = player.transform.position;
        }

        // �ړI�n�_�܂ł̋���(remainingDistance)���ړI�n�̎�O�܂ł̋���(stoppingDistance)�ȉ��ɂȂ�����
        if (navMeshAgent.remainingDistance <= navMeshAgent.stoppingDistance)
        {
            // �ړI�n�̔ԍ����P�X�V�i�E�ӂ���]���Z�q�ɂ��邱�ƂŖړI�n�����[�v�������j
            currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.Length;
            // �ړI�n�����̏ꏊ�ɐݒ�
            navMeshAgent.SetDestination(waypoints[currentWaypointIndex].transform.position);
        }
    }

    // StayEnemy�̖ړI�n��ݒ�
    void SetStayEnemyDestination()
    {
        if ( !searchPlayer1.invaded || playerController.isHidden == true)
        {
            // �����ʒu�ֈړ�
            navMeshAgent.SetDestination(initialPos);

            // Enemy�̉�]
            EnemyRotate();
        }
        else
        {
            if (searchPlayer1.invaded == true)
            {
                // Player�̕����ֈړ�
                navMeshAgent.destination = player.transform.position;
                navMeshAgent.isStopped = false;
            }
        }

        // �ړI�n�_�܂ł̋���(remainingDistance)���ړI�n�̎�O�܂ł̋���(stoppingDistance)�ȉ��ɂȂ�����
        if (navMeshAgent.remainingDistance <= navMeshAgent.stoppingDistance)
        {
            navMeshAgent.isStopped = true;
        }
    }

    // StayEnemy�̎��E����]
    void EnemyRotate()
    {
        if (isRotate == true)
        {
            if (searchPlayer1.invaded == false)
            {
                gameObject.transform.Rotate(angularVelocity * Time.deltaTime);
            }
        }
        else
        {
                if (Mathf.Abs(transform.rotation.y - initialVelY) > 0.2f)
                {
                    if (transform.rotation.y > initialVelY)
                    {
                        transform.Rotate(new Vector3(0, -0.05f, 0));
                    }
                    else
                    {
                        transform.Rotate(new Vector3(0, 0.05f, 0));
                    }
                }
        }
    }

    // Enemy�̈ړ����x��ݒ�
    void SetSpeed()
    {
        if (searchPlayer1.invaded == true) navMeshAgent.speed = runspeed;
        else navMeshAgent.speed = walkspeed;
    }
}