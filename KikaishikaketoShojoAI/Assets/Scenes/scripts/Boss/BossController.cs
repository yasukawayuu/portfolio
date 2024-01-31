using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossController : MonoBehaviour
{
    GameObject player;  // プレイヤー
    Transform playerTransform;

    GameObject monitor; // ボスのモニター
    Transform monitorTransform;
    MonitorController monitorController;

    [SerializeField]
    GimmickConcent[] life;
    public int damage = 0;
    int damagecnt = 0;


    [SerializeField]
    GameObject se;
    public AudioClip sedamage;
    AudioSource audioSourceDamage;

    [SerializeField]
    GameObject sela;
    public AudioClip selaser;
    AudioSource audioSourceLaser;

    [SerializeField]
    GoalController goal;
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        playerTransform = player.transform;
        monitor = GameObject.Find("monitor");
        monitorTransform = monitor.transform;
        monitorController = monitor.GetComponent<MonitorController>();
        audioSourceDamage = se.GetComponent<AudioSource>();

        audioSourceLaser = se.GetComponent<AudioSource>();
    }

    void FixedUpdate()
    {
        if(Time.timeScale == 0)
        {
            audioSourceLaser.Stop();
            audioSourceDamage.Stop();
        }


        //ダメージを受けた時
        damagecnt = 0;
        for (int i = 0;i < life.Length; i++)
        {
            if(life[i].active == true)
            {
                damagecnt += 1;
            }
        }

        if (damagecnt != damage)
        {
            monitorController.SetLaserState(LASERSTATE.LASER_DAMAGE);
            damage = damagecnt;
            if(audioSourceDamage.isPlaying == false)
            {
                audioSourceDamage.PlayOneShot(sedamage);
            }
        }

        if(damage >= life.Length)
        {
            //CLEAR
            goal.NextStage();
        }

        if (monitorController.GetLaserState() == LASERSTATE.LASER_BEAM)
        {
            if (audioSourceDamage.isPlaying == false)
            {
                audioSourceLaser.PlayOneShot(selaser);
            }
            else
            {
                //audioSourceLaser.Stop();
            }
        }
    }

}
