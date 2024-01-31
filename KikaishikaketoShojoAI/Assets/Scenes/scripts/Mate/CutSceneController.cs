using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum CUTSCENE
{
    CUTSCENE_WALKING,
    CUTSCENE_TALKING,
    CUTSCENE_ENDING,

    CUTSCENE_NUM,
}

public class CutSceneController : MonoBehaviour
{
    public CUTSCENE cutSceneState;

    public GameObject player;
    public GameObject maincamera;

    public float x;

    float frame; //フレーム

    [SerializeField]
    PlayerAnimTalk pa;


    [SerializeField]
    GoalController goal;
    void Start()
    {
        cutSceneState = CUTSCENE.CUTSCENE_WALKING;
        x = 0.0f;
        frame = 0.0f;
        pa.StartWalk();
    }


    void FixedUpdate()
    {
        switch (cutSceneState)
        {
            case CUTSCENE.CUTSCENE_WALKING:
                //CutSceneWlaking()を3.0秒後に呼び出す
                if (x < 12.0f) Invoke(nameof(CutSceneWalking), 1.0f);
                break;
            case CUTSCENE.CUTSCENE_TALKING:
                Invoke(nameof(CutSceneTalking), 1.0f);
                break;
            case CUTSCENE.CUTSCENE_ENDING:
                Invoke(nameof(CutSceneEnding), 1.0f);
                break;
        }
    }

    void CutSceneWalking()
    {
        player.transform.position += new Vector3(0.1f, 0.0f, 0.0f);
        x += 0.1f;
        if (x >= 12.0f)
        {
            CancelInvoke();
            pa.StopWalk();
            cutSceneState = CUTSCENE.CUTSCENE_TALKING;
        }
    }

    void CutSceneTalking()
    {
        gameObject.GetComponent<Talk4>().talkFlag = true;
        maincamera.transform.LookAt(player.transform);
        x = 0.0f;
    }

    void CutSceneEnding()
    {
        pa.StartWalk();
        maincamera.transform.LookAt(player.transform);
        player.transform.position += new Vector3(0.1f, 0.0f, 0.0f);
        x += 0.1f;
        if (x >= 5.0f)
        {
            //次のシーンへ
            goal.NextStage();
        }
    }
}