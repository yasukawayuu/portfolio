using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.ParticleSystemJobs;

public enum LASERSTATE
{
    LASER_NON,
    LASER_SETTING,
    LASER_BEAM,
    LASER_DAMAGE,

    LASER_NUM,
}

public class MonitorController : MonoBehaviour
{
    GameObject player;  // プレイヤー
    Transform playerTransform;

    GameObject boss; // ボス
    Transform bossTransform;

    public ParticleSystem laser; // レーザー
    LASERSTATE laserState;

    public Material[] AImaterials;
    private Renderer meshRenderer;
    private Material material;

    public Texture[] AI;

    Transform monitorTransform;

    float angle;
    float xPos;
    float yPos;
    float zPos;
    Vector3 pos;

    Vector3 laserTargetPos;
    public float monitorRadius = 5.0f;
    public float lazeRadius = 6.5f;

    int dframe = 0;
    float frame = 0.0f;

    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        playerTransform = player.transform;
        boss = GameObject.Find("Boss");
        bossTransform = boss.transform;
        monitorTransform = this.transform;
        laser.gameObject.SetActive(false);
        laserState = LASERSTATE.LASER_NON;

        meshRenderer = GetComponent<Renderer>();
        material = meshRenderer.material;

    }
   
    void FixedUpdate()
    {
        // モニター更新
        if (laserState == LASERSTATE.LASER_NON || laserState == LASERSTATE.LASER_DAMAGE)
            MonitorUpdate();

        // レーザー
        LaserUpdate();
    }

    void MonitorUpdate()
    {
        // プレイヤーの方向を向く
        monitorTransform.LookAt(playerTransform);
        monitorTransform.Rotate(new Vector3(0.0f, 90.0f, 0.0f));

        //位置の更新
        angle = GetAngle(playerTransform.position, bossTransform.position);
        xPos = -monitorRadius * Mathf.Cos(angle * Mathf.PI / 180.0f);
        yPos = 3.0f * Mathf.Cos(monitorTransform.rotation.z * Mathf.PI / 180.0f);
        zPos = -monitorRadius * Mathf.Sin(angle * Mathf.PI / 180.0f);
        pos = new Vector3(bossTransform.position.x + xPos, monitorTransform.position.y, bossTransform.position.z + zPos);
        monitorTransform.position = pos;
    }

    void LaserUpdate()
    {
        frame += 1.0f / 60.0f;
        switch (laserState)
        {
            case LASERSTATE.LASER_NON:
                LazerNonUpdate();    //通常時
                break;
            case LASERSTATE.LASER_SETTING:
                LazerSettingUpdate();//レーザー準備
                break;
            case LASERSTATE.LASER_BEAM:
                LaserBeam();         //レーザー発射
                break;
            case LASERSTATE.LASER_DAMAGE:
                LaserDamage();       //モニター点滅
                break;
        }
    }

    void LazerNonUpdate()
    {
        if ((frame / 3.0f) > 1.0f)
        {
            laserState = LASERSTATE.LASER_SETTING;
            laser.gameObject.transform.position = new Vector3(monitorTransform.position.x - monitorRadius * Mathf.Cos(angle * Mathf.PI / 180.0f), yPos, monitorTransform.position.z - monitorRadius * Mathf.Sin(angle * Mathf.PI / 180.0f));
            laser.gameObject.transform.LookAt(playerTransform.position + new Vector3(0.0f, 0.5f, 0.0f));
            material.SetTexture("_MainTex", AI[2]);
            FrameReset();
        }
    }

    void LazerSettingUpdate()
    {
        if ((frame / 0.5f) > 1.0f)
        {
            laser.gameObject.SetActive(true);
            laserState = LASERSTATE.LASER_BEAM;
            FrameReset();
        }
    }

    void LaserBeam()
    {
        if ((frame / 1.5f) > 1.0f)
        {
            laser.gameObject.SetActive(false);
            laserState = LASERSTATE.LASER_NON;
            material.SetTexture("_MainTex", AI[0]);
            FrameReset();
        }
    }

    void LaserDamage()
    {
        dframe++;
        if (dframe % 5 == 1)
        {
            //if (meshRenderer.material == AImaterials[0]) meshRenderer.material = AImaterials[1];
            //else meshRenderer.material = AImaterials[0];
            if (material.GetTexture("_MainTex") == AI[0]) material.SetTexture("_MainTex", AI[1]);
            else material.SetTexture("_MainTex", AI[0]);
            Debug.Log(material.GetTexture("_MainTex"));
        }
        if ((frame / 1.5f) > 1.0f)
        {
            dframe = 0;
            //material = AImaterials[0];
            material.SetTexture("_MainTex", AI[0]);
            laserState = LASERSTATE.LASER_SETTING;
            FrameReset();
        }
    }

    float GetAngle(Vector3 start, Vector3 target)
    {
        Vector3 dt = target - start;
        float rad = Mathf.Atan2(dt.z, dt.x);
        float degree = rad * Mathf.Rad2Deg;

        return degree;
    }

    void FrameReset()
    {
        frame = 0.0f;
    }

    public void SetLaserState(LASERSTATE state)
    {
        laserState = state;
    }

    public LASERSTATE GetLaserState()
    {
        return laserState;
    }
}
