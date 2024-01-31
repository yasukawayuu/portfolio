using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEditor;
public class SkySearchPlayer1 : MonoBehaviour
{

    [SerializeField] float len = 6.0f;                           // 視界距離

    [SerializeField]
    [Tooltip("追いかける対象")]
    private GameObject player;

    [SerializeField]
    private Text text;

    public bool invaded;                      // 視野内にいるかどうかの識別子

    [SerializeField]
    [Tooltip("どれくらい視線を下に向けるか")]
    private float downAngle = -1.0f;

    private Ray centerray;
    private Vector3 colPosition;

    [SerializeField]
    GameObject move;
    [SerializeField]
    GameObject search;
    public AudioClip seMove;
    AudioSource audioSourceMove;
    public AudioClip seSearch;
    AudioSource audioSourceSearch;
    // Start is called before the first frame update
    void Start()
    {
        text.enabled = false;
        audioSourceMove = move.GetComponent<AudioSource>();
        audioSourceSearch = search.GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.timeScale > 0)
        {
            if (audioSourceMove.isPlaying == false)
            {
                audioSourceMove.PlayOneShot(seMove);
            }
            //探索範囲の中心
            //初期位置の向きを合わせる
            Vector3 dir = new Vector3(0, downAngle, 0) + transform.forward;
            //初期位置　角度指定
            centerray = new Ray(transform.position, dir);
            RaycastHit centerhit;
            if (Physics.Raycast(centerray, out centerhit))
            {
                colPosition = centerhit.point;
            }
            //Rayの可視化
            //開始位置、向き×当たった物までの距離、色
            Debug.DrawRay(centerray.origin, centerray.direction * centerhit.distance, Color.red);

            //探索範囲の中心を利用して円の当たり判定
            //Y軸を無視したX軸とZ軸で判定
            float l;
            Vector3 col = colPosition;
            l = Mathf.Sqrt(Mathf.Pow(player.transform.position.x - col.x, 2)
                + Mathf.Pow(player.transform.position.z - col.z, 2));

            if (l < len)
            {
                //範囲内に入ったプレイヤーへ向かってRayを飛ばす
                //初期位置角度指定
                if (invaded == false)
                {
                    //    invaded = true;
                    //    text.enabled = true;
                    // Playerの位置を取得
                    Vector3 dirct = player.transform.position;
                    Ray ray = new Ray(transform.position, (dirct - transform.position));
                    RaycastHit hit;
                    if (Physics.Raycast(ray, out hit))
                    {
                        if (hit.collider.name != "Player")
                        {
                        }
                        else
                        {
                            invaded = true;
                            text.enabled = true;
                        }
                    }
                    //Rayの可視化
                    //開始位置、向き×当たった物までの距離、色
                    Debug.DrawRay(ray.origin, ray.direction * 10, new Color(1.0f, 1.0f, 0.0f, 1.0f), 0.1f, true);
                }
            }

            // 視認している場合視野角を広げる
            if (invaded == true)
            {
                colPosition = transform.position;

                if (audioSourceSearch.isPlaying == false)
                {
                    audioSourceSearch.PlayOneShot(seSearch);
                }
            }
            else// if(searchAngle != searchAnglefalse)
            {
                colPosition = centerhit.point;
            }
        }
        else
        {
            audioSourceMove.Stop();
            audioSourceSearch.Stop();
        }
    }
        public void Search()
        {
            invaded = false;
            text.enabled = false;
        }

        private void OnCollisionEnter(Collision collision)
        {
            if (collision.gameObject.CompareTag("Player"))
            {
                invaded = false;
                text.enabled = false;
                audioSourceSearch.Stop();
            }
        }

#if UNITY_EDITOR
    private void OnDrawGizmos()
    {
        Handles.color = new Color(1.0f, 0, 0, 0.1f);
        Handles.DrawSolidDisc(colPosition, new Vector3(0,0.1f,0), len);
    }
#endif
}