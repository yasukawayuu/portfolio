using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WallRoll : MonoBehaviour
{
    [SerializeField]
    [Tooltip("ボタンに接続")]
    GimmickButton[] button;
    [SerializeField]
    [Tooltip("チャージに接続")]
    Charger[] chargers;
    private int rotate_cnt = 0;
    private bool rot = false;
    private bool rotateL = true;

    private float angleY;


    [SerializeField]
    private float rotAngle = 90.0f;

    [SerializeField]
    private float rotSpeed = 0.5f;

    public AudioClip se;
    AudioSource audioSource;

    // Start is called before the first frame update
    void Start()
    {
        rotate_cnt = 0;
        rot = false;
        rotateL = true;

        angleY = transform.localEulerAngles.y;
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.timeScale > 0)
        {
            int acnt = 0;
            for (int i = 0; i < button.Length; i++)
            {
                if (button[i].active == true)
                {
                    acnt += 1;
                }
            }

            for (int i = 0; i < chargers.Length; i++)
            {
                if (chargers[i].active == true)
                {
                    acnt += 1;
                }
            }

            //壁回転 ONになっている電源の数が違ったら

            if (rotate_cnt != acnt)
            {
                if (rotate_cnt > acnt)
                {
                    rotateL = false;
                }
                else
                {
                    rotateL = true;
                }
                rotate_cnt = acnt;
                //回転フラグをtrueに
                rot = true;

                if (audioSource.isPlaying == false)
                {
                    audioSource.PlayOneShot(se);
                }
            }

            if (rot == true)
            {
                if (rotateL == true)
                {
                    transform.Rotate(0.0f, rotSpeed, 0.0f);
                    if (transform.localEulerAngles.y >= angleY + rotAngle * rotate_cnt)
                    {
                        transform.rotation = Quaternion.Euler(0.0f, angleY + rotAngle * rotate_cnt, 0.0f);
                        rot = false;
                    }
                }
                else
                {
                    transform.Rotate(0.0f, -rotSpeed, 0.0f);
                    if (transform.localEulerAngles.y <= angleY + rotAngle * rotate_cnt)
                    {
                        transform.rotation = Quaternion.Euler(0.0f, angleY + rotAngle * rotate_cnt, 0.0f);
                        rot = false;
                    }
                }

            }
        }

    }
}
