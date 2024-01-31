//
// Mecanimのアニメーションデータが、原点で移動しない場合の Rigidbody付きコントローラ
// サンプル
// 2014/03/13 N.Kobyasahi
// 2015/03/11 Revised for Unity5 (only)
//
using UnityEngine;
using System.Collections;

namespace Player
{
    // 必要なコンポーネントの列記
    [RequireComponent(typeof(Animator))]
    [RequireComponent(typeof(CapsuleCollider))]
    [RequireComponent(typeof(Rigidbody))]

    public class P_C : MonoBehaviour
    {
        [Tooltip("キャラクターのスピード")]
        private float speed;
        [Tooltip("キャラクターの通常時スピード")]
        public float walkspeed = 0.1f;
        [Tooltip("キャラクターのアイテム取得時スピード")]
        public float slowspeed = 0.07f;

        public float animSpeed = 1.5f;              // アニメーション再生速度設定
        public float lookSmoother = 3.0f;           // a smoothing setting for camera motion
        public bool useCurves = true;               // Mecanimでカーブ調整を使うか設定する
                                                    // このスイッチが入っていないとカーブは使われない
        public float useCurvesHeight = 0.5f;        // カーブ補正の有効高さ（地面をすり抜けやすい時には大きくする）

        // キャラクターコントローラ（カプセルコライダ）の参照
        private CapsuleCollider col;
        private Rigidbody rb;
        // キャラクターコントローラ（カプセルコライダ）の移動量
        private Vector3 velocity;
        // キャラクターのPlayerControllerを取得
        private PlayerController pc;

        // CapsuleColliderで設定されているコライダのHeiht、Centerの初期値を収める変数
        private float orgColHight;
        private Vector3 orgVectColCenter;
        private Animator anim;                          // キャラにアタッチされるアニメーターへの参照

        [SerializeField]
        private bool running;

        // 初期化
        void Start()
        {
            // Animatorコンポーネントを取得する
            anim = GetComponent<Animator>();
            // CapsuleColliderコンポーネントを取得する（カプセル型コリジョン）
            col = GetComponent<CapsuleCollider>();
            rb = GetComponent<Rigidbody>();
            // CapsuleColliderコンポーネントのHeight、Centerの初期値を保存する
            orgColHight = col.height;
            orgVectColCenter = col.center;

            // キャラクターのPlayerControllerを取得
            pc = GetComponent<PlayerController>();

            // スピードを初期化する
            speed = walkspeed;
        }


        // 以下、メイン処理.リジッドボディと絡めるので、FixedUpdate内で処理を行う.
        void FixedUpdate()
        {
            float moveHorizontal = Input.GetAxis("Horizontal");             // 入力デバイスの水平軸をhで定義
            float moveVertical = Input.GetAxis("Vertical");             // 入力デバイスの垂直軸をvで定義                          

            rb.useGravity = true;//ジャンプ中に重力を切るので、それ以外は重力の影響を受けるようにする


            // 以下、キャラクターの移動処理
            // キャラクターのスピード処理
            SetCharacterSpeed();

            velocity = new Vector3(moveHorizontal, 0, moveVertical);

            /*
            // アニメーションの処理
            if (velocity.magnitude > 0.1f)
            {
                running = true;
                anim.SetBool("run", running);
                //anim.SetBool("hiku", true);
                Vector3 cameraForward = Vector3.Scale(Camera.main.transform.forward, new Vector3(1, 0, 1)).normalized;
                Vector3 moveForward = cameraForward * moveVertical + Camera.main.transform.right * moveHorizontal;

                transform.rotation = Quaternion.LookRotation(moveForward);

                transform.Translate(Vector3.forward * speed);
            }
            else
            {
                running = false;
                anim.SetBool("run", running);
               
            }

            if (velocity.magnitude > 0.1f&&Input.GetKey(KeyCode.Z))
            {
                
                //anim.SetBool("run", running);
                anim.SetBool("hiku", true);
                Vector3 cameraForward = Vector3.Scale(Camera.main.transform.forward, new Vector3(1, 0, 1)).normalized;
                Vector3 moveForward = cameraForward * moveVertical + Camera.main.transform.right * moveHorizontal;

                transform.rotation = Quaternion.LookRotation(moveForward);

                transform.Translate(Vector3.forward * speed *-0.5f) ;
            }
            else
            {
                running = false;
                //anim.SetBool("run", running);
                anim.SetBool("hiku", running);
            }

            if (Input.GetKey(KeyCode.Space))
            {
                anim.SetBool("jump", true);
            }
            AnimatorStateInfo state = anim.GetCurrentAnimatorStateInfo(0);
            if (state.IsName("tobu"))
            {
                anim.SetBool("jump", false);
            }

            if (Input.GetKey(KeyCode.Z))
            {
                anim.SetBool("hiku_start", true);
            }
            AnimatorStateInfo state2 = anim.GetCurrentAnimatorStateInfo(0);
            if (state2.IsName("hiku_start"))
            {
                anim.SetBool("hiku_start", false);
            }
            */
        }

        // キャラクターのコライダーサイズのリセット関数
        void resetCollider()
        {
            // コンポーネントのHeight、Centerの初期値を戻す
            col.height = orgColHight;
            col.center = orgVectColCenter;
        }

        // キャラクターの移動速度を設定
        void SetCharacterSpeed()
        {
            if (!pc.GetItem()) speed = walkspeed;
            else speed = slowspeed;
        }
    }
}