using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//using UnityEngine.AI;

public class EnemySkyController : MonoBehaviour
{
    enum State
    {
        CHASE,
        MOVE,
        FLY,

        NONE
    }
    State enemyState;
    GameObject player;                 // Player���擾
    PlayerController playerController; // PlayerController���擾
    SkySearchPlayer1 searchPlayer1;       // SearchPlayer���擾

    [SerializeField]
    [Tooltip("���񂷂�n�_�̔z��")]
    GameObject[] waypoints;            // ���񂷂�n�_�̔z��
    private int currentWaypointIndex;  // ���݂̖ړI�n
    
    [Tooltip("�L�����N�^�[�̏���X�s�[�h")]
    public float walkspeed = 2.5f;
    [Tooltip("�L�����N�^�[�̒ǔ��X�s�[�h")]
    public float runspeed = 7.0f;

    [SerializeField]
    [Tooltip("��]���x")]
    private float rotspeed = 0.025f;

    private Vector3 initialPos;        // �������W
    public Vector3 angularVelocity;    // ��]���x

    //��s���鍂��
    [SerializeField]
    [Tooltip("���x")]
    private float altitude = 3.0f;

    //���V�Ԃ��o��
    private bool fly = false;

    private bool chase = false;

    //�O�ɕǂ��L��Γo��
    //private bool climb = false;
    //���Ƃ���ꏊ
    private float ground;

    void Start()
    {
        enemyState = State.MOVE;
        // Player���擾
        player = GameObject.Find("Player");
        // PlayerController���擾
        playerController = player.GetComponent<PlayerController>();

        // SearchPlayer���擾
        searchPlayer1 = GetComponent<SkySearchPlayer1>();
        
        // �������W���擾
        initialPos = gameObject.transform.position;

        enemyState = State.MOVE;
    }
    void Update()
    {
        if (Time.timeScale > 0)
        {
            switch (enemyState)
            {
                case State.CHASE:
                    ChaseEnemy();
                    break;
                case State.MOVE:
                    MoveEnemy();
                    Hovering();
                    break;
                case State.FLY:
                    FlyEnemy();
                    break;
            }
        }
    }

    void StayEnemy()
    {
        gameObject.transform.Rotate(angularVelocity * Time.deltaTime);
    }

    void MoveEnemy()
    {
        Vector3 wayp = waypoints[currentWaypointIndex].transform.position;
        wayp.y = transform.position.y;
        float speed = walkspeed;

        //�T�[�`
        if (searchPlayer1.invaded == true)
        {
            enemyState = State.CHASE;
            chase = true;
        }

        var direction = wayp - transform.position;
        direction.y = 0;
        var lookRotation = Quaternion.LookRotation(direction, Vector3.up);
        transform.rotation = Quaternion.Lerp(transform.rotation, lookRotation, rotspeed);

        Vector3 pos = transform.position;
        if(transform.position.y < (transform.localScale.y / 2) + 0.1f)
        {
            pos.y = (transform.localScale.y / 2) + 0.1f;
        }

        //�ړ�����
        transform.position = Vector3.MoveTowards(pos, wayp, speed * Time.deltaTime);
        
        //WayPoint�ɓ���
        if (Physics.OverlapSphere(wayp, 0).Length > 0)
        {
            if (searchPlayer1.invaded != true)
            {
                // targetPos��Collider�ɐG��Ă���ꍇ
                // �ړI�n�̔ԍ����P�X�V�i�E�ӂ���]���Z�q�ɂ��邱�ƂŖړI�n�����[�v�������j
                currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.Length;
            }
            else
            {
                searchPlayer1.Search();
            }
        }

        if(CheckWall() == true)
        {
            enemyState = State.FLY;
            chase = false;
        }
    }

    void ChaseEnemy()
    {

        Vector3 wayp = player.transform.position;
        float speed = runspeed;


        //�v���C���[�����Ȃ��A�e�ɉB��Ă���
        if (player == null || playerController.isHidden == true)
        {
            searchPlayer1.Search();
            enemyState = State.MOVE;
        }
        else
        {
            //�T�[�`
            if (searchPlayer1.invaded == false)
            {
                enemyState = State.MOVE;
            }
        }

        var direction = wayp - transform.position;
        direction.y = 0;
        var lookRotation = Quaternion.LookRotation(direction, Vector3.up);
        transform.rotation = Quaternion.Lerp(transform.rotation, lookRotation, rotspeed);

        Vector3 pos = transform.position;
        if (transform.position.y < (transform.localScale.y / 2) + 0.1f)
        {
            pos.y = (transform.localScale.y / 2) + 0.1f;
        }

        //�ړ�����
        transform.position = Vector3.MoveTowards(pos, wayp, speed * Time.deltaTime);


        if (CheckWall() == true)
        {
            enemyState = State.FLY;
            chase = true;
        }
    }
    
    void FlyEnemy()
    {
        if (CheckWall() == true)
        {
            Vector3 pos = transform.position;
            pos.y += 0.05f;

            transform.position = pos;
            //climb = true;
        }
        else
        {
            if (chase == true)
            {
                ChaseEnemy();
                if (player == null || playerController.isHidden == true)
                {
                    searchPlayer1.Search();
                    MoveEnemy();
                }
                else
                {
                    //�T�[�`
                    if (searchPlayer1.invaded == false)
                    {
                        MoveEnemy();
                    }
                }
            }
            else
            {
                MoveEnemy();
            }
            
            if (CheckGround() == false)
            {
                if (chase == true)
                {
                    enemyState = State.CHASE;
                }
                else
                {
                    enemyState = State.MOVE;
                }
            }
        }
        
    }

    void Hovering()
    {
        Vector3 pos = transform.position;

        if(transform.position.y > altitude)
        {
            fly = false;
        }
        else if(transform.position.y < altitude - 0.5f)
        {
            fly = true;
        }

        if (fly)
        {
            pos.y += 0.005f;
        }
        else
        {
            pos.y -= 0.005f;
        }

        transform.position = pos;
        
    }
    bool CheckWall()
    {
        Vector3 rayPosition = transform.position + Vector3.down;
        Vector3 dir = transform.forward;
        Ray ray = new Ray(rayPosition, dir);
        Debug.DrawRay(ray.origin, ray.direction * 2.0f, Color.green);

        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, 2.0f))
        {
            if (hit.collider.name != "Player")
            {
                return true;
            }
        }
        return false;
    }

    bool CheckGround()
    {
        Vector3 rayPosition = transform.position + Vector3.down;
        Vector3 dir = new Vector3(0,-0.9f,0);
        Ray ray = new Ray(rayPosition, dir);
        Debug.DrawRay(ray.origin, ray.direction * altitude, Color.green);

        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, altitude))
        {
            return true;
        }
        return false;
    }
}