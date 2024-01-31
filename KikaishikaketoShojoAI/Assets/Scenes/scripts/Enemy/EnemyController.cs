using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
public class EnemyController : MonoBehaviour
{
    GameObject player;                 // Playerを取得
    PlayerController playerController; // PlayerControllerを取得
    SearchPlayer1 searchPlayer1;       // SearchPlayerを取得
    
    [SerializeField]
    [Tooltip("巡回する地点の配列")]
    GameObject[] waypoints;            // 巡回する地点の配列
    private int currentWaypointIndex;  // 現在の目的地

    NavMeshAgent navMeshAgent;         // NaviMeshAgentを取得

    [Tooltip("キャラクターの巡回スピード")]
    public float walkspeed = 5f;
    [Tooltip("キャラクターの追尾スピード")]
    public float runspeed = 7f;

    [SerializeField]
    [Tooltip("一点に留まるエネミー")]
    private bool isStayEnemy;          // 一点に留まるエネミーかどうか

    [SerializeField]
    [Tooltip("回転する")]
    private bool isRotate;             // 回転するかどうか

    private Vector3 initialPos;        // 初期座標
    private float initialVelY;         // 初期角度
    public Vector3 angularVelocity;    // 回転速度

    void Start()
    {
        // Playerを取得
        player = GameObject.Find("Player");
        // PlayerControllerを取得
        playerController = player.GetComponent<PlayerController>();

        // SearchPlayerを取得
        searchPlayer1 = GetComponent<SearchPlayer1>();

        // NaviMeshAgentを取得
        navMeshAgent = GetComponent<NavMeshAgent>();
        // 最初の目的地を入れる
        if (isStayEnemy == false)
            navMeshAgent.SetDestination(waypoints[0].transform.position);

        // 初期座標を取得
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

    // Enemyの目的地を設定
    void SetEnemyDestination()
    {
        if (player==null || playerController.isHidden == true)
        {

            // 巡回する地点へ移動
            navMeshAgent.SetDestination(waypoints[currentWaypointIndex].transform.position);
        }
        else 
        {
            if(searchPlayer1.invaded==true)
            // Playerの方向へ移動
            navMeshAgent.destination = player.transform.position;
        }

        // 目的地点までの距離(remainingDistance)が目的地の手前までの距離(stoppingDistance)以下になったら
        if (navMeshAgent.remainingDistance <= navMeshAgent.stoppingDistance)
        {
            // 目的地の番号を１更新（右辺を剰余演算子にすることで目的地をループさせれる）
            currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.Length;
            // 目的地を次の場所に設定
            navMeshAgent.SetDestination(waypoints[currentWaypointIndex].transform.position);
        }
    }

    // StayEnemyの目的地を設定
    void SetStayEnemyDestination()
    {
        if ( !searchPlayer1.invaded || playerController.isHidden == true)
        {
            // 初期位置へ移動
            navMeshAgent.SetDestination(initialPos);

            // Enemyの回転
            EnemyRotate();
        }
        else
        {
            if (searchPlayer1.invaded == true)
            {
                // Playerの方向へ移動
                navMeshAgent.destination = player.transform.position;
                navMeshAgent.isStopped = false;
            }
        }

        // 目的地点までの距離(remainingDistance)が目的地の手前までの距離(stoppingDistance)以下になったら
        if (navMeshAgent.remainingDistance <= navMeshAgent.stoppingDistance)
        {
            navMeshAgent.isStopped = true;
        }
    }

    // StayEnemyの視界を回転
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

    // Enemyの移動速度を設定
    void SetSpeed()
    {
        if (searchPlayer1.invaded == true) navMeshAgent.speed = runspeed;
        else navMeshAgent.speed = walkspeed;
    }
}