using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShadowWallController : MonoBehaviour
{
    GameObject ground; // Ground���擾
    GroundJudgeisHidden groundJudgeishidden;

    // Ground����n��
    public void Initialize(GameObject go)
    {
        ground = go;
    }

    void Start()
    {
        // GroundJudgeisHidden���擾
        groundJudgeishidden = ground.GetComponent<GroundJudgeisHidden>();
    }

    void Update()
    {
        DeleteShadowWall();
    }

    // ShadowWall���폜
    void DeleteShadowWall()
    {
        // GroundInfo�̒���isHidden���ۂ̂��̂�T��
        for (int y = 0; y < groundJudgeishidden.groundsplitY; y++)
        {
                for (int x = 0; x < groundJudgeishidden.groundsplitX; x++)
                {
                            Destroy(gameObject);
                            groundJudgeishidden.groundinfo[x, y].isUseShadowWall = false;
                }
        }
        //// GroundInfo�̒���isHidden���ۂ̂��̂�T��
        //for (int y = 0; y < groundJudgeishidden.groundsplitY; y++)
        //{
        //    if(gameObject.transform.position.z == (-groundJudgeishidden.groundpointDepth * 5) + groundJudgeishidden.groundpointDepth * y)
        //    {
        //        for (int x = 0; x < groundJudgeishidden.groundsplitX; x++)
        //        {
        //            if (gameObject.transform.position.x == (-groundJudgeishidden.groundpointWidth * 5) + groundJudgeishidden.groundpointWidth * x)
        //            {
        //                // ���W���B��Ă��Ȃ��Ƃ�
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
