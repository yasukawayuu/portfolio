using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShadowWallMaker : MonoBehaviour
{
    GameObject ground; // Ground���擾
    GroundJudgeisHidden groundJudgeishidden;

    [SerializeField]
    GameObject prefab; // ShadowWall�̃v���n�u

    void Start()
    {
        // Ground���擾
        ground = gameObject;
        // GroundJudgeisHidden���擾
        groundJudgeishidden = ground.GetComponent<GroundJudgeisHidden>();
    }

    void Update()
    {
        CreateShadowWall();
    }

    // ShadowWall�𐶐�
    void CreateShadowWall()
    {
        // GroundInfo�̒���isHidden���^�̂��̂�T��
        for (int y = 0; y < groundJudgeishidden.groundsplitY; y++)
        {
            for (int x = 0; x < groundJudgeishidden.groundsplitX; x++)
            {
                // ���W���B��Ă��Ă��v���n�u�𐶐����Ă��Ȃ��Ƃ�
                if ((groundJudgeishidden.groundinfo[x, y].isHidden == true)&& (groundJudgeishidden.groundinfo[x, y].isUseShadowWall == false))
                {
                    // Cube�v���n�u�����ɁA�C���X�^���X�𐶐��A
                    Instantiate(prefab, groundJudgeishidden.groundinfo[x, y].pos, Quaternion.identity).GetComponent<ShadowWallController>().Initialize(gameObject);
                    groundJudgeishidden.groundinfo[x, y].isUseShadowWall = true;
                }
            }
        }
    }
}
