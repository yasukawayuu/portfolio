using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShadowWallController : MonoBehaviour
{
    GameObject ground; // Groundを取得
    GroundJudgeisHidden groundJudgeishidden;

    // Ground情報を渡す
    public void Initialize(GameObject go)
    {
        ground = go;
    }

    void Start()
    {
        // GroundJudgeisHiddenを取得
        groundJudgeishidden = ground.GetComponent<GroundJudgeisHidden>();
    }

    void Update()
    {
        DeleteShadowWall();
    }

    // ShadowWallを削除
    void DeleteShadowWall()
    {
        // GroundInfoの中にisHiddenが否のものを探す
        for (int y = 0; y < groundJudgeishidden.groundsplitY; y++)
        {
                for (int x = 0; x < groundJudgeishidden.groundsplitX; x++)
                {
                            Destroy(gameObject);
                            groundJudgeishidden.groundinfo[x, y].isUseShadowWall = false;
                }
        }
        //// GroundInfoの中にisHiddenが否のものを探す
        //for (int y = 0; y < groundJudgeishidden.groundsplitY; y++)
        //{
        //    if(gameObject.transform.position.z == (-groundJudgeishidden.groundpointDepth * 5) + groundJudgeishidden.groundpointDepth * y)
        //    {
        //        for (int x = 0; x < groundJudgeishidden.groundsplitX; x++)
        //        {
        //            if (gameObject.transform.position.x == (-groundJudgeishidden.groundpointWidth * 5) + groundJudgeishidden.groundpointWidth * x)
        //            {
        //                // 座標が隠れていないとき
        //                if (groundJudgeishidden.groundinfo[x, y].isHidden == false)
        //                {
        //                    Destroy(gameObject);
        //                    groundJudgeishidden.groundinfo[x, y].isUseShadowWall = false;
        //                }
        //            }
        //        }
        //    }
        //}
    }
}
