using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShadowWallMaker : MonoBehaviour
{
    GameObject ground; // Groundを取得
    GroundJudgeisHidden groundJudgeishidden;

    [SerializeField]
    GameObject prefab; // ShadowWallのプレハブ

    void Start()
    {
        // Groundを取得
        ground = gameObject;
        // GroundJudgeisHiddenを取得
        groundJudgeishidden = ground.GetComponent<GroundJudgeisHidden>();
    }

    void Update()
    {
        CreateShadowWall();
    }

    // ShadowWallを生成
    void CreateShadowWall()
    {
        // GroundInfoの中にisHiddenが真のものを探す
        for (int y = 0; y < groundJudgeishidden.groundsplitY; y++)
        {
            for (int x = 0; x < groundJudgeishidden.groundsplitX; x++)
            {
                // 座標が隠れていてかつプレハブを生成していないとき
                if ((groundJudgeishidden.groundinfo[x, y].isHidden == true)&& (groundJudgeishidden.groundinfo[x, y].isUseShadowWall == false))
                {
                    // Cubeプレハブを元に、インスタンスを生成、
                    Instantiate(prefab, groundJudgeishidden.groundinfo[x, y].pos, Quaternion.identity).GetComponent<ShadowWallController>().Initialize(gameObject);
                    groundJudgeishidden.groundinfo[x, y].isUseShadowWall = true;
                }
            }
        }
    }
}
