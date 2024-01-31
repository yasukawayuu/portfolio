using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEngine.UI;

public class SearchPlayerSensor : MonoBehaviour
{
    [SerializeField] float searchAngle = 60f;                // 視野角
    [SerializeField] int len = 14;                           // 視界距離
    [SerializeField] private float searchAngletrue = 180f;    // 視認しているときの視野角
    float searchAnglefalse;                                  // 視認していないときの視野角

    [SerializeField]
    [Tooltip("追いかける対象")]
    private GameObject player;

    [SerializeField]
    private Text text;

    private Ray ray;

    private Vector3 positionDiff;             // 自身（敵）とプレイヤーの距離ベクトル
    public bool invaded;                      // 視野内にいるかどうかの識別子

    //センサー
    [SerializeField]
    Alarm alarm;

    [SerializeField]
    GameObject walk;
    [SerializeField]
    GameObject search;
    public AudioClip seWalk;
    AudioSource audioSourceWalk;
    public AudioClip seSearch;
    AudioSource audioSourceSearch;

    private Vector3 oldPos;
    void Start()
    {
        searchAnglefalse = searchAngle;

        // Rayを生成
        ray = new Ray(transform.position, (player.transform.position - transform.position));
        audioSourceWalk = walk.GetComponent<AudioSource>();
        audioSourceSearch = search.GetComponent<AudioSource>();
        oldPos = transform.position;
    }

    void Update()
    {

        if (Time.timeScale > 0)
        {
            positionDiff = player.transform.position - transform.position;  // 自身（敵）とプレイヤーの距離
            var angle = Vector3.Angle(transform.forward, positionDiff);  // 敵のZ軸　と　敵とプレイヤーのベクトルの角度を取る

            // 視認しているかどうか
            if ((positionDiff.magnitude <= len && angle <= searchAngle) && (player.GetComponent<PlayerController>().isHidden == false))
            {
                RaycastHit hit; // 衝突したオブジェクト
                ray = new Ray(transform.position + (player.transform.position - transform.position) * 0.1f, (player.transform.position - transform.position));
                if (Physics.Raycast(ray, out hit))
                {
                    // オブジェクトがPlayer時取得する
                    if (hit.collider.gameObject.CompareTag("Player"))
                    {
                        invaded = true;
                        text.enabled = true;
                    }
                }
            }
            else
            {
                invaded = false;
                text.enabled = false;
            }

            // 視認している場合視野角を広げる
            if (invaded == true)
            {
                searchAngle = searchAngletrue;

                if (audioSourceSearch.isPlaying == false)
                {
                    audioSourceSearch.PlayOneShot(seSearch);
                }
            }
            else
            {
                searchAngle = searchAnglefalse;
            }


            if (alarm.active == true)
            {
                invaded = true;
                text.enabled = true;
            }


            RaycastHit p; // 衝突したオブジェクト
            ray = new Ray(transform.position + (player.transform.position - transform.position) * 0.1f, (player.transform.position - transform.position));
            if (Physics.Raycast(ray, out p, 1))
            {
                // オブジェクトがPlayer時取得する
                if (p.collider.gameObject.CompareTag("Player"))
                {
                    alarm.ResetAlarm();
                    invaded = false;
                    text.enabled = false;
                }
            }


            //移動していたら
            if (oldPos.x != transform.position.x || oldPos.z != transform.position.z)
            {
                if (audioSourceWalk.isPlaying == false)
                {
                    audioSourceWalk.PlayOneShot(seWalk);
                }
                oldPos = transform.position;
            }
            else
            {
                audioSourceWalk.Stop();
            }

        }
        else
        {
            audioSourceWalk.Stop();
            audioSourceSearch.Stop();
        }
    }
    
#if UNITY_EDITOR
    private void OnDrawGizmos()
    {
        Handles.color = new Color(1.0f, 0, 0, 0.3f);
        Handles.DrawSolidArc(transform.position, Vector3.up, Quaternion.Euler(0f, -searchAngle, 0f) * transform.forward, searchAngle * 2f, len);
    }
#endif
}
