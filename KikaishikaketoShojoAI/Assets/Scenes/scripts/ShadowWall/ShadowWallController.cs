using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShadowWallController : MonoBehaviour
{
    GameObject ground; // Ground‚ğæ“¾
    GroundJudgeisHidden groundJudgeishidden;

    // Groundî•ñ‚ğ“n‚·
    public void Initialize(GameObject go)
    {
        ground = go;
    }

    void Start()
    {
        // GroundJudgeisHidden‚ğæ“¾
        groundJudgeishidden = ground.GetComponent<GroundJudgeisHidden>();
    }

    void Update()
    {
        DeleteShadowWall();
    }

    // ShadowWall‚ğíœ
    void DeleteShadowWall()
    {
        // GroundInfo‚Ì’†‚ÉisHidden‚ª”Û‚Ì‚à‚Ì‚ğ’T‚·
        for (int y = 0; y < groundJudgeishidden.groundsplitY; y++)
        {
                for (int x = 0; x < groundJudgeishidden.groundsplitX; x++)
                {
                            Destroy(gameObject);
                            groundJudgeishidden.groundinfo[x, y].isUseShadowWall = false;
                }
        }
        //// GroundInfo‚Ì’†‚ÉisHidden‚ª”Û‚Ì‚à‚Ì‚ğ’T‚·
        //for (int y = 0; y < groundJudgeishidden.groundsplitY; y++)
        //{
        //    if(gameObject.transform.position.z == (-groundJudgeishidden.groundpointDepth * 5) + groundJudgeishidden.groundpointDepth * y)
        //    {
        //        for (int x = 0; x < groundJudgeishidden.groundsplitX; x++)
        //        {
        //            if (gameObject.transform.position.x == (-groundJudgeishidden.groundpointWidth * 5) + groundJudgeishidden.groundpointWidth * x)
        //            {
        //                // À•W‚ª‰B‚ê‚Ä‚¢‚È‚¢‚Æ‚«
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
