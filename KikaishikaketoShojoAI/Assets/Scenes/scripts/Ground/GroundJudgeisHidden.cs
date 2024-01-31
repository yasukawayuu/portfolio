using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GroundJudgeisHidden : MonoBehaviour
{
    public int groundsplitX = 15; // Groundの横の分割数
    public int groundsplitY = 15; // Groundの縦の分割数
    public float groundWidth;     // Groundの横幅
    public float groundDepth;     // Groundの縦幅
    public float groundpointWidth;// Groundの各地点の横間隔
    public float groundpointDepth;// Groundの各地点の縦間隔

    GameObject sun;             // Sunを取得
    GameObject player;          // playerを取得

    public GroundInfo[,] groundinfo;   // GroundInfoの作成

    Vector3 origin;             // 光源の位置
    Vector3 direction;          // ターゲットの位置
    Ray ray;                    // Raycast

    //test
    int frame = 0;

    void Start()
    {
        // Sunを取得
        sun = GameObject.Find("Sun");
        // Playerを取得
        player = GameObject.Find("Player");

        // Groundの情報を取得
        groundWidth = 3;
        groundDepth = 3;

        // Groundの各地点の間隔を設定
        groundpointWidth = groundWidth;
        groundpointDepth = groundDepth;

        // groundinfoの初期化
        groundinfo = new GroundInfo[groundsplitX, groundsplitY];
        for (int y = 0; y < groundsplitY; y++)
        {
            for (int x = 0; x < groundsplitX; x++)
            {
                groundinfo[x, y].pos
                    = new Vector3((-groundpointWidth * 5) + groundpointWidth * x, 0.0f, (-groundpointDepth * 5) + groundpointDepth * y);
                groundinfo[x, y].posInt = new Vector2Int(x, y);
                groundinfo[x, y].isHidden = true;
                groundinfo[x, y].isUseShadowWall = false;
            }
        }

        // 初期位置を取得
        origin = new Vector3(0, 0, 0);
        // 初期位置を設定
        direction = new Vector3(0, 0, 0);
        // Rayを生成
        ray = new Ray(origin, direction);
    }

    void Update()
    {
        // test
        frame++;
        if (frame % 10 == 0)
        {
            for (int y = 0; y < groundsplitY; y++)
            {
                for (int x = 0; x < groundsplitX; x++)
                {
                    groundinfo[x, y].pos.x = player.transform.position.x + (-groundpointWidth * 5) + groundpointWidth * x;
                    groundinfo[x, y].pos.z = player.transform.position.z + (-groundpointDepth * 5) + groundpointDepth * y;
                    groundinfo[x, y].isHidden = true;
                    groundinfo[x, y].isUseShadowWall = false;
                }
            }
        }

        // 光源の位置を取得
        origin = sun.transform.position;

        GroundJudge();
    }

    // GroundInfoの情報を設定
    void GroundJudge()
    {
        // Groundのすべての地点を参照する
        for (int y = 0; y < groundsplitY; y++)
        {
            for (int x = 0; x < groundsplitX; x++)
            {
                CalcRaycast(x, y);
                HitCheckRaycast(x, y);
            }
        }
    }

    // Rayの向きを計算
    void CalcRaycast(int x, int y)
    {
        // Playerの位置を取得
        direction = groundinfo[x, y].pos;
        // Rayを生成
        ray = new Ray(origin, (direction - origin));
    }

    // Rayの衝突判定
    void HitCheckRaycast(int x, int y)
    {
        RaycastHit hit; // 衝突したオブジェクト

        // Rayの衝突判定
        if (Physics.Raycast(ray, out hit))
        {
            // 衝突したオブジェクトの名前を取得
            string name = hit.collider.gameObject.tag;
            // 影にいない場合
            if (name == "Ground")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "ShadowWall")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "Enemy")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "Player")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "Respawn")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "NPC")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "Untagged")
            {
                groundinfo[x, y].isHidden = false;
            }
            // 影にいる場合
            else
            {
                groundinfo[x, y].isHidden = true;
                Debug.DrawRay(origin, (direction - origin), new Color(1.0f, 0.0f, 0.0f, 1.0f), 0.1f, true);
            }
        }

    }
}

// フィールドの地点の情報クラス
public struct GroundInfo
{
    public bool isHidden;     // 隠れているかどうか
    public Vector3 pos;       // 地点の座標
    public Vector2Int posInt; // 地点の配列

    public bool isUseShadowWall; // ShadowWallを生成しているかどうか
}