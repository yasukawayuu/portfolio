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
    GameObject player;                 // Playerを取得
    PlayerController playerController; // PlayerControllerを取得
    SkySearchPlayer1 searchPlayer1;       // SearchPlayerを取得

    [SerializeField]
    [Tooltip("巡回する地点の配列")]
    GameObject[] waypoints;            // 巡回する地点の配列
    private int currentWaypointIndex;  // 現在の目的地
    
    [Tooltip("キャラクターの巡回スピード")]
    public float walkspeed = 2.5f;
    [Tooltip("キャラクターの追尾スピード")]
    public float runspeed = 7.0f;

    [SerializeField]
    [Tooltip("回転速度")]
    private float rotspeed = 0.025f;

    private Vector3 initialPos;        // 初期座標
    public Vector3 angularVelocity;    // 回転速度

    //飛行する高さ
    [SerializeField]
    [Tooltip("高度")]
    private float altitude = 3.0f;

    //浮遊間を出す
    private bool fly = false;

    private bool chase = false;

    //前に壁が有れば登る
    //private bool climb = false;
    //床とする場所
    private float ground;

    void Start()
    {
        enemyState = State.MOVE;
        // Playerを取得
        player = GameObject.Find("Player");
        // PlayerControllerを取得
        playerController = player.GetComponent<PlayerController>();

        // SearchPlayerを取得
        searchPlayer1 = GetComponent<SkySearchPlayer1>();
        
        // 初期座標を取得
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

        //サーチ
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

        //移動処理
        transform.position = Vector3.MoveTowards(pos, wayp, speed * Time.deltaTime);
        
        //WayPointに到着
        if (Physics.OverlapSphere(wayp, 0).Length > 0)
        {
            if (searchPlayer1.invaded != true)
            {
                // targetPosがColliderに触れている場合
                // 目的地の番号を１更新（右辺を剰余演算子にすることで目的地をループさせれる）
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


        //プレイヤーが居ない、影に隠れている
        if (player == null || playerController.isHidden == true)
        {
            searchPlayer1.Search();
            enemyState = State.MOVE;
        }
        else
        {
            //サーチ
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

        //移動処理
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
                    //サーチ
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